#include <gtest/gtest.h>
#include "queue.h"

TEST(TestQueue, can_create_queue_with_default_size) {
    ASSERT_NO_THROW(Queue<int> queue);
}

TEST(TestQueue, can_create_queue_with_given_size) {
    ASSERT_NO_THROW(Queue<int> queue(50));
}

TEST(TestQueue, created_queue_is_empty) {
    Queue<int> queue;

    EXPECT_TRUE(queue.is_empty());
}

TEST(TestQueue, can_push_element) {
    Queue<int> queue;

    ASSERT_NO_THROW(queue.push(10));
}

TEST(TestQueue, push_increases_size) {
    Queue<int> queue;

    queue.push(10);

    EXPECT_EQ(queue.size(), 1);
}

TEST(TestQueue, can_pop_element) {
    Queue<int> queue;
    queue.push(10);

    ASSERT_NO_THROW(queue.pop());
}

TEST(TestQueue, pop_decreases_size) {
    Queue<int> queue;
    queue.push(10);
    queue.push(20);

    queue.pop();

    EXPECT_EQ(queue.size(), 1);
}

TEST(TestQueue, can_get_head_element) {
    Queue<int> queue;
    queue.push(42);

    ASSERT_NO_THROW(queue.head());
}

TEST(TestQueue, head_returns_correct_element) {
    Queue<int> queue;
    queue.push(42);
    queue.push(24);

    int result = queue.head();

    EXPECT_EQ(result, 42);
}

TEST(TestQueue, queue_follows_fifo_principle) {
    Queue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);

    EXPECT_EQ(queue.head(), 1);
    queue.pop();
    EXPECT_EQ(queue.head(), 2);
    queue.pop();
    EXPECT_EQ(queue.head(), 3);
}

TEST(TestQueue, can_clear_queue) {
    Queue<int> queue;
    queue.push(1);
    queue.push(2);

    queue.clear();

    EXPECT_TRUE(queue.is_empty());
}

TEST(TestQueue, is_full_works_correctly) {
    Queue<int> queue(2);
    queue.push(1);
    queue.push(2);

    EXPECT_TRUE(queue.is_full());
}

TEST(TestQueue, throw_when_pop_from_empty_queue) {
    Queue<int> queue;

    ASSERT_ANY_THROW(queue.pop());
}

TEST(TestQueue, throw_when_get_head_from_empty_queue) {
    Queue<int> queue;

    ASSERT_ANY_THROW(queue.head());
}

TEST(TestQueue, throw_when_push_to_full_queue) {
    Queue<int> queue(1);
    queue.push(1);

    ASSERT_ANY_THROW(queue.push(2));
}

TEST(TestQueue, can_push_and_pop) {
    Queue<int> queue(3);
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.pop();
    queue.pop();
    queue.push(4);
    queue.push(5);

    EXPECT_EQ(queue.head(), 3);
    queue.pop();
    EXPECT_EQ(queue.head(), 4);
    queue.pop();
    EXPECT_EQ(queue.head(), 5);
}

TEST(TestQueue, can_copy_queue) {
    Queue<int> original(5);
    original.push(1);
    original.push(2);

    Queue<int> copy(original);

    EXPECT_EQ(original.size(), copy.size());
    EXPECT_EQ(original.head(), copy.head());
}

TEST(TestQueue, can_assign_queue) {
    Queue<int> original(5);
    original.push(1);
    original.push(2);
    Queue<int> assigned(3);

    assigned = original;

    EXPECT_EQ(original.size(), assigned.size());
    EXPECT_EQ(original.head(), assigned.head());
}

TEST(TestQueue, copied_queue_is_independent) {
    Queue<int> original(5);
    original.push(1);
    original.push(2);

    Queue<int> copy(original);
    original.pop();

    EXPECT_NE(original.size(), copy.size());
    EXPECT_NE(original.head(), copy.head());
}

TEST(TestQueue, assigned_queue_is_independent) {
    Queue<int> original(5);
    original.push(1);
    original.push(2);
    Queue<int> assigned(3);

    assigned = original;
    original.pop();

    EXPECT_NE(original.size(), assigned.size());
    EXPECT_NE(original.head(), assigned.head());
}

TEST(TestQueue, can_handle_self_assignment) {
    Queue<int> queue(3);
    queue.push(1);
    queue.push(2);

    ASSERT_NO_THROW(queue = queue);
}

TEST(TestQueue, works_with_different_data_types) {
    Queue<std::string> stringQueue(2);

    stringQueue.push("hello");
    stringQueue.push("world");

    EXPECT_EQ(stringQueue.head(), "hello");
    stringQueue.pop();
    EXPECT_EQ(stringQueue.head(), "world");
}

TEST(TestQueue, size_returns_correct_value_after_multiple_operations) {
    Queue<int> queue(5);

    queue.push(1);
    EXPECT_EQ(queue.size(), 1);

    queue.push(2);
    EXPECT_EQ(queue.size(), 2);

    queue.pop();
    EXPECT_EQ(queue.size(), 1);

    queue.push(3);
    queue.push(4);
    EXPECT_EQ(queue.size(), 3);

    queue.clear();
    EXPECT_EQ(queue.size(), 0);
}

TEST(TestQueue, can_reuse_queue_after_clear) {
    Queue<int> queue(3);
    queue.push(1);
    queue.push(2);
    queue.clear();

    queue.push(10);
    queue.push(20);

    EXPECT_EQ(queue.size(), 2);
    EXPECT_EQ(queue.head(), 10);
    queue.pop();
    EXPECT_EQ(queue.head(), 20);
}