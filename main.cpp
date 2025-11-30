#include <iostream>
#include "Parser.h"
#include "Scanner.h"
#include "Finder.h"
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

int main(int argc, char** argv){
    Parser parser;
    Options options;
    options = parser.parse(argc, argv);
    Scanner scanner(options);
    std::vector<fs::path> scannedFiles = scanner.scan();
    Finder finder(scannedFiles, options);
    std::vector<std::vector<fs::path>> duplicates = finder.findDuplicates();
    for (const auto& group : duplicates) {
        for (const auto& file : group) {
            std::cout << "  " << file.string() << std::endl;
        }
        std::cout << std::endl;
    }
    return 0;
}
