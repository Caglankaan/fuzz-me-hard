#include <filesystem>
#include <iostream>
#include "parameters.h"
#include "fuzzer.h"
#include "file_io.h"
#include <unistd.h>
#include "mutation.h"

std::vector<std::string> split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

bool is_number(const std::string &s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

int main(int argc, char **argv){
    if(getuid())
    {
        std::cout << "This project must be run as root !\n";
        exit(1);
    }

    InputParser input(argc, argv);

    std::string binary_path{};
    std::string original_file{};
    std::string mutation_type{"dword"};
    std::string log_file{"log.txt"};
    std::string work_dir{"./"};

    if(input.cmdOptionExists("-w"))
    {
        work_dir = input.getCmdOption("-w");
        if(!FileIO::isDirectoryExists(work_dir))
        {
            std::cout << "Please enter valid working directory. \"" << work_dir << "\" does not exists\n";
            exit(1);
        }
        
    }
    if(input.cmdOptionExists("-b"))
    {
        
        binary_path = input.getCmdOption("-b");
        if(!FileIO::fileExists(binary_path))
        {
            std::cout << "Please enter valid binary path !\n";
            exit(1);
        }
    }
    else
    {
        std::cout << "Please enter binary path!\n";
        exit(1);
    }
    if(input.cmdOptionExists("-t"))
    {
        mutation_type = input.getCmdOption("-t");
    }
    if(input.cmdOptionExists("-f"))
    {
        original_file = input.getCmdOption("-f");
        if(!FileIO::fileExists(original_file))
        {
            std::cout << "Please enter valid file path !\n";
            exit(1);
        }
    }
    else
    {
        std::cout << "Please enter file path!\n";
        exit(1);
    }
    
    std::filesystem::path work_dir_path(work_dir);

    Fuzzer fuzzer(work_dir_path, binary_path, binary_path);
    
    Mutation mut(original_file, mutation_type, work_dir_path);

    for(int i = 0; i < mut.original_file_content.size(); i++)
    {
        for(int j = 0; j < mut.values.size(); j++)
        {
            std::string filename = mut.mutateTheFile(i,j);
            std::filesystem::path filename_fs(filename);
            std::filesystem::path input_path = work_dir_path/filename_fs;
            if(!fuzzer.fuzz(input_path))
            {
                FileIO::removeFile(input_path);
            }
        }
        if(i%10 == 0)
            std::cout << std::to_string(i*mut.values.size()) << " mutation executed, current crash count: " << fuzzer.crash_count << "\n";
    }
    
    std::cout << "Total crashes: " << fuzzer.crash_count << " in " << std::to_string(mut.values.size() * mut.original_file_content.size()) << " execution" << "\n";
    
    
    return 0;
}