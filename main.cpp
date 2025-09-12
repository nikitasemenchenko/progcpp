#include "functions.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
int main(){ 
    auto ip_pool = parse("ip_filter.tsv");

    mainSort(ip_pool); 
    printFullList(ip_pool); 
    printWith1(ip_pool); 
    printWith46And70(ip_pool); 
    printWith46(ip_pool); 
    return 0; 
}