#include <gtest/gtest.h>
#include "list.h"
TEST(ListTest, DefaultConstructor) {
    List<int> list;

    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(ListTest, CopyConstructor) {
    List<int> original;
    original.push_back(1);
    original.push_back(3);

    List<int> copy(original);

    EXPECT_EQ(copy.size(), 2);
    EXPECT_EQ(copy.front(), 1);
    EXPECT_EQ(copy.back(), 3);
}

TEST(ListTest, AssignmentOperator) {
    List<int> original;
    original.push_back(1);
    original.push_back(2);

    List<int> copy;
    copy = original;

    EXPECT_EQ(copy.size(), 2);
    EXPECT_EQ(copy.front(), 1);
    EXPECT_EQ(copy.back(), 2);
}

TEST(ListTest, PushAndPop) {
    List<int> list;

    list.push_front(2);
    list.push_front(1);
    list.push_back(3);

    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
    EXPECT_EQ(list.size(), 3);

    list.pop_front();
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.size(), 2);

    list.pop_back();
    EXPECT_EQ(list.back(), 2);
    EXPECT_EQ(list.size(), 1);
}

TEST(ListTest, InsertAtPosition) {
    List<int> list;
    list.push_back(1);
    list.push_back(3);
    list.insert(1, 2);

    EXPECT_EQ(list.size(), 3);
    auto it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
}

TEST(ListTest, EraseNode) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto node = list.find(2);
    list.erase(node);

    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, Clear) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    list.clear();

    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(ListTest, FindReturnsCorrectNode) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    auto found = list.find(2);
    auto notFound = list.find(3);

    EXPECT_NE(found, nullptr);
    EXPECT_EQ(found->value, 2);
    EXPECT_EQ(notFound, nullptr);
}

TEST(ListTest, FrontAndBackReturnCorrectElements) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

//iterator
TEST(IteratorTest, ReadValues) {
    List<int> list;
    for (int i = 0; i < 5; i++) {
        list.push_back(i * 3 + 1); // 1, 4, 7, 10, 13
    }

    // ++it
    std::stringstream result1;
    for (auto it = list.begin(); it != list.end(); ++it) {
        result1 << *it << " ";
    }
    EXPECT_EQ(result1.str(), "1 4 7 10 13 ");

    // it++
    std::stringstream result2;
    for (auto it = list.begin(); it != list.end(); it++) {
        result2 << *it << " ";
    }
    EXPECT_EQ(result2.str(), "1 4 7 10 13 ");
}

TEST(IteratorTest, WriteValues) {
    List<int> list;
    for (int i = 0; i < 5; i++) {
        list.push_back(0); 
    }

    int value = 10;
    for (auto it = list.begin(); it != list.end(); ++it) {
        *it = value;
        value += 5;
    }

    std::stringstream result;
    for (auto it = list.begin(); it != list.end(); it++) {
        result << *it << " ";
    }
    EXPECT_EQ(result.str(), "10 15 20 25 30 ");
}

TEST(IteratorTest, EmptyList) {
    List<int> list;

    auto begin = list.begin();
    auto end = list.end();
    EXPECT_EQ(begin, end);

    auto it = list.begin();
    ++it; 
    it++; 

    EXPECT_EQ(it, end);
    EXPECT_EQ(it, list.end());
}