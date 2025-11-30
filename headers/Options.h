#pragma once
#include <vector>
#include <string>

struct Options {
        std::vector<std::string> dirs;
        std::vector<std::string> disableDirs;
        int depth;
        size_t fileSize;
        std::vector<std::string> masks;
        size_t blockSize;
        std::string hash;
    };