#pragma once
#include "list.h"
#include <stdexcept>

template <class T>
class StackList {
private:
    List<T>* _list;
public:
    StackList() {
        _list = new List<T>();
    }

    StackList(const StackList& other) {
        _list = new List<T>(*other._list);
    }

    ~StackList() {
        delete _list;
        _list = nullptr;
    }

    StackList& operator=(const StackList& other) {
        if (this != &other) {
            delete _list;
            _list = new List<T>(*other._list);
        }
        return *this;
    }

    void push(const T& val);
    void pop();
    T& top();  
    const T& top() const;  
    bool is_empty() const noexcept;
    void clear() noexcept;
    size_t size() const noexcept; 
};

template <class T>
void StackList<T>::push(const T& val) {
    _list->push_front(val);
}

template <class T>
void StackList<T>::pop() {
    if (is_empty()) {
        throw std::logic_error("Stack is empty");
    }
    _list->pop_front();
}

template <class T>
T& StackList<T>::top() { 
    if (is_empty()) {
        throw std::logic_error("Stack is empty");
    }
    auto it = _list->begin();
    return *it; 

template <class T>
const T& StackList<T>::top() const {  
    if (is_empty()) {
        throw std::logic_error("Stack is empty");
    }
    auto it = _list->begin();
    return *it;
}

template <class T>
bool StackList<T>::is_empty() const noexcept {
    return _list->is_empty();
}

template <class T>
void StackList<T>::clear() noexcept {
    _list->clear();
}

template <class T>
size_t StackList<T>::size() const noexcept {  
 
    size_t count = 0;
    for (auto it = _list->begin(); it != _list->end(); ++it) {
        count++;
    }
    return count;
}

