#include <gtest/gtest.h>
#include "../functions.h"
#include <vector>
#include <tuple>

TEST(split, empty) {
    auto r = split("", '.');
    ASSERT_EQ(r.size(), 1);
    EXPECT_EQ(r[0], "");
}

TEST(split, onePart) {
    auto r = split("11", '.');
    ASSERT_EQ(r.size(), 1);
    EXPECT_EQ(r[0], "11");
}

TEST(split, twoParts) {
    auto r = split("11.22", '.');
    ASSERT_EQ(r.size(), 2u);
    EXPECT_EQ(r[0], "11");
    EXPECT_EQ(r[1], "22");
}

TEST(sort, check){
    std::vector<std::tuple<int, int, int, int>> ips = {{1, 2, 3, 4}, {1, 10, 1, 1}, {2, 0, 0, 0}};
    mainSort(ips);

    EXPECT_EQ(std::get<0>(ips[0]), 2);

    EXPECT_EQ(std::get<0>(ips[1]), 1);
    EXPECT_EQ(std::get<1>(ips[1]), 10);

    EXPECT_EQ(std::get<0>(ips[2]), 1);
    EXPECT_EQ(std::get<1>(ips[2]), 2);
}