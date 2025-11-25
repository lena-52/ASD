#include <gtest/gtest.h>
#include "doubly_linked_list.h"

TEST(DoublyLinkedListTest, DefaultConstructor) {
    List<int> list;

    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);
    EXPECT_EQ(list.begin(), list.end());
}

TEST(DoublyLinkedListTest, PushFront) {
    List<int> list;

    list.push_front(3);
    EXPECT_EQ(list.front(), 3);
    EXPECT_EQ(list.back(), 3);
    EXPECT_EQ(list.size(), 1);
}

TEST(DoublyLinkedListTest, PushBack) {
    List<int> list;

    list.push_back(1);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 1);
    EXPECT_EQ(list.size(), 1);
}

TEST(DoublyLinkedListTest, PopFront) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_front();
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.size(), 2);
}

TEST(DoublyLinkedListTest, PopBack) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_back();
    EXPECT_EQ(list.back(), 2);
    EXPECT_EQ(list.size(), 2);

}

TEST(DoublyLinkedListTest, InsertByPosition) {
    List<int> list;
    list.push_back(1);
    list.push_back(3);

    list.insert(1, 2);

    EXPECT_EQ(list.size(), 3);

    List<int>::Iterator it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
}
TEST(DoublyLinkedListTest, InsertByNode) {
    List<int> list;
    list.push_back(1);
    list.push_back(3);

    Node<int>* first = list.get_head();
    list.insert(first, 2); 

    EXPECT_EQ(list.size(), 3);

    List<int>::Iterator it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
}

TEST(DoublyLinkedListTest, EraseNode) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    Node<int>* middle = list.find(2);
    list.erase(middle);

    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);
}

TEST(DoublyLinkedListTest, Clear) {
    List<int> list;
    list.push_back(1);

    list.clear();

    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);
    EXPECT_EQ(list.begin(), list.end());
}

TEST(DoublyLinkedListTest, Find) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    Node<int>* found = list.find(2);
    EXPECT_NE(found, nullptr);
    EXPECT_EQ(found->value, 2);

    Node<int>* not_found = list.find(5);
    EXPECT_EQ(not_found, nullptr);
}

TEST(DoublyLinkedListTest, CopyConstructor) {
    List<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    List<int> copy(original);

    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy.front(), 1);
    EXPECT_EQ(copy.back(), 3);

    original.pop_front();
    EXPECT_EQ(copy.front(), 1); 
    EXPECT_EQ(copy.size(), 3);
}

TEST(DoublyLinkedListTest, AssignmentOperator) {
    List<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    List<int> copy;
    copy = original;

    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy.front(), 1);
    EXPECT_EQ(copy.back(), 3);

    original.pop_front();
    EXPECT_EQ(copy.front(), 1); 
    EXPECT_EQ(copy.size(), 3);
}

TEST(DoublyLinkedListTest, IteratorForward) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    List<int>::Iterator it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(it, list.end());
}

TEST(DoublyLinkedListTest, IteratorBackward) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    List<int>::Iterator it = list.begin();
    ++it; 
    ++it; 

    --it;
    EXPECT_EQ(*it, 2);
    --it;
    EXPECT_EQ(*it, 1);
}

TEST(DoublyLinkedListTest, IteratorPostIncrement) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    List<int>::Iterator it = list.begin();
    List<int>::Iterator old_it = it++;

    EXPECT_EQ(*old_it, 1);
    EXPECT_EQ(*it, 2);
}

TEST(DoublyLinkedListTest, IteratorPostDecrement) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    List<int>::Iterator it = list.begin();
    ++it; 
    List<int>::Iterator old_it = it--;

    EXPECT_EQ(*old_it, 2);
    EXPECT_EQ(*it, 1);
}


TEST(DoublyLinkedListTest, RangeBasedForLoop) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    int sum = 0;
    for (const int& value : list) {
        sum += value;
    }

    EXPECT_EQ(sum, 6);
}

TEST(DoublyLinkedListTest, FrontBackAccess) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 2);

    list.front() = 10;
    list.back() = 20;

    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 20);
}

TEST(DoublyLinkedListTest, EmptyListOperations) {
    List<int> list;

    EXPECT_THROW(list.pop_front(), std::logic_error);
    EXPECT_THROW(list.pop_back(), std::logic_error);
    EXPECT_THROW(list.front(), std::logic_error);
    EXPECT_THROW(list.back(), std::logic_error);
}

TEST(DoublyLinkedListTest, InsertInvalidPosition) {
    List<int> list;
    list.push_back(1);

    EXPECT_THROW(list.insert(-1, 0), std::logic_error);
    EXPECT_THROW(list.insert(5, 0), std::logic_error);
}

TEST(DoublyLinkedListTest, ComplexOperations) {
    List<int> list;

    list.push_front(3);
    list.push_back(4);
    list.push_front(2);
    list.push_back(5);
    list.push_front(1);

    EXPECT_EQ(list.size(), 5);

    // 1, 2, 3, 4, 5
    auto it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(*it, 4);
    ++it;
    EXPECT_EQ(*it, 5);
}