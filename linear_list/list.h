#pragma once
#include <iostream>
#include <stdexcept>

template <class T>
class List {
    struct Node {
        T value;
        Node* next;
        Node(const T& value, Node* next = nullptr) : value(value), next(next) {}
    };

    Node* _head;
    Node* _tail;
    size_t _size;

public:
    class Iterator {
        Node* current;
    public:
        Iterator() : current(nullptr) {}
        Iterator(Node* pos) : current(pos) {}

        T& operator*() {
            if (current == nullptr) throw std::logic_error("null iterator");
            return current->value;
        }

        bool operator==(const Iterator& other) const { return current == other.current; }
        bool operator!=(const Iterator& other) const { return current != other.current; }

        Iterator operator++(int) {
            Iterator temp = *this;
            if (current != nullptr) current = current->next;
            return temp;
        }

        Iterator& operator++() {
            if (current != nullptr) current = current->next;
            return *this;
        }

    };

    List() : _head(nullptr), _tail(nullptr), _size(0) {}

    List(const List& other) : _head(nullptr), _tail(nullptr), _size(0) {
        Node* current = other._head;
        while (current != nullptr) {
            push_back(current->value);
            current = current->next;
        }
    }

    void clear() {
        while (_head != nullptr) {
            Node* temp = _head;
            _head = _head->next;
            delete temp;
        }
        _head = nullptr;
        _tail = nullptr;
        _size = 0;
    }

    List<T>& operator=(const List& other) {
        if (this != &other) {
            clear();

            Node* current = other._head;
            while (current != nullptr) {
                push_back(current->value);
                current = current->next;
            }
        }
        return *this;
    }

    ~List() {
        clear();
    }

    Iterator begin() { return Iterator(_head); }
    Iterator end() { return Iterator(nullptr); }

    void push_front(const T& val) {
        Node* node = new Node(val, _head);
        _head = node;
        if (_tail == nullptr) _tail = node;
        _size++;
    }

    void push_back(const T& val) {
        Node* node = new Node(val);
        if (_tail == nullptr) {
            _head = _tail = node;
        }
        else {
            _tail->next = node;
            _tail = node;
        }
        _size++;
    }

    void pop_front() {
        if (!_head) throw std::logic_error("Cannot pop from empty list");
        Node* temp = _head;
        _head = _head->next;
        if (!_head) _tail = nullptr;
        delete temp;
        _size--;
    }

    void pop_back() {
        if (!_head) throw std::logic_error("Cannot pop from empty list");
        if (_head == _tail) {
            delete _head;
            _head = _tail = nullptr;
        }
        else {
            Node* current = _head;
            while (current->next != _tail) current = current->next;
            delete _tail;
            _tail = current;
            _tail->next = nullptr;
        }
        _size--;
    }

    void insert(int pos, const T& val) {
        if (pos < 0 || pos > static_cast<int>(_size)) throw std::logic_error("Position out of range");
        if (pos == 0) {
            push_front(val);
        }
        else if (pos == static_cast<int>(_size)) {
            push_back(val);
        }
        else {
            Node* current = _head;
            for (int i = 0; i < pos - 1; i++) current = current->next;
            Node* new_node = new Node(val, current->next);
            current->next = new_node;
            _size++;
        }
    }

    void erase(Node* node) {
        if (node == nullptr || !_head) throw std::logic_error("Node cannot be null");
        if (node == _head) {
            pop_front();
            return;
        }
        Node* current = _head;
        while (current && current->next != node) current = current->next;
        if (!current) throw std::logic_error("Node not found in list");
        current->next = node->next;
        if (node == _tail) _tail = current;
        delete node;
        _size--;
    }

    bool is_empty() const { return _head == nullptr; }
    size_t size() const { return _size; }

    Node* find(const T& val) {
        Node* current = _head;
        while (current != nullptr) {
            if (current->value == val) return current;
            current = current->next;
        }
        return nullptr;
    }

    Node* get_head() { return _head; }
    const Node* get_head() const { return _head; }
    Node* get_tail() { return _tail; }
    const Node* get_tail() const { return _tail; }

    T& front() {
        if (!_head) throw std::logic_error("List is empty");
        return _head->value;
    }

    const T& front() const {
        if (!_head) throw std::logic_error("List is empty");
        return _head->value;
    }

    T& back() {
        if (!_tail) throw std::logic_error("List is empty");
        return _tail->value;
    }

    const T& back() const {
        if (!_tail) throw std::logic_error("List is empty");
        return _tail->value;
    }
};