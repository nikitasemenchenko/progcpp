#include "Hasher.h"
#include <fstream>
#include <vector>
#include <boost/uuid/detail/md5.hpp>
#include <boost/crc.hpp>
#include <iomanip>

std::string Hasher::getHashedBlock(const fs::path &filePath, size_t blockIndex, size_t blockSize, const std::string &hashAlgo)
{
    std::ifstream file(filePath.string(), std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("file openning error: " + filePath.string());
    }
    file.seekg(blockIndex * blockSize); //перемещаем указатель на место блока
    std::vector<char> buffer(blockSize, 0); //заполняем нулями для выравнивания
    file.read(buffer.data(), blockSize); //записываем
    if (hashAlgo == "crc32") {
            return hashCrc32(buffer.data(), blockSize);
        } else if (hashAlgo == "md5") {
            return hashMd5(buffer.data(), blockSize);
        }
}

std::string Hasher::hashCrc32(const char *data, size_t size)
{
    boost::crc_32_type result;
    result.process_bytes(data, size);

    //преобразуем в строку из шестнадцатеричных символов
    std::stringstream ss;
    ss << std::hex << std::setw(8) << std::setfill('0') << result.checksum();
    return ss.str();
}

std::string Hasher::hashMd5(const char *data, size_t size)
{
    boost::uuids::detail::md5 hash;
    hash.process_bytes(data, size);
    boost::uuids::detail::md5::digest_type digest; //массив для хранения хэша - 16 байтовый
    hash.get_digest(digest); //получение хэша

    // Преобразование 16-байтового массива digest в 32-значную шестнадцатеричную строку
    std::stringstream ss;
    for(int i = 0; i < 16; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i];
    }
    return ss.str();
}
