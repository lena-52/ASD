#include <gtest/gtest.h>
#include "algorithms.h"

// Тесты для проверки скобок
TEST(BracketCheck, Simple_Correct_Sequences) {
    EXPECT_TRUE(check_brackets("()"));
    EXPECT_TRUE(check_brackets("[]"));
    EXPECT_TRUE(check_brackets("{}"));
}

TEST(BracketCheck, Nested_Correct_Sequences) {
    EXPECT_FALSE(check_brackets("({[}])"));
    EXPECT_FALSE(check_brackets("([)]"));
    EXPECT_FALSE(check_brackets("{(})"));
}

TEST(BracketCheck, Text_Between_Brackets) {
    EXPECT_TRUE(check_brackets("h(e[l{l}o]w)d"));
}

TEST(BracketCheck, Simple_Incorrect_Sequences) {
    EXPECT_FALSE(check_brackets("("));
    EXPECT_FALSE(check_brackets("["));
    EXPECT_FALSE(check_brackets("{"));
}

TEST(BracketCheck, Notmatched_Brackets) {
    EXPECT_FALSE(check_brackets("{)"));
    EXPECT_FALSE(check_brackets("(}"));
    EXPECT_FALSE(check_brackets("[}"));
}

TEST(BracketCheck, Wrong_Order) {
    EXPECT_FALSE(check_brackets(")("));
    EXPECT_FALSE(check_brackets("]["));
    EXPECT_FALSE(check_brackets("}{"));
}

TEST(BracketCheck, Unclosed_Brackets) {
    EXPECT_FALSE(check_brackets("({[]"));
    EXPECT_FALSE(check_brackets("{}[)"));
}

TEST(IslandsTest, Example) {
    const int rows = 5;
    const int cols = 5;

    int** grid = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        grid[i] = new int[cols];
    }

    int data[rows][cols] = {{0, 1, 0, 0, 1},{0, 1, 1, 0, 1},{1, 1, 0, 1, 1},{0, 0, 0, 0, 1},{1, 0, 1, 1, 1}};

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = data[i][j];
        }
    }

    EXPECT_EQ(countIslands(grid, rows, cols), 3);

    for (int i = 0; i < rows; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
}

