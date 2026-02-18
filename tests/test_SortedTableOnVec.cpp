#include <gtest/gtest.h>
#include <sstream>
#include "SortedTableOnVec.h"

TEST(SortedTableOnVecTest, DefaultConstructor) {
    SortedTableOnVec<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
}


TEST(SortedTableOnVecTest, Insert) {
    SortedTableOnVec<int, std::string> table;
    table.insert(3, "three");
    table.insert(1, "one");
    table.insert(2, "two");

    EXPECT_EQ(table.get_by_index(0).first, 1);
    EXPECT_EQ(table.get_by_index(0).second, "one");
    EXPECT_EQ(table.get_by_index(1).first, 2);
    EXPECT_EQ(table.get_by_index(1).second, "two");
    EXPECT_EQ(table.get_by_index(2).first, 3);
    EXPECT_EQ(table.get_by_index(2).second, "three");
}

TEST(SortedTableOnVecTest, FindExistingKey) {
    SortedTableOnVec<int, std::string> table;
    table.insert(10, "ten");

    EXPECT_EQ(table.find(10), "ten");
    EXPECT_THROW(table.find(3), std::out_of_range);
}

TEST(SortedTableOnVecTest, EraseExistingKey) {
    SortedTableOnVec<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");
    table.erase(2);

    EXPECT_FALSE(table.consist(2));
    EXPECT_TRUE(table.consist(1));
    EXPECT_TRUE(table.consist(3));

    EXPECT_THROW(table.erase(10), std::out_of_range);
}

TEST(SortedTableOnVecTest, IsEmpty) {
    SortedTableOnVec<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
}

TEST(SortedTableOnVecTest, Clear) {
    SortedTableOnVec<int, std::string> table;
    table.insert(1, "one");
    table.clear();

    EXPECT_TRUE(table.is_empty());
    EXPECT_THROW(table.find(1), std::out_of_range);
}

TEST(SortedTableOnVecTest, GetMinAndMaxKey) {
    SortedTableOnVec<int, std::string> table;
    table.insert(5, "five");
    table.insert(1, "one");

    EXPECT_EQ(table.get_min_key(), 1);
    EXPECT_EQ(table.get_max_key(), 5);

}

TEST(SortedTableOnVecTest, GetKeys) {
    SortedTableOnVec<int, std::string> table;
    table.insert(3, "three");
    table.insert(1, "one");
    table.insert(2, "two");

    auto keys = table.get_keys();
    EXPECT_EQ(keys[0], 1);
    EXPECT_EQ(keys[1], 2);
    EXPECT_EQ(keys[2], 3);
}

TEST(SortedTableOnVecTest, GetValues) {
    SortedTableOnVec<int, std::string> table;
    table.insert(3, "three");
    table.insert(1, "one");
    table.insert(2, "two");

    auto values = table.get_values();
    EXPECT_EQ(values[0], "one");
    EXPECT_EQ(values[1], "two");
    EXPECT_EQ(values[2], "three");
}

TEST(SortedTableOnVecTest, PrintTable) {
    SortedTableOnVec<int, std::string> table;
    table.insert(2, "two");
    table.insert(1, "one");

    std::stringstream ss;
    ss << table;
    std::string output = ss.str();

    EXPECT_TRUE(output.find("SortedTableOnVec") != std::string::npos);
    EXPECT_TRUE(output.find("{") != std::string::npos);
    EXPECT_TRUE(output.find("}") != std::string::npos);

    size_t pos1 = output.find("1: one");
    size_t pos2 = output.find("2: two");

    EXPECT_TRUE(pos1 != std::string::npos);
    EXPECT_TRUE(pos2 != std::string::npos);
}

