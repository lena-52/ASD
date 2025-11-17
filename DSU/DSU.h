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

DSU::DSU(size_t size) : _size(size) {
    _rank = new int[size];
    _parent = new int[size];
    for (size_t i = 0; i < _size; i++) {
        _parent[i] = i;
        _rank[i] = 0;
    }
}

DSU::~DSU() {
    delete[] _rank;
    delete[] _parent;
}

void DSU::unite(int x1, int x2) {
    int rank_x1 = find(x1);
    int rank_x2 = find(x2);

    if (_rank[rank_x1] < _rank[rank_x2]) {
        _parent[rank_x1] = rank_x2;
    }
    else if (_rank[rank_x1] > _rank[rank_x2]) {
        _parent[rank_x2] = rank_x1;
    }
    else {
        _parent[rank_x2] = rank_x1;
        _rank[rank_x1]++;
    }
}

int DSU::find(int x) {
    if (x < 0 || x >= _size) {
        throw std::out_of_range("Index out of bounds");
    }

    if (_parent[x] != x) {
        _parent[x] = find(_parent[x]);
    }
    return _parent[x];
}