TEST(IslandsTest, NoLand) {
    const int rows = 3;
    const int cols = 3;

    int** grid = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        grid[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = 0; // Вся вода
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
    // создание матрицы 3x3 из нулей 
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

TEST(IslandsTest, TwoIslands) {
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
    grid[0][1] = 1;
    grid[1][0] = 1;

    grid[2][2] = 1;
    grid[2][3] = 1;
    grid[3][2] = 1;
    grid[3][3] = 1;

    EXPECT_EQ(countIslands(grid, rows, cols), 2);

    for (int i = 0; i < rows; ++i) delete[] grid[i];
    delete[] grid;
}



// Тесты для заяц-черепаха
TEST(CycleTest_TurtleRabbit, EmptyList) {
    Node<int>* head = nullptr;
    EXPECT_FALSE(check_cycle_turtle_rabbit(head));
}

TEST(CycleTest_TurtleRabbit, SingleElementNoCycle) {
    Node<int>* head = new Node<int>(1);
    EXPECT_FALSE(check_cycle_turtle_rabbit(head));
    delete head;
}

TEST(CycleTest_TurtleRabbit, NoCycle) {
    Node<int>* head = new Node<int>(1);
    head->next = new Node<int>(2);
    head->next->next = new Node<int>(3);

    EXPECT_FALSE(check_cycle_turtle_rabbit(head));

    delete head->next->next;
    delete head->next;
    delete head;
}

TEST(CycleTest_TurtleRabbit, WithCycle) {
    Node<int>* head = new Node<int>(1);
    Node<int>* node2 = new Node<int>(2);
    Node<int>* node3 = new Node<int>(3);

    head->next = node2;
    node2->next = node3;
    node3->next = node2;  // цикл 3 -> 2

    EXPECT_TRUE(check_cycle_turtle_rabbit(head));

    // Разрываем цикл перед удалением
    node3->next = nullptr;
    delete node3;
    delete node2;
    delete head;
}

TEST(CycleTest_TurtleRabbit, SingleElementCycle) {
    Node<int>* head = new Node<int>(1);
    head->next = head;  

    EXPECT_TRUE(check_cycle_turtle_rabbit(head));

    head->next = nullptr;
    delete head;
}

// Тесты для разворота указателей
TEST(CycleTest_ReversePointers, EmptyList) {
    Node<int>* head = nullptr;
    EXPECT_FALSE(check_cycle_with_reverse_pointers(head));
}
TEST(CycleTest_ReversePointers, NoCycle) {
    Node<int>* head = new Node<int>(1);
    Node<int>* node2 = new Node<int>(2);
    Node<int>* node3 = new Node<int>(3);

    head->next = node2;
    node2->next = node3;
    node3->next = nullptr;

    EXPECT_FALSE(check_cycle_with_reverse_pointers(head));

    // Проверяем восстановление структуры
    EXPECT_EQ(head->next, node2);
    EXPECT_EQ(node2->next, node3);
    EXPECT_EQ(node3->next, nullptr);

    delete node3;
    delete node2;
    delete head;
}
TEST(CycleTest_ReversePointers, SingleNodeSelfCycle) {
    Node<int>* head = new Node<int>(1);
    head->next = head;  // цикл

    EXPECT_TRUE(check_cycle_with_reverse_pointers(head));

    // После функции цикл должен быть разорван
    EXPECT_EQ(head->next, nullptr);
    delete head;
}
TEST(CycleTest_ReversePointers, WithCycleInMiddle) {
    Node<int>* head = new Node<int>(1);
    Node<int>* node2 = new Node<int>(2);
    Node<int>* node3 = new Node<int>(3);

    head->next = node2;
    node2->next = node3;
    node3->next = node2;  //цикл 3 -> 2

    EXPECT_TRUE(check_cycle_with_reverse_pointers(head));

    // Убедимся, что нет цикла, пройдя по списку
    Node<int>* current = head;
    int count = 0;
    while (current != nullptr && count < 10) {  
        current = current->next;
        count++;
    }
    if (count >= 10) {
        throw std::logic_error("Обнаружен возможный цикл. count = ");
    }
    head->next = nullptr;
    node2->next = nullptr;
    node3->next = nullptr;

    delete node3;
    delete node2;
    delete head;
}
// Тесты для поиска места поломки
TEST(CycleTest_FindNode, EmptyList) {
    Node<int>* head = nullptr;
    EXPECT_EQ(check_cycle_find_node(head), nullptr);
}

TEST(CycleTest_FindNode, NoCycle) {
    Node<int>* head = new Node<int>(1);
    head->next = new Node<int>(2);
    head->next->next = new Node<int>(3);

    EXPECT_EQ(check_cycle_find_node(head), nullptr);

    delete head->next->next;
    delete head->next;
    delete head;
}

TEST(CycleTest_FindNode, CycleAtBeginning) {
    Node<int>* head = new Node<int>(1);
    Node<int>* node2 = new Node<int>(2);
    Node<int>* node3 = new Node<int>(3);

    head->next = node2;
    node2->next = node3;
    node3->next = head;  

    Node<int>* cycleStart = check_cycle_find_node(head);
    EXPECT_NE(cycleStart, nullptr);
    EXPECT_EQ(cycleStart->value, 1);

    // Разрываем цикл
    node3->next = nullptr;
    delete node3;
    delete node2;
    delete head;
}

TEST(CycleTest_FindNode, CycleInMiddle) {
    Node<int>* head = new Node<int>(1);
    Node<int>* node2 = new Node<int>(2);
    Node<int>* node3 = new Node<int>(3);
    Node<int>* node4 = new Node<int>(4);

    head->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node2;  // цикл 4 -> 2

    Node<int>* cycleStart = check_cycle_find_node(head);
    EXPECT_NE(cycleStart, nullptr);
    EXPECT_EQ(cycleStart->value, 2);

    // Разрываем цикл
    node4->next = nullptr;
    delete node4;
    delete node3;
    delete node2;
    delete head;
}

TEST(CycleTest_FindNode, SelfCycle) {
    Node<int>* head = new Node<int>(1);
    head->next = head;  

    Node<int>* cycleStart = check_cycle_find_node(head);
    EXPECT_NE(cycleStart, nullptr);
    EXPECT_EQ(cycleStart->value, 1);

    head->next = nullptr;
    delete head;
}