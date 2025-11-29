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

