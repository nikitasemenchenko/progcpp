#pragma once
#include <map>
#include <vector>
#include <boost/filesystem.hpp>
#include "Options.h"
#include "Hasher.h"

namespace fs = boost::filesystem;

class Finder {
    public:
        Finder(const std::vector<fs::path>& scannedFiles, Options options);
        std::vector<std::vector<fs::path>> findDuplicates();
    private:
        std::vector<fs::path> allFiles;
        Options command;
        Hasher hasher;
        std::map<size_t, std::vector<fs::path>> groupBySize();
        std::map<fs::path, std::vector<std::string>> hashCache;
        std::string getBlockHashCached(const fs::path& file, size_t blockIndex);
};