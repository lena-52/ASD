#include <gtest/gtest.h>
#include "UnsortedTableOnVec.h"

TEST(UnsortedTableOnVecTest, DefaultConstructor) {
    UnsortedTableOnVec<int, std::string> table;
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
    EXPECT_THROW(table.find(7), std::logic_error);
}

TEST(UnsortedTableOnVecTest, InsertNewElement) {
    UnsortedTableOnVec<int, std::string> table;
    table.insert(1, "one");

    EXPECT_EQ(table.size(), 1);
    EXPECT_TRUE(table.consist(1));
    EXPECT_EQ(table.find(1), "one");
    EXPECT_TRUE(table.consist(1));
    EXPECT_FALSE(table.consist(6));
}

TEST(UnsortedTableOnVecTest, InsertDuplicateKey) {
    UnsortedTableOnVec<int, std::string> table;
    table.insert(1, "one");
    table.insert(1, "один");

    EXPECT_EQ(table.size(), 1);
    EXPECT_EQ(table.find(1), "один");
}

TEST(UnsortedTableOnVecTest, FindExistingKey) {
    UnsortedTableOnVec<int, std::string> table;
    table.insert(5, "five");

    EXPECT_EQ(table.find(5), "five");
}

TEST(UnsortedTableOnVecTest, EraseKey) {
    UnsortedTableOnVec<int, std::string> table;
    table.insert(1, "one");
    table.insert(6, "six");
    table.erase(1);

    EXPECT_EQ(table.size(), 1);
    EXPECT_FALSE(table.consist(1));
    EXPECT_TRUE(table.consist(6));
    EXPECT_THROW(table.erase(7), std::logic_error);
}


TEST(UnsortedTableOnVecTest, ClearTable) {
    UnsortedTableOnVec<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.clear();

    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
    EXPECT_FALSE(table.consist(1));
    EXPECT_FALSE(table.consist(2));
}

TEST(UnsortedTableOnVecTest, PrintTable) {
    UnsortedTableOnVec<int, std::string> table;
    table.insert(1, "one");

    std::stringstream ss;
    ss << table;
    std::string output = ss.str();

    // Проверяем, что вывод содержит ключи и значения
    EXPECT_TRUE(output.find("1") != std::string::npos);
    EXPECT_TRUE(output.find("one") != std::string::npos);
    EXPECT_TRUE(output.find("UnsortedTableOnVec") != std::string::npos);
}

TEST(UnsortedTableOnVecTest, PrintEmptyTable) {
    UnsortedTableOnVec<int, std::string> table;

    std::stringstream ss;
    ss << table;
    std::string output = ss.str();

    EXPECT_TRUE(output.find("UnsortedTableOnVec") != std::string::npos);
    EXPECT_TRUE(output.find("{") != std::string::npos);
    EXPECT_TRUE(output.find("}") != std::string::npos);
}

// Комплексный тест
TEST(UnsortedTableOnVecTest, ComplexScenario) {
    UnsortedTableOnVec<int, std::string> table;

    // Вставка элементов
    for (int i = 0; i < 10; ++i) {
        table.insert(i, "value" + std::to_string(i));
    }

    EXPECT_EQ(table.size(), 10);

    // Проверка наличия
    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(table.consist(i));
    }

    // Поиск значений
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(table.find(i), "value" + std::to_string(i));
    }

    // Обновление значений
    for (int i = 0; i < 10; i += 2) {
        table.insert(i, "updated" + std::to_string(i));
    }

    EXPECT_EQ(table.size(), 10);
    for (int i = 0; i < 10; ++i) {
        if (i % 2 == 0) {
            EXPECT_EQ(table.find(i), "updated" + std::to_string(i));
        }
        else {
            EXPECT_EQ(table.find(i), "value" + std::to_string(i));
        }
    }

    // Удаление элементов
    for (int i = 0; i < 10; i += 3) {
        table.erase(i);
    }

    for (int i = 0; i < 10; ++i) {
        if (i % 3 == 0) {
            EXPECT_FALSE(table.consist(i));
        }
        else {
            EXPECT_TRUE(table.consist(i));
        }
    }

    // Очистка
    table.clear();
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
}