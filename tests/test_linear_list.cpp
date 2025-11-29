#include <gtest/gtest.h>
#include "list.h"

TEST(ListTest, BasicTest) {
    List<int> list;
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);

    list.push_back(1);
    EXPECT_FALSE(list.is_empty());
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 1);

    list.push_front(0);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 0);
    EXPECT_EQ(list.back(), 1);
}

TEST(ListTest, CopyTest) {
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);

    List<int> list2 = list1;
    EXPECT_EQ(list2.size(), 2);
    EXPECT_EQ(list2.front(), 1);
    EXPECT_EQ(list2.back(), 2);
}