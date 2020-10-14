#pragma once

#ifndef FUZZ_ME_HARD_HEADERS_MUTATIONS
#define FUZZ_ME_HARD_HEADERS_MUTATIONS

#include <iostream>
#include <vector>
#include <algorithm>
#include <vector>
#include "limits.h"
#include "file_io.h"


class Mutation{
    public:
        std::string original_file_content;
        std::string copy_of_original_file_content;
        std::string original_file;
        std::string output_directory;
        std::string mutation_type;
        std::string tmp_directory;
        std::vector<std::vector<unsigned int>> values;
        Mutation(const std::filesystem::path& original_file, const std::string& mutation_type, const std::filesystem::path& work_dir);
        void convertToBytes(const std::string& mutation_type);
        std::string mutateTheFile(int offset, int mutation_index);
};

struct MutationTypeStruct
{
    MutationTypeStruct(unsigned int val_, std::string process_, short size_): 
        val(val_), process(process_), size(size_) 
        {

        }
    unsigned int val;
    std::string process;
    short size;
};

namespace MutationType
{
    extern std::vector<MutationTypeStruct> v32_bit;

}
#endif //FUZZ_ME_HARD_HEADERS_MUTATIONS