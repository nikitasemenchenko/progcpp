#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <istream>

std::vector<std::string> split(const std::string &str, char d);
void mainSort(std::vector<std::tuple<int, int, int, int>>& start_vector);
std::vector<std::tuple<int, int, int, int>> parse(const std::string& file_name);
void printFullList(std::vector<std::tuple<int, int, int, int>>& list_of_ip);
void printWith1(std::vector<std::tuple<int, int, int, int>>& list_of_ip);
void printWith46(std::vector<std::tuple<int, int, int, int>>& list_of_ip);
void printWith46And70(std::vector<std::tuple<int, int, int, int>>& list_of_ip);