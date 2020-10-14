#pragma once

#ifndef SHELLPHUZZ_CPP_HEADERS_FUZZER
#define SHELLPHUZZ_CPP_HEADERS_FUZZER

#include <iostream>
#include <vector>
#include <algorithm>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "file_io.h"
#include "timer.h"

class Fuzzer{
    public:
        std::string temp_dir;
        std::string log_dir;
        std::string binary_dir;
        int crash_count{0};
        Fuzzer(const std::filesystem::path& work_dir, const std::filesystem::path& temp_dir_, const std::filesystem::path&binary_dir_);
        void start();
        bool fuzz(const std::filesystem::path &filename, Timer &timer);
};

#endif