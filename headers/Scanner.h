#pragma once
#include <boost/filesystem.hpp>
#include "Options.h"

namespace fs = boost::filesystem;

class Scanner {
    public:
        Scanner(const Options& consoleCommand);
        std::vector<fs::path> scan();
    private:
        Options command;
        std::vector<fs::path> result;
        bool checkMask(const std::string &fileName, const std::string &maskName);
        bool isMasked(const fs::path& file);
        bool isDisabled(const fs::path& dir);
};