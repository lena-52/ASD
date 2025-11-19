#include <gtest/gtest.h>
#include <stdexcept>
#include "stack.h"
// Ňĺńňű äë˙ ęîíńňđóęňîđîâ
TEST(StackTest, DefaultConstructor) {
    Stack<int> stack;
    EXPECT_TRUE(stack.is_empty());
    EXPECT_EQ(stack.size(), 0);
}

TEST(StackTest, ParameterizedConstructor) {
    Stack<int> stack(50);
    EXPECT_TRUE(stack.is_empty());
    EXPECT_EQ(stack.size(), 0);
}

TEST(StackTest, CopyConstructor) {
    Stack<int> original;
    original.push(1);
    original.push(2);

    Stack<int> copy(original);
    EXPECT_EQ(original.size(), copy.size());
    EXPECT_EQ(original.top(), copy.top());
}

// Ňĺńňű äë˙ îďĺđŕňîđŕ ďđčńâŕčâŕíč˙
TEST(StackTest, AssignmentOperator) {
    Stack<int> stack1;
    stack1.push(10);
    stack1.push(20);

    Stack<int> stack2;
    stack2 = stack1;

    EXPECT_EQ(stack1.size(), stack2.size());
    EXPECT_EQ(stack1.top(), stack2.top());
}

TEST(StackTest, SelfAssignment) {
    Stack<int> stack;
    stack.push(5);
    stack = stack; 
    stack = stack; // self-assignment


    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.top(), 5);
}



// Ňĺńňű äë˙ push č top

TEST(StackTest, PushAndTop) {
    Stack<int> stack;
    stack.push(42);

    EXPECT_FALSE(stack.is_empty());
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.top(), 42);
}

TEST(StackTest, PushMultiple) {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    EXPECT_EQ(stack.top(), 3);
    EXPECT_EQ(stack.size(), 3);
}



// Ňĺńňű äë˙ pop

TEST(StackTest, PopOperation) {
    Stack<int> stack;
    stack.push(10);
    stack.push(20);

    EXPECT_EQ(stack.top(), 20);
    stack.pop();
    EXPECT_EQ(stack.top(), 10);
    EXPECT_EQ(stack.size(), 1);
}


// Ňĺńňű äë˙ is_empty č is_full

TEST(StackTest, IsEmpty) {
    Stack<int> stack;
    EXPECT_TRUE(stack.is_empty());

    stack.push(1);
    EXPECT_FALSE(stack.is_empty());

    stack.pop();
    EXPECT_TRUE(stack.is_empty());
}

TEST(StackTest, IsFull) {
    Stack<int> stack(2);
    EXPECT_FALSE(stack.is_full());

    stack.push(1);
    stack.push(2);
    EXPECT_TRUE(stack.is_full());
}



// Ňĺńňű äë˙ size

TEST(StackTest, Size) {
    Stack<int> stack;
    EXPECT_EQ(stack.size(), 0);

    stack.push(1);
    EXPECT_EQ(stack.size(), 1);

    stack.push(2);
    EXPECT_EQ(stack.size(), 2);

    stack.pop();
    EXPECT_EQ(stack.size(), 1);
}



// Ňĺńňű äë˙ clear

TEST(StackTest, Clear) {
    Stack<int> stack;
    stack.push(1);
    stack.push(2);

    stack.clear();
    EXPECT_TRUE(stack.is_empty());
    EXPECT_EQ(stack.size(), 0);
}



// Ňĺńňű äë˙ čńęëţ÷ĺíčé

TEST(StackTest, PopEmptyThrows) {
    Stack<int> stack;
    ASSERT_THROW(stack.pop(), std::logic_error);
}

TEST(StackTest, TopEmptyThrows) {
    Stack<int> stack;
    ASSERT_THROW(stack.top(), std::logic_error);
}

TEST(StackTest, PushFullThrows) {
    Stack<int> stack(1);
    stack.push(1);
    ASSERT_THROW(stack.push(2), std::logic_error);
}