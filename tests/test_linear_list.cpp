#include <gtest/gtest.h>
#include "list.h"

TEST(ListTest, BasicTest) {
    List<int> list;
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);

}



    list.push_back(1);
    EXPECT_FALSE(list.is_empty());
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 1);

    EXPECT_EQ(list.back(), 2);
}

TEST(TestList, can_pop_front) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);

    ASSERT_NO_THROW(list.pop_front());
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 20);
    EXPECT_EQ(list.back(), 20);
}

TEST(TestList, can_pop_back) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);

    ASSERT_NO_THROW(list.pop_back());
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 10);
}

TEST(TestList, pop_front_on_empty_list_throws) {
    List<int> list;
    EXPECT_THROW(list.pop_front(), std::logic_error);
}

TEST(TestList, pop_back_on_empty_list_throws) {
    List<int> list;
    EXPECT_THROW(list.pop_back(), std::logic_error);
}

TEST(TestList, can_insert_at_position) {
    List<int> list;
    list.push_back(10);
    list.push_back(30);

    ASSERT_NO_THROW(list.insert(1, 20));
    EXPECT_EQ(list.size(), 3);

    // ��������� ������������������
    auto it = list.begin();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
    ++it;
    EXPECT_EQ(*it, 30);
}

TEST(TestList, insert_at_invalid_position_throws) {
    List<int> list;
    list.push_back(10);

    EXPECT_THROW(list.insert(-1, 0), std::logic_error);
    EXPECT_THROW(list.insert(5, 0), std::logic_error);
}

TEST(TestList, can_erase_by_value) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    // ������� ���� ����� find � ������� ���
    auto node = list.find(20);
    ASSERT_NE(node, nullptr);
    ASSERT_NO_THROW(list.erase(node));
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 30);
}

TEST(TestList, erase_head_node_works) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);

    auto head = list.find(10);
    ASSERT_NO_THROW(list.erase(head));
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 20);
}

TEST(TestList, erase_tail_node_works) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);

    auto tail = list.find(20);
    ASSERT_NO_THROW(list.erase(tail));
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 10);
}

TEST(TestList, erase_null_node_throws) {
    List<int> list;
    EXPECT_THROW(list.erase(nullptr), std::logic_error);
}

TEST(TestList, can_find_element) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    auto found = list.find(20);
    EXPECT_NE(found, nullptr);

    auto not_found = list.find(40);
    EXPECT_EQ(not_found, nullptr);
}

TEST(TestList, copy_constructor_works) {
    List<int> original;
    original.push_back(10);
    original.push_back(20);
    original.push_back(30);

    List<int> copy(original);
    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy.front(), 10);
    EXPECT_EQ(copy.back(), 30);
}

TEST(TestList, assignment_operator_works) {
    List<int> original;
    original.push_back(10);
    original.push_back(20);

    List<int> copy;
    copy = original;
    EXPECT_EQ(copy.size(), 2);
    EXPECT_EQ(copy.front(), 10);
    EXPECT_EQ(copy.back(), 20);
}

TEST(TestList, self_assignment_works) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);

    list = list;
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 20);
}

TEST(TestList, can_clear_list) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    ASSERT_NO_THROW(list.clear());
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(TestList, destructor) {
    List<int>* list = new List<int>();
    list->push_back(10);
    list->push_back(20);
    list->push_back(30);

    ASSERT_NO_THROW(delete list);
}

TEST(TestList, front_and_back_on_empty_list_throw) {
    List<int> list;
    EXPECT_THROW(list.front(), std::logic_error);
    EXPECT_THROW(list.back(), std::logic_error);
}

// ����������� �����
TEST(ListIterator, ReadOperations) {
    List<int> list;
    for (int i = 0; i < 5; i++) {
        list.push_back(i * 2 + 1);
    }

    int expected[] = { 1, 3, 5, 7, 9 };
    int index = 0;
    for (auto it = list.begin(); it != list.end(); it++) {
        EXPECT_EQ(*it, expected[index]);
        index++;
    }
    EXPECT_EQ(index, 5);
}

TEST(ListIterator, IterateEmptyList) {
    List<int> list;

    int count = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        count++;
    }
    EXPECT_EQ(count, 0);

    auto it = list.begin();
    auto it2 = it++;
    EXPECT_EQ(it, list.end());
    EXPECT_EQ(it2, list.begin());
}

TEST(ListIterator, WriteOperations) {
    List<int> list;
    for (int i = 0; i < 3; i++) {
        list.push_back(0);
    }

    int value = 10;
    for (auto it = list.begin(); it != list.end(); ++it) {
        *it = value;
        value += 5;
    }

    int expected[] = { 10, 15, 20 };
    int index = 0;
    for (auto it = list.begin(); it != list.end(); it++) {
        EXPECT_EQ(*it, expected[index]);
        index++;
    }

    EXPECT_EQ(list.back(), 1);

    list.push_front(0);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 0);
    EXPECT_EQ(list.back(), 1);
}

TEST(ListTest, CopyTest) {
    List<int> list1;
    list1.push_back(1);
    list1.push_back(2);

    List<int> list2 = list1;
    EXPECT_EQ(list2.size(), 2);
    EXPECT_EQ(list2.front(), 1);
    EXPECT_EQ(list2.back(), 2);

}