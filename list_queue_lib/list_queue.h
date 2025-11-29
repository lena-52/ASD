
#include <stdexcept>
#include "list.h"

template <class T>
class ListQueue {
private:
    List<T> _list;
public:
    ListQueue() = default;
    void push(const T& value);
    void pop();
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    bool is_empty() const;
    void clear();
    int size() const;
};

template <class T>
void ListQueue<T>::push(const T& value) {
    _list.push_back(value);
}
template <class T>
void ListQueue<T>::pop() {
    if (is_empty()) {
        throw std::logic_error("Queue is empty");
    }
    _list.pop_front();
}

template <class T>
T& ListQueue<T>::front() {
    if (is_empty()) {
        throw std::logic_error("Queue is empty");
    }
    return _list.front();
}

template <class T>
const T& ListQueue<T>::front() const {
    if (is_empty()) {
        throw std::logic_error("Queue is empty");
    }
    return _list.front();
}
template <class T>
T& ListQueue<T>::back() {
    if (is_empty()) {
        throw std::logic_error("Queue is empty");
    }
    return _list.back();
}

template <class T>
const T& ListQueue<T>::back() const {
    if (is_empty()) {
        throw std::logic_error("Queue is empty");
    }
    return _list.back();
}

template <class T>
bool ListQueue<T>::is_empty() const {
    return _list.is_empty();
}

template <class T>
void ListQueue<T>::clear() {
    _list.clear();
}

template <class T>
int ListQueue<T>::size() const {
    return _list.size();
}
