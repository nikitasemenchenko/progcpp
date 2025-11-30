#include "Finder.h"
#include "Options.h"
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

Finder::Finder(const std::vector<fs::path> &scannedFiles, Options options): allFiles(scannedFiles), command(options){};


std::map<size_t, std::vector<fs::path>> Finder::groupBySize()
{
    std::map<size_t, std::vector<fs::path>> groups;
    for(const auto& file: allFiles){
        size_t size = fs::file_size(file);
        groups[size].push_back(file);
    }
    return groups;
}

std::string Finder::getBlockHashCached(const fs::path& file, size_t blockIndex) {
    // проверяем есть ли уже вычисленный хеш в кеше. ключ - файл, значение - вектор хешей где индекс элемента совпадает с номером блока
    auto cache = hashCache.find(file);
    if (cache != hashCache.end() && cache->second.size() > blockIndex) {
        return cache->second[blockIndex];
    }

    // вычисляем хеш блока и сохраняем в кеш
    std::string hash = hasher.getHashedBlock(file, blockIndex, command.blockSize, command.hash);
    if (cache == hashCache.end()) { // если кеша у файла нет нет то создаем новый
        hashCache.emplace(file, std::vector<std::string>(blockIndex + 1));
        cache = hashCache.find(file); // передаем указатель на только что созданный кеш
    } else if (cache->second.size() <= blockIndex) { // если уже какие то хеши были посчитаны но не хватит места для текущего блока
        // увеличиваем размер вектора до нужного индекса
        cache->second.resize(blockIndex + 1);
    }

    cache->second[blockIndex] = hash;
    return hash;
}

std::vector<std::vector<fs::path>> Finder::findDuplicates()
{
    std::vector<std::vector<fs::path>> result;

    auto groupsBySize = groupBySize();

    for (const auto& [fileSize, files] : groupsBySize) {
        if (files.size() < 2) continue; // если 1 файл то дубликатов не может быть 

        const size_t blockCount = (fileSize + command.blockSize - 1) / command.blockSize; // количество блоков в файле

        // Текущие группы кандидатов
        std::vector<std::vector<fs::path>> currentGroups;
        currentGroups.push_back(files); //изначально кандидаты это все файлы одного размера

        // Сравниваем блок за блоком
        for (size_t blockInd = 0; blockInd < blockCount; ++blockInd) {
            std::vector<std::vector<fs::path>> nextGroups;

            for (const auto& group : currentGroups) {
                if (group.size() < 2) continue;

                std::map<std::string, std::vector<fs::path>> byHash; //ключ — хеш блока, значение — вектор файлов с этим хешем

                //хэшируем блок каждго файла в группе и сохраняем в мап
                for (const auto& file : group) {
                    std::string hash = getBlockHashCached(file, blockInd);
                    byHash[hash].push_back(file);
                }

                // оставляем только те подгруппы где >1 файла
                for (auto& [h, subGroup] : byHash) {
                    if (subGroup.size() > 1) {
                        nextGroups.push_back(std::move(subGroup));
                    }
                }
            }

            if (nextGroups.empty()) break;  // больше нет кандидатов
            currentGroups = std::move(nextGroups);
        }

        // все группы которые остались это дубликаты
        for (auto& group : currentGroups) {
            if (group.size() > 1) {
                result.push_back(std::move(group));
            }
        }
    }

    return result;
}