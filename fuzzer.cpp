#include "fuzzer.h"
#include <thread> 
#include <vector>

Fuzzer::Fuzzer(const std::filesystem::path& work_dir, const std::string& binary_path_, const std::string& mutation_type_)
{
    std::filesystem::path save("save");
    std::filesystem::path temp("temp");
    std::filesystem::path log("log.txt");
    save_path = work_dir / save;
    temp_path = work_dir / temp;
    log_path = work_dir / log;
    binary_path = binary_path_;
    mutation_type = mutation_type_;

    
}

void exec(const char* cmd, std::string &filename) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        FileIO::writeToFile(buffer.data(), filename);
    }
}

void threadForFuzzing(std::string name, std::string command)
{
    exec(command.c_str(), name);
}

void Fuzzer::start()
{
    /*
    std::vector<std::thread> workers;
    for(int i = 1; i <= 1; i++)
    {
      
        workers.push_back(std::thread(threadForFuzzing, "name", "ss_command.str()"));
    }
    
    for(auto &thread: workers){
        thread.join();
    }
    */
}
