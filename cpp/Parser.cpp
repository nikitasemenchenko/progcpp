#include "Parser.h"
#include "Options.h"
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

Options Parser::parse(int argc, char **argv)
{
    Options command;
    po::variables_map vm;
    po::options_description descrtiption("Options");
    descrtiption.add_options()
    ("help", "show all options")
    ("dirs", po::value< std::vector<std::string> >(), "select directories to scan")
    ("disableDirs", po::value<std::vector<std::string>>()->default_value({}, "none"), "select directories you do not want to scan")
    ("depth", po::value<int>()->default_value(0), "set scanning depth")
    ("fileSize", po::value<size_t>()->default_value(1), "set minimal file size to scan")
    ("masks", po::value<std::vector<std::string>>()->default_value({}, "none"), "set masks of file names allowed for comparison")
    ("blockSize", po::value<size_t>()->default_value(1024), "set minimal block size to compare")
    ("hash", po::value<std::string>()->default_value("crc32"), "set hash algorithm (crc32 or md5)");

    try {
        po::store(po::parse_command_line(argc, argv, descrtiption), vm);
        po::notify(vm); 
    } catch (const po::error& e) {
        std::cout << "Ошибка парсинга: " << e.what() << std::endl;
        std::cout << descrtiption << std::endl;
        exit(0);
    }

    if(vm.count("help")){
        std::cout << descrtiption << std::endl;
        exit(0);
    }


    if(vm.count("dirs")){
        command.dirs = vm["dirs"].as<std::vector<std::string>>();
        if(command.dirs.empty()){
            throw std::invalid_argument("type directories to scan");
        }
    }



    if(vm.count("disableDirs")){
        command.disableDirs = vm["disableDirs"].as<std::vector<std::string>>();
    }


    if(vm.count("depth")){
        command.depth = vm["depth"].as<int>();
        if(command.depth > 1  || command.depth < 0){
            throw std::invalid_argument("depth must be 0 or 1");
        }
    }


    if(vm.count("fileSize")){
        command.fileSize = vm["fileSize"].as<size_t>();
        if(command.fileSize <1){
            throw std::invalid_argument("size of file must be at least 1 byte");
        }
    }


    if(vm.count("masks")){
        command.masks = vm["masks"].as<std::vector<std::string>>();
    }


    if(vm.count("blockSize")){
        command.blockSize = vm["blockSize"].as<size_t>();
        if(command.blockSize <1){
            throw std::invalid_argument("invalid block size");
        }
    }
    if(vm.count("hash")){
        command.hash = vm["hash"].as<std::string>();
        if(command.hash != "crc32" && command.hash != "md5"){
            throw std::invalid_argument("must be crc32 or md5");
        }
    }

    return command;
};