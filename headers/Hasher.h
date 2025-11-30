#pragma once
#include <string>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

class Hasher {
    public:
        std::string getHashedBlock(const fs::path& filePath, size_t blockIndex, size_t blockSize, const std::string& hashAlgo);
    private:
        std::string hashCrc32(const char* data, size_t size);
        std::string hashMd5(const char* data, size_t size);
};