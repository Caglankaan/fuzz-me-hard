#pragma once

#ifndef SHELLPHUZZ_CPP_HEADERS_FILE_IO
#define SHELLPHUZZ_CPP_HEADERS_FILE_IO

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

namespace FileIO 
{   
    bool fileExists (const std::string& name);
    bool isDirectoryExists(const std::string& path);
    void createFileWithContent(std::string path, std::string fileName, std::string content);
    void writeToFile(std::string fileText, std::string &fileName);
    void removeDirectory(const std::string &path);
    void removeFile(const std::string &path);
    void createDirectory(const std::string &path);
    std::string fileToString(const std::string &fileName);
    template<typename T>
    void reCreateDirectories(const T &t)
    {
        if(!FileIO::isDirectoryExists(t))
            FileIO::createDirectory(t);
        else
        {
            FileIO::removeDirectory(t);
            FileIO::createDirectory(t);
        }
    }

    template<typename T, typename... Args>
    void reCreateDirectories(const T &t, Args... args)
    {
        if(!FileIO::isDirectoryExists(t))
            FileIO::createDirectory(t);
        else
        {
            FileIO::removeDirectory(t);
            FileIO::createDirectory(t);
        }
        reCreateDirectories(args...);
    }
}
#endif