#include <gtest/gtest.h>
#include "algorithms.h"

TEST(BracketCheck, Simple_Correct_Sequences) {
    EXPECT_TRUE(check_brackets("()"));
    EXPECT_TRUE(check_brackets("[]"));
    EXPECT_TRUE(check_brackets("{}"));
}

//вложенные скобки
TEST(BracketCheck, Nested_Correct_Sequences) {
    EXPECT_TRUE(check_brackets("({[]})"));
    EXPECT_TRUE(check_brackets("[({})]"));
    EXPECT_TRUE(check_brackets("{([])}"));
    EXPECT_FALSE(check_brackets("({[}])"));
    EXPECT_FALSE(check_brackets("([)]"));
    EXPECT_FALSE(check_brackets("{(})"));
}

TEST(BracketCheck, Text_Between_Brackets) {
    EXPECT_TRUE(check_brackets("(hello)"));
    EXPECT_TRUE(check_brackets("[hello]{world}"));
    EXPECT_TRUE(check_brackets("h(e[l{l}o]w)d"));
}

TEST(BracketCheck, Simple_Incorrect_Sequences) {
    EXPECT_FALSE(check_brackets("("));
    EXPECT_FALSE(check_brackets(")"));
    EXPECT_FALSE(check_brackets("["));
    EXPECT_FALSE(check_brackets("]"));
    EXPECT_FALSE(check_brackets("{"));
    EXPECT_FALSE(check_brackets("}"));
}

TEST(BracketCheck, notmatched_Brackets) {
    EXPECT_FALSE(check_brackets("(]"));
    EXPECT_FALSE(check_brackets("[)"));
    EXPECT_FALSE(check_brackets("{)"));
    EXPECT_FALSE(check_brackets("(}"));
    EXPECT_FALSE(check_brackets("{]"));
    EXPECT_FALSE(check_brackets("[}"));
}

TEST(BracketCheck, Wrong_Order) {
    EXPECT_FALSE(check_brackets(")("));
    EXPECT_FALSE(check_brackets("]["));
    EXPECT_FALSE(check_brackets("}{"));
}

TEST(BracketCheck, Unclosed_Brackets) {
    EXPECT_FALSE(check_brackets("({[]"));
    EXPECT_FALSE(check_brackets("[({})"));
    EXPECT_FALSE(check_brackets("{([]"));
    EXPECT_FALSE(check_brackets("()]"));
    EXPECT_FALSE(check_brackets("{}[)"));
    EXPECT_FALSE(check_brackets("[]})"));
}


TEST(IslandsTest, ExampleFromProblem) {
    const int rows = 5;
    const int cols = 5;

    int** grid = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        grid[i] = new int[cols];
    }

    int data[rows][cols] = {
        {0, 1, 0, 0, 1},
        {0, 1, 1, 0, 1},
        {1, 1, 0, 1, 1},
        {0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1}
    };

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = data[i][j];
        }
    }

    EXPECT_EQ(countIslands(grid, rows, cols), 3);

    for (int i = 0; i < rows; ++i) delete[] grid[i];
    delete[] grid;
}

TEST(IslandsTest, NoLand) {
    const int rows = 3;
    const int cols = 3;

    int** grid = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        grid[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = 0;
        }
    }

    EXPECT_EQ(countIslands(grid, rows, cols), 0);

    for (int i = 0; i < rows; ++i) delete[] grid[i];
    delete[] grid;
}

TEST(IslandsTest, AllLand) {
    const int rows = 3;
    const int cols = 3;

    int** grid = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        grid[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = 1;
        }
    }

    EXPECT_EQ(countIslands(grid, rows, cols), 1);

    for (int i = 0; i < rows; ++i) delete[] grid[i];
    delete[] grid;
}

TEST(IslandsTest, DiagonalNotConnected) {
    const int rows = 3;
    const int cols = 3;

    int** grid = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        grid[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = 0;
        }
    }

    grid[0][0] = 1;
    grid[1][1] = 1;
    grid[2][2] = 1;

    EXPECT_EQ(countIslands(grid, rows, cols), 3);

    for (int i = 0; i < rows; ++i) delete[] grid[i];
    delete[] grid;
}

TEST(IslandsTest, SingleIslands) {
    const int rows = 4;
    const int cols = 4;

    int** grid = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        grid[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = 0;
        }
    }

    grid[0][0] = 1;
    grid[1][2] = 1;
    grid[3][3] = 1;

    EXPECT_EQ(countIslands(grid, rows, cols), 3);

    for (int i = 0; i < rows; ++i) delete[] grid[i];
    delete[] grid;
}

TEST(IslandsTest, TwoSeparatedIslands) {
    const int rows = 4;
    const int cols = 4;

    int** grid = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        grid[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = 0;
        }
    }

    // Левый верхний остров
    grid[0][0] = 1;
    grid[0][1] = 1;
    grid[1][0] = 1;

    // Правый нижний остров
    grid[2][2] = 1;
    grid[2][3] = 1;
    grid[3][2] = 1;
    grid[3][3] = 1;

    EXPECT_EQ(countIslands(grid, rows, cols), 2);

    for (int i = 0; i < rows; ++i) delete[] grid[i];
    delete[] grid;
}