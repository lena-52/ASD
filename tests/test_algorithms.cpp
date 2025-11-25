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



//тесты для 1й функции заяц-черепахаха
TEST(CycleTest, EmptyList) {
    Node<int>* head = nullptr;
    EXPECT_FALSE(check_cycle(head));
}

TEST(CycleTest, NoCycle) {
    Node<int>* head = new Node<int>(1);
    head->next = new Node<int>(2);
    head->next->next = new Node<int>(3);

    EXPECT_FALSE(check_cycle(head));

    delete head->next->next;
    delete head->next;
    delete head;
}

TEST(CycleTest, WithCycle) {
    Node<int>* head = new Node<int>(1);
    Node<int>* node2 = new Node<int>(2);
    Node<int>* node3 = new Node<int>(3);

    head->next = node2;
    node2->next = node3;
    node3->next = node2;  // цикл: 3 -> 2

    EXPECT_TRUE(check_cycle(head));

    // Разрываем цикл перед удалением
    node3->next = nullptr;
    delete head;
    delete node2;
    delete node3;
}

TEST(CycleTest, SingleElementCycle) {
    Node<int>* head = new Node<int>(1);
    head->next = head;  // цикл на себя

    EXPECT_TRUE(check_cycle(head));

    head->next = nullptr;
    delete head;
}