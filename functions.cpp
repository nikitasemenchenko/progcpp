#include "functions.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>
#include <algorithm>

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

std::vector<std::tuple<int, int, int, int>> parse(const std::string& file_name){
    std::ifstream file(file_name);

    std::vector<std::tuple<int, int, int, int>> ip_pool;

    std::string line;
    while(std::getline(file, line)) {
        std::vector<std::string> v = split(line, '\t');
        std::vector<std::string> ip_parts = split(v[0], '.');
            
        int a = std::stoi(ip_parts[0]);
        int b = std::stoi(ip_parts[1]);
        int c = std::stoi(ip_parts[2]);
        int d = std::stoi(ip_parts[3]);
        std::tuple<int, int, int, int> ip {a, b, c, d};
        ip_pool.push_back(ip);
    }
    file.close();
    return ip_pool;
}

void mainSort(std::vector<std::tuple<int, int, int, int>>& start_vector){
    std::sort(start_vector.begin(), start_vector.end(), [](const auto& a, const auto& b) {
    return a > b;
});
}

void printFullList(std::vector<std::tuple<int, int, int, int>>& list_of_ip) {
    for (int i = 0; i < list_of_ip.size(); ++i) {
        auto ip = list_of_ip[i];
        std::cout << std::get<0>(ip) << "." << std::get<1>(ip) << "." << std::get<2>(ip) << "." << std::get<3>(ip) << std::endl;
    }
    std::cout << '\n';
}

void printWith1(std::vector<std::tuple<int, int, int, int>>& list_of_ip) {
    for (int i = 0; i < list_of_ip.size(); ++i) {
        auto ip = list_of_ip[i];
        if (std::get<0>(ip) == 1) {
            std::cout << std::get<0>(ip) << "." << std::get<1>(ip) << "." << std::get<2>(ip) << "." << std::get<3>(ip) << std::endl;
        }
    }
    std::cout << '\n';
}

void printWith46And70(std::vector<std::tuple<int, int, int, int>>& list_of_ip) {
    for (int i = 0; i < list_of_ip.size(); ++i) {
        auto ip = list_of_ip[i];
        if (std::get<0>(ip) == 46 && std::get<1>(ip) == 70) {
            std::cout << std::get<0>(ip) << "." << std::get<1>(ip) << "." << std::get<2>(ip) << "." << std::get<3>(ip) << std::endl;
        }
    }
    std::cout << '\n';
}

void printWith46(std::vector<std::tuple<int, int, int, int>>& list_of_ip) {
    for (int i = 0; i < list_of_ip.size(); ++i) {
        auto ip = list_of_ip[i];
        if (std::get<0>(ip) == 46 || std::get<1>(ip) == 46 || std::get<2>(ip) == 46 || std::get<3>(ip) == 46) {
            std::cout << std::get<0>(ip) << "." << std::get<1>(ip) << "." << std::get<2>(ip) << "." << std::get<3>(ip) << std::endl;
        }
    }
    std::cout << '\n';
}