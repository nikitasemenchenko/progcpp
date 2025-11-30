#include "Scanner.h"
#include <cctype>
#include <algorithm>

Scanner::Scanner(const Options &consoleCommand): command(consoleCommand) {};

bool Scanner::checkMask(const std::string &fileName, const std::string &maskName)
{
    std::string file = fileName;
    std::transform(file.begin(), file.end(), file.begin(),
        [](unsigned char c) { return std::tolower(c); });

    std::string mask = maskName;
    std::transform(mask.begin(), mask.end(), mask.begin(),
        [](unsigned char c) { return std::tolower(c); });

    int maskInd = 0; // индекс для маски
    int fileInd = 0; // индекс для файла
    int starInd = -1; // индекс последней звезды в маске
    int matchInd =0; // индекс в файле с которого съедаются символы при звезде

    while(fileInd < file.length()){
        if(maskInd < mask.length() && ((file[fileInd] == mask[maskInd]) || mask[maskInd] == '?' )){ //совпадение символов или ?
            fileInd++; // просто двигаем оба индекса
            maskInd++;
        }
        else if(maskInd < mask.length() && mask[maskInd] == '*'){ //если звезда в маске
            starInd = maskInd; // запоминаем индекс звезды
            maskInd++; // двигаем индекс маски
            matchInd = fileInd; // запоминаем индекс файла где начинается съедание символов
        }
        else if(starInd != -1){ //если была звезда ранее
            matchInd++; //двигаем индекс съедания символов
            fileInd = matchInd; //двигаем индекс файла на съедаемый символ
            maskInd = starInd + 1; //двигаем индекс маски на символ после звезды
        }
        else { // совпадения нет и звезды не было
            return false;
        }
    }
    
    return maskInd == mask.length();
}


bool Scanner::isMasked(const fs::path &file)
{
    if(command.masks.empty()){ //если масок нет то все файлы подходят
        return true;
    }
    std::string filename = file.filename().string();
    for (const auto& mask : command.masks) { //чекаем подходит ли файл под одну из масок
        if (checkMask(filename, mask)) return true;
    }
    return false;
}

bool Scanner::isDisabled(const fs::path &directory)
{
    if(command.disableDirs.empty()){ //если нет отключенных директорий то все директории подходят
        return false;
    }

    for(const auto& dir: command.disableDirs){  //чекаем совпадает ли директория с одной из отключенных
        fs::path path(dir);
        if (fs::absolute(directory) == fs::absolute(path)) return true;
    }
    return false;
};

std::vector<fs::path> Scanner::scan()
{
    result.clear(); // вдруг сканировали уже раньше

    for (const auto& dir : command.dirs) {
        fs::path path(dir);

        if (!fs::exists(path) || !fs::is_directory(path)){ // есои директория не существует или не директория
            continue;
        }

        if (command.depth == 0) { // если глубина 0 только текущая папка
            for (const auto& file : fs::directory_iterator(path)) { // проходим по файлам в папке
                if (fs::is_directory(file.path())) { // если не файл а папка то пропускаем
                    continue;
                }
                else if (fs::is_regular_file(file.path()) && isMasked(file.path()) && fs::file_size(file.path()) >= command.fileSize) { 
                    result.push_back(file.path()); // если файл подходит по маске и размеру добавляем в результат
                }
            }
        } 
        else { // если глубина 1 то и текущая и все вложенные папки
            fs::recursive_directory_iterator it(path), end; // итератор по всем файлам и папкам внутри директории
            while (it != end) {
                if (fs::is_directory(it -> path()) && isDisabled(it -> path())) { //если это папка и она отключена
                    it.disable_recursion_pending();
                }
                else if (fs::is_regular_file(it->path()) && isMasked(it->path()) && fs::file_size(it -> path()) >= command.fileSize) {
                    result.push_back(it -> path()); // если файл подходит по маске и размеру добавляем в результат
                }
                ++it;
            }
        }
    }

    return result;
}