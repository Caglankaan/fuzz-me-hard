#include <iostream>
#include <vector>
#include <algorithm>
#include <vector>
#include "file_io.h"
class Fuzzer{
    public:
        std::string save_path;
        std::string temp_path;
        std::string log_path;
        std::string binary_path;
        std::string mutation_type;
        Fuzzer(const std::filesystem::path& work_dir, const std::string& binary_path_, const std::string& mutation_type_);
        void start();
};