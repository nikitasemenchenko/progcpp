#include <iostream>
#include "version.h"

int main() {
    std::cout << "Hello world! Version " << VERSION_MAJOR << '.' << VERSION_MINOR << '.' << VERSION_PATCH << std::endl;
    return 0;
}