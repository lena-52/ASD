#include "DSU.h"
#include <gtest/gtest.h>

TEST(DSUTest, ConstructorInitializesCorrectly) {
    DSU dsu(5);

    //  каждый элемент является родителем самого себя
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(dsu.find(i), i);
    }
}

TEST(DSUTest, UniteConnectsElements) {
    DSU dsu(5);

    dsu.unite(0, 1);
    dsu.unite(2, 3);

    EXPECT_EQ(dsu.find(0), dsu.find(1));
    EXPECT_EQ(dsu.find(2), dsu.find(3));
}

TEST(DSUTest, UnionByRank) {
    DSU dsu(6);

    dsu.unite(0, 1);
    dsu.unite(1, 2);  // дерево высоты 2
    dsu.unite(3, 4);  // дерево высоты 1

    // Объединяем - меньшее дерево должно присоединиться к большему
    dsu.unite(2, 4);

    EXPECT_EQ(dsu.find(0), dsu.find(3));
    EXPECT_EQ(dsu.find(1), dsu.find(4));
    EXPECT_EQ(dsu.find(2), dsu.find(3));
}

TEST(DSUTest, SelfUnion) {
    DSU dsu(3);

    dsu.unite(1, 1); // Объединение с самим собой

    EXPECT_EQ(dsu.find(1), 1);
}

TEST(DSUTest, MultipleUnionsStar) {
    DSU dsu(10);

    //  соединяем все элементы с центральным
    for (int i = 1; i < 10; i++) {
        dsu.unite(0, i);
    }

    //  все элементы должны иметь один корень
    int center_root = dsu.find(0);
    for (int i = 1; i < 10; i++) {
        EXPECT_EQ(dsu.find(i), center_root);
    }
}


TEST(DSUTest, OutOfBoundsAccess) {
    DSU dsu(3);

    EXPECT_THROW(dsu.find(-1), std::out_of_range);
    EXPECT_THROW(dsu.find(5), std::out_of_range);
}

TEST(DSUTest, WaysCompression) {
    DSU dsu(10);

    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(2, 3);
    dsu.unite(3, 4);

    int root = dsu.find(4); 

    // После сжатия пути все элементы должны иметь прямой доступ к корню
    EXPECT_EQ(dsu.find(0), root);
    EXPECT_EQ(dsu.find(1), root);
    EXPECT_EQ(dsu.find(2), root);
    EXPECT_EQ(dsu.find(3), root);
    EXPECT_EQ(dsu.find(4), root);
}