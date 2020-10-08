#include <iostream>
#include <vector>
#include <algorithm>
#include <vector>
#include "file_io.h"

#define MAX8 0xff
#define MAX16 0xffff
#define MAX32 0xffffffff

class Mutation{
    public:
        std::string original_file;
        std::string mutation_type;
        std::string tmp_directory;
        Mutation(const std::filesystem::path& original_file, const std::string& mutation_type, const std::string& tmp_directory);
};


namespace MutationType
{
    
}