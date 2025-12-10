#pragma once
#include "list.h"
#include <stdexcept>

template <class T>
class StackList {
private:
    List<T> _list;
public:
    StackList() = default;
    StackList(const StackList& other) : _list(other._list) {}
    ~StackList() = default;

    StackList& operator=(const StackList& other) {
        if (this != &other) {
            _list = other._list;
        }
        return *this;
    }

    void push(const T& val) {
        _list.push_front(val);
    }

    void pop() {
        if (is_empty()) {
            throw std::logic_error("Stack is empty");
        }
        _list.pop_front();
    }

    T& top() {
        if (is_empty()) {
            throw std::logic_error("Stack is empty");
        }
        return _list.front();
    }

    const T& top() const {
        if (is_empty()) {
            throw std::logic_error("Stack is empty");
        }
        return _list.front();
    }

    bool is_empty() const noexcept {
        return _list.is_empty();
    }

    void clear() noexcept {
        _list.clear();
    }

    size_t size() const noexcept {
        return _list.size();
    }
};