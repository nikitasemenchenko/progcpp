#include <iostream>
#include <map>
#include "headers/myAllocator.h"
#include "headers/myvector.h"

int factorial(int n) {
    if (n == 0) return 1;
    int x = 1;
    for (int i = 2; i <= n; ++i) {
        x *= i;
    }
    return x;
}

int main() {
    std::map<int, int> defaultMap;

    for (int i = 0; i < 10; ++i) {
        defaultMap[i] = factorial(i);
    }
    std::cout << "Standart map:"<<std::endl;
    for (auto& m : defaultMap) {
        std::cout << m.first << " " << m.second << "\n";
    }

    myAllocator<std::pair<const int, int>> mapAlloc(10);
    std::map<int, int, std::less<int>, myAllocator<std::pair<const int, int>>> customMap(std::less<int>(), mapAlloc);

    for (int i = 0; i < 10; ++i) {
        customMap[i] = factorial(i);
    }

    std::cout << "\n Map with custom allocator:"<<std::endl;
    for (auto& m : customMap) {
        std::cout << m.first << " " << m.second << "\n";
    }

    MyVector<int> vec1;

    for (int i = 0; i < 10; ++i) {
        vec1.push_back(i);
    }

    std::cout << "\n Standart vector:"<<std::endl;
    for (auto& value : vec1) {
        std::cout << value << " ";
    }

    MyVector<int, myAllocator<int>> vec2;

    for (int i = 0; i < 10; ++i) {
        vec2.push_back(i);
    }

    std::cout << "\n Vector with custom allocator:"<<std::endl;
    for (auto& value : vec2) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    return 0;
}