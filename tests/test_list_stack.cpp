#include <gtest/gtest.h>
#include "list_stack.h"
#include "list.h"
TEST(StackListTest, DefaultConstructor) {
    StackList<int> stack;

    EXPECT_TRUE(stack.is_empty());
    EXPECT_EQ(stack.size(), 0);
}

TEST(StackListTest, CopyConstructorAndAssignment) {
    StackList<int> stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);

    StackList<int> stack2(stack1); 
    EXPECT_EQ(stack2.size(), 3);
    EXPECT_EQ(stack2.top(), 3);

    StackList<int> stack3;
    stack3 = stack1; 
    EXPECT_EQ(stack3.size(), 3);
    EXPECT_EQ(stack3.top(), 3);
}

TEST(StackListTest, PushAndTopWork) {
    StackList<int> stack;

    stack.push(10);
    EXPECT_FALSE(stack.is_empty());
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.top(), 10);

    stack.push(20);
    EXPECT_EQ(stack.size(), 2);
    EXPECT_EQ(stack.top(), 20);
}

TEST(StackListTest, Pop) {
    StackList<int> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    stack.pop();
    EXPECT_EQ(stack.size(), 2);
    EXPECT_EQ(stack.top(), 20);

    stack.pop();
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.top(), 10);

    stack.pop();
    EXPECT_TRUE(stack.is_empty());
    EXPECT_EQ(stack.size(), 0);
}

TEST(StackListTest, Clear) {
    StackList<int> stack;
    stack.push(1);
    stack.push(2);

    stack.clear();
    EXPECT_TRUE(stack.is_empty());
    EXPECT_EQ(stack.size(), 0);
}

TEST(StackListTest, ConstMethods) {
    StackList<int> stack;
    stack.push(42);
    stack.push(100);

    const StackList<int>& const_stack = stack;
    EXPECT_EQ(const_stack.top(), 100);
    EXPECT_EQ(const_stack.size(), 2);
    EXPECT_FALSE(const_stack.is_empty());
}

TEST(StackListTest, EmptyStackThrows) {
    StackList<int> stack;

    EXPECT_THROW(stack.pop(), std::logic_error);
    EXPECT_THROW(stack.top(), std::logic_error);

    const StackList<int>& const_stack = stack;
    EXPECT_THROW(const_stack.top(), std::logic_error);
}

TEST(StackListTest, SelfAssignmentWorks) {
    StackList<int> stack;
    stack.push(1);
    stack.push(2);

    stack = stack;

    EXPECT_EQ(stack.size(), 2);
    EXPECT_EQ(stack.top(), 2);
}