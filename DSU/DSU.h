#pragma once
#include <stdexcept>

class DSU {
private:
    int* _rank;
    int* _parent;
    size_t _size;

public:
    DSU(size_t size);
    ~DSU();
    void unite(int x1, int x2);
    int find(int x);
};