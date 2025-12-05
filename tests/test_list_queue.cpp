
#include <gtest/gtest.h>
#include "list_queue.h"  

TEST(ListQueueTest, DefaultConstructor) {
    ListQueue<int> queue;

    EXPECT_TRUE(queue.is_empty());
    EXPECT_EQ(queue.size(), 0);
}

TEST(ListQueueTest, PushAndFrontBack) {
    ListQueue<int> queue;

    queue.push(10);
    EXPECT_FALSE(queue.is_empty());
    EXPECT_EQ(queue.size(), 1);
    EXPECT_EQ(queue.front(), 10);
    EXPECT_EQ(queue.back(), 10);

    queue.push(20);
    queue.push(30);
    EXPECT_EQ(queue.size(), 3);
    EXPECT_EQ(queue.front(), 10);  
    EXPECT_EQ(queue.back(), 30);  
}

TEST(ListQueueTest, Pop) {
    ListQueue<int> queue;
    queue.push(10);
    queue.push(20);
    queue.push(30);

    queue.pop();
    EXPECT_EQ(queue.size(), 2);
    EXPECT_EQ(queue.front(), 20);  

    queue.pop();
    EXPECT_EQ(queue.size(), 1);
    EXPECT_EQ(queue.front(), 30); 
    EXPECT_EQ(queue.back(), 30);  

    queue.pop();
    EXPECT_TRUE(queue.is_empty());
    EXPECT_EQ(queue.size(), 0);
}

TEST(ListQueueTest, ConstMethods) {
    ListQueue<int> queue;
    queue.push(42);
    queue.push(100);

    const ListQueue<int>& const_queue = queue;
    EXPECT_EQ(const_queue.front(), 42);
    EXPECT_EQ(const_queue.back(), 100);
    EXPECT_EQ(const_queue.size(), 2);
    EXPECT_FALSE(const_queue.is_empty());
}

TEST(ListQueueTest, Clear) {
    ListQueue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);

    queue.clear();
    EXPECT_TRUE(queue.is_empty());
    EXPECT_EQ(queue.size(), 0);
}

TEST(ListQueueTest, EmptyQueueThrows) {
    ListQueue<int> queue;

    EXPECT_THROW(queue.pop(), std::logic_error);
    EXPECT_THROW(queue.front(), std::logic_error);
    EXPECT_THROW(queue.back(), std::logic_error);

    const ListQueue<int>& const_queue = queue;
    EXPECT_THROW(const_queue.front(), std::logic_error);
    EXPECT_THROW(const_queue.back(), std::logic_error);
}

TEST(ListQueueTest, OrderCorrect) {
    ListQueue<int> queue;

    // Добавляем элементы в порядке 1, 2, 3
    queue.push(1);
    queue.push(2);
    queue.push(3);

    // Должны извлекаться в том же порядке: 1, 2, 3
    EXPECT_EQ(queue.front(), 1);
    queue.pop();

    EXPECT_EQ(queue.front(), 2);
    queue.pop();

    EXPECT_EQ(queue.front(), 3);
    queue.pop();

    EXPECT_TRUE(queue.is_empty());
}