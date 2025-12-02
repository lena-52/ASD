#include <gtest/gtest.h>
#include "list.h"
#include <sstream>

// Тест 1: Создание пустого списка
TEST(ListTest, DefaultConstructor) {
    List<int> list;

    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);

    // Проверка итераторов для пустого списка
    EXPECT_EQ(list.begin(), list.end());
}

// Тест 2: Конструктор копирования
TEST(ListTest, CopyConstructor) {
    List<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);

    List<int> copy(original);

    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy.front(), 1);
    EXPECT_EQ(copy.back(), 3);
    EXPECT_FALSE(copy.is_empty());

    // Проверяем, что это действительно глубокая копия
    original.pop_back();
    EXPECT_EQ(original.size(), 2);
    EXPECT_EQ(copy.size(), 3); // Копия не должна измениться
}

// Тест 3: Оператор присваивания
TEST(ListTest, AssignmentOperator) {
    List<int> original;
    original.push_back(10);
    original.push_back(20);
    original.push_back(30);

    List<int> copy;
    copy = original;

    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy.front(), 10);
    EXPECT_EQ(copy.back(), 30);

    // Проверка само-присваивания
    copy = copy;
    EXPECT_EQ(copy.size(), 3);
}

// Тест 4: Push front и push back
TEST(ListTest, PushFrontAndBack) {
    List<int> list;

    list.push_front(3);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 3);
    EXPECT_EQ(list.back(), 3);

    list.push_front(2);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.back(), 3);

    list.push_back(4);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.back(), 4);

    list.push_back(5);
    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.back(), 5);
}

// Тест 5: Pop front и pop back
TEST(ListTest, PopFrontAndBack) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    list.pop_front();
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.back(), 4);

    list.pop_back();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.back(), 3);

    list.pop_front();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 3);
    EXPECT_EQ(list.back(), 3);

    list.pop_back();
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);
}

// Тест 6: Исключения при pop на пустом списке
TEST(ListTest, PopEmptyListThrows) {
    List<int> list;

    EXPECT_THROW(list.pop_front(), std::logic_error);
    EXPECT_THROW(list.pop_back(), std::logic_error);
}

// Тест 7: Вставка по позиции
TEST(ListTest, InsertAtPosition) {
    List<int> list;
    list.push_back(1);
    list.push_back(3); // Список: [1, 3]

    // Вставка в середину
    list.insert(1, 2); // Должно стать: [1, 2, 3]
    EXPECT_EQ(list.size(), 3);

    // Проверяем последовательность через итератор
    auto it = list.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);

    // Вставка в начало
    list.insert(0, 0); // Должно стать: [0, 1, 2, 3]
    EXPECT_EQ(list.size(), 4);
    EXPECT_EQ(list.front(), 0);

    // Вставка в конец
    list.insert(4, 4); // Должно стать: [0, 1, 2, 3, 4]
    EXPECT_EQ(list.size(), 5);
    EXPECT_EQ(list.back(), 4);
}

// Тест 8: Исключения при некорректной позиции вставки
TEST(ListTest, InsertInvalidPositionThrows) {
    List<int> list;
    list.push_back(1);

    EXPECT_THROW(list.insert(-1, 0), std::logic_error);
    EXPECT_THROW(list.insert(10, 0), std::logic_error);
}

// Тест 9: Удаление узла через find
TEST(ListTest, EraseNode) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    // Находим и удаляем узел со значением 3
    auto node = list.find(3);
    ASSERT_NE(node, nullptr);
    list.erase(node);

    EXPECT_EQ(list.size(), 4);

    // Проверяем, что 3 действительно удалено
    std::stringstream ss;
    for (auto it = list.begin(); it != list.end(); ++it) {
        ss << *it << " ";
    }
    EXPECT_EQ(ss.str(), "1 2 4 5 ");
}

// Тест 10: Удаление головы через erase
TEST(ListTest, EraseHead) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto head = list.find(1);
    list.erase(head);

    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.back(), 3);
}

// Тест 11: Удаление хвоста через erase
TEST(ListTest, EraseTail) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto tail = list.find(3);
    list.erase(tail);

    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 2);
}

// Тест 12: Исключения при удалении nullptr
TEST(ListTest, EraseNullptrThrows) {
    List<int> list;
    list.push_back(1);

    EXPECT_THROW(list.erase(nullptr), std::logic_error);
}

// Тест 13: Поиск элементов
TEST(ListTest, FindElements) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);

    auto found = list.find(20);
    EXPECT_NE(found, nullptr);

    auto notFound = list.find(50);
    EXPECT_EQ(notFound, nullptr);
}

// Тест 14: Очистка списка
TEST(ListTest, ClearList) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.clear();

    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);
    EXPECT_EQ(list.begin(), list.end());

    // После очистки можно снова добавлять элементы
    list.push_back(10);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 10);
}

// Тест 15: Исключения при доступе к front/back пустого списка
TEST(ListTest, FrontBackEmptyListThrows) {
    List<int> list;

    EXPECT_THROW(list.front(), std::logic_error);
    EXPECT_THROW(list.back(), std::logic_error);

    const List<int>& constList = list;
    EXPECT_THROW(constList.front(), std::logic_error);
    EXPECT_THROW(constList.back(), std::logic_error);
}

// Тест 16: Константные методы front и back
TEST(ListTest, ConstFrontBack) {
    List<int> list;
    list.push_back(100);
    list.push_back(200);

    const List<int>& constList = list;

    EXPECT_EQ(constList.front(), 100);
    EXPECT_EQ(constList.back(), 200);
}

// Тест 17: Итераторы - чтение значений
TEST(ListIteratorTest, ReadValues) {
    List<int> list;
    for (int i = 1; i <= 5; i++) {
        list.push_back(i * 10);
    }

    std::stringstream ss;
    for (auto it = list.begin(); it != list.end(); ++it) {
        ss << *it << " ";
    }
    EXPECT_EQ(ss.str(), "10 20 30 40 50 ");
}

// Тест 18: Итераторы - запись значений
TEST(ListIteratorTest, WriteValues) {
    List<int> list;
    for (int i = 0; i < 3; i++) {
        list.push_back(0);
    }

    int value = 1;
    for (auto it = list.begin(); it != list.end(); ++it) {
        *it = value * 100;
        value++;
    }

    std::stringstream ss;
    for (auto it = list.begin(); it != list.end(); ++it) {
        ss << *it << " ";
    }
    EXPECT_EQ(ss.str(), "100 200 300 ");
}

// Тест 19: Итераторы - post-increment
TEST(ListIteratorTest, PostIncrement) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    auto it = list.begin();
    auto old_it = it++;

    EXPECT_EQ(*old_it, 1);
    EXPECT_EQ(*it, 2);

    old_it = it++;
    EXPECT_EQ(*old_it, 2);
    EXPECT_EQ(*it, 3);
}

// Тест 20: Итераторы - сравнение
TEST(ListIteratorTest, IteratorComparison) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    auto it1 = list.begin();
    auto it2 = list.begin();
    auto end = list.end();

    EXPECT_EQ(it1, it2);
    EXPECT_NE(it1, end);

    ++it1;
    EXPECT_NE(it1, it2);

    ++it2;
    EXPECT_EQ(it1, it2);
}

// Тест 21: Итераторы пустого списка
TEST(ListIteratorTest, EmptyListIterators) {
    List<int> list;

    auto begin = list.begin();
    auto end = list.end();

    EXPECT_EQ(begin, end);

    // Инкремент не должен приводить к ошибке
    ++begin;
    begin++;
    EXPECT_EQ(begin, end);
}

// Тест 22: Range-based for loop
TEST(ListTest, RangeBasedForLoop) {
    List<int> list;
    for (int i = 1; i <= 3; i++) {
        list.push_back(i * 5);
    }

    int sum = 0;
    for (int value : list) {
        sum += value;
    }

    EXPECT_EQ(sum, 30); // 5 + 10 + 15 = 30
}

// Тест 23: Перемещение между элементами с помощью итератора
TEST(ListIteratorTest, IteratorTraversal) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    auto it = list.begin();
    EXPECT_EQ(*it, 1);

    ++it;
    EXPECT_EQ(*it, 2);

    it++;
    EXPECT_EQ(*it, 3);

    ++it;
    EXPECT_EQ(*it, 4);

    it++;
    EXPECT_EQ(*it, 5);

    ++it;
    EXPECT_EQ(it, list.end());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}