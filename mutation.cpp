#include "mutation.h"
#include "struct_pack.h"

static std::vector<std::string> split(const std::string& str, const std::string& delim)
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

std::vector<MutationTypeStruct> v32_bit
{
    MutationTypeStruct(0x00, "replace", 4),MutationTypeStruct(0x01, "replace", 4),MutationTypeStruct(UINT_MAX/2-16, "replace", 4),
    MutationTypeStruct(UINT_MAX/2-1, "replace", 4),MutationTypeStruct(UINT_MAX/2, "replace", 4),MutationTypeStruct(UINT_MAX/2+1, "replace", 4),
    MutationTypeStruct(UINT_MAX/2+16, "replace", 4),MutationTypeStruct(UINT_MAX-1, "replace", 4),MutationTypeStruct(UINT_MAX, "replace", 4)
};

Mutation::Mutation(const std::filesystem::path& original_file_, const std::string& mutation_type, const std::filesystem::path& work_dir)
{
    std::filesystem::path temp("temp");
    std::filesystem::path output("output");
    tmp_directory = work_dir / temp;
    output_directory = work_dir / output;
    original_file = original_file_;
    original_file_content = FileIO::fileToString(original_file);

    FileIO::reCreateDirectories(tmp_directory, output_directory);
    
    convertToBytes(mutation_type);
}
void Mutation::convertToBytes(const std::string& mutation_type)
{
    std::shared_ptr<StructPack> s = StructPack::getInstance();
    for(auto &val: v32_bit)
    {
        values.push_back(s->unpack(s->pack("<", val.val)));
    }
}

std::string Mutation::mutateTheFile(int offset, int mutation_index)
{
    
    /*if(offset >= values.size() || offset +4 >= values.size())
        throw "Index out of bounds";
    */
    copy_of_original_file_content = original_file_content;
    for(int i = offset; i < offset + 4; i++)
    {
        copy_of_original_file_content[i] = values[mutation_index][i-offset];
    }
    
    std::stringstream ss;
    std::vector<std::string> splitted = split(original_file, "/");
    std::vector<std::string> name = split(splitted.back(), ".") ;
    ss << tmp_directory << "/" << name[0] << "-" << offset << "-" << mutation_index << "." << name[1];

    std::ofstream file;
    file.open(ss.str());
    file << copy_of_original_file_content;
    file.close();

    return ss.str();
    
}