#pragma once
#include <iostream>

template <class T>
class List {
    struct Node { //для описания 1 элемента
        T value;
        Node* next;
        Node(const T& value, Node* next = nullptr) : value(value), next(next) {}
    };

    Node* _head; //указатель на верх массива
    size_t _size; 
    Node* _tail;

public:
    class Iterator {
        Node* current;
    public:
        Iterator() : current(nullptr) {}
        Iterator(Node* pos) : current(pos) {}
        Iterator(const Iterator& other) : current(other.current) {}

        Iterator& operator=(const Iterator& other) {
            if (this != &other) {
                current = other.current;
            }
            return *this;
        }

        T& operator*() {
            if (current == nullptr) {
                throw std::logic_error("null iterator");
            }
            return current->value;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;

        }
        Iterator operator++(int) { //x++
            Iterator temp = *this;
            if (current != nullptr) {
                current = current->next;
            }
            return temp;
        }
        Iterator& operator++() { //++x
            if (current != nullptr) {
                current = current->next;
            }
            return *this;
        }


    };
    Iterator begin() {
        return Iterator(_head); 
    }

    Iterator end() {
        return Iterator(nullptr);
    }

    List();
    List(const List& other); //идти по оригинальному массиву и создавать копии элементов 
    List& operator=(const List& other);
    ~List();

    void push_front(const T& val) noexcept;
    void push_back(const T& val) noexcept;
    void insert(int pos, const T& val); //удобно пользователю
    void insert(Node* node, const T& val); //эффективно
    void pop_front();
    void pop_back();
    void erase(Node* node);
    void clear();

    bool is_empty() const;
    size_t size() const;
    Node* find(const T& val);
    Node* get_head() const;
    Node* get_tail() const;
    T& front();
    T& back();
    const T& front() const;
    const T& back() const;
};

template <class T>
List<T>::List() : _head(nullptr), _tail(nullptr), _size(0) {}

template <class T>
List<T>::List(const List& other) : _head(nullptr), _size(0), _tail(nullptr) {
    Node* current = other._head;
    while (current != nullptr) {
        push_back(current->value);
        current = current->next;
    }
}

template <class T>
List<T>& List<T>::operator=(const List& other) {
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

template <class T>
List<T>::~List() {
    clear();
}

template <class T>
void List<T>::push_front(const T& val) noexcept {
    Node* node = new Node(val, _head); //создали звено, которое указывает на head
    _head = node;
    if (_tail == nullptr) { //если список пустой
        _tail = node;
    }
    _size++;
}

template <class T>
void List<T>::push_back(const T& val) noexcept {
    Node* node = new Node(val);
    if (is_empty()) {
        _head = node;
        _tail = node;
    }
    else {
        _tail->next = node; // текущий хвост указывает на новый узел
        _tail = node; // новый узел становится хвостом
    }
    _size++;
}

template <class T>
void List<T>::insert(int pos, const T& val) {
    if (pos < 0 || pos >  _size) {
        throw std::logic_error("Position out of range");
    }

    if (pos == 0) {
        push_front(val);
    }
    else if (pos == _size) {
        push_back(val);
    }
    else {
        Node* current = _head;
        for (int i = 0; i < pos - 1; i++) { // ищем узел перед позицией вставки
            current = current->next;
        }
        insert(current, val);
    }
}
// Вставка после указанного узла
template <class T>
void List<T>::insert(Node* node, const T& val) {
    if (node == nullptr) {
        throw std::logic_error("Node cannot be null");
    }
    Node* new_node = new Node(val, node->next); // создаем новый узел
    node->next = new_node; // связываем 
    if (_tail == node) { // если вставляем после хвоста
        _tail = new_node;
    }
    _size++;
}

template <class T>
void List<T>::pop_front() {
    if (is_empty()) {
        throw std::logic_error("Cannot pop from empty list");
    }
    Node* temp = _head; // сохраняем указатель на удаляемый узел
    _head = _head->next; // перемещаем голову на следующий узел
    if (_head == nullptr) { // если список стал пустым
        _tail = nullptr;
    }
    delete temp;
    _size--;
}

template <class T>
void List<T>::pop_back() {
    if (is_empty()) {
        throw std::logic_error("Cannot pop from empty list");
    }

    if (_head == _tail) {
        delete _head;
        _head = nullptr;
        _tail = nullptr;
    }
    else {
        Node* current = _head;
        while (current->next != _tail) { // ищем предпоследний узел
            current = current->next;
        }
        delete _tail;
        _tail = current; // предпоследний узел становится хвостом
        _tail->next = nullptr; _tail->next = nullptr; // обнуляем указатель следующего
    }
    _size--;
}

template <class T>
void List<T>::erase(Node* node) {
    if (node == nullptr || is_empty()) {
        throw std::logic_error("Node cannot be null");
    }

    if (node == _head) { // если удаляем голову
        pop_front();
        return;
    }

    Node* current = _head;
    while (current != nullptr && current->next != node) { // ищем узел перед удаляемым
        current = current->next;
    }

    if (current == nullptr) { // если узел не найден
        throw std::logic_error("Node not found in list");
    }

    current->next = node->next; // связываем узлы вокруг удаляемого
    if (node == _tail) {
        _tail = current;
    }
    delete node;
    _size--;
}

template <class T>
void List<T>::clear() {
    while (!is_empty()) {
        pop_front();
    }
}

template <class T>
bool List<T>::is_empty() const {
    return _head == nullptr;
}

template <class T>
size_t List<T>::size() const {
    return _size;
}

template <class T>
typename List<T>::Node* List<T>::find(const T& val) {
    Node* current = _head;
    while (current != nullptr) {
        if (current->value == val) {
            return current;
        }
        current = current->next;
    }
    return nullptr; // если не нашли
}

template <class T>
typename List<T>::Node* List<T>::get_head() const {
    return _head;
}

template <class T>
typename List<T>::Node* List<T>::get_tail() const {
    return _tail;
}

template <class T>
T& List<T>::front() {
    if (is_empty()) {
        throw std::logic_error("List is empty");
    }
    return _head->value;
}

template <class T>
T& List<T>::back() {
    if (is_empty()) {
        throw std::logic_error("List is empty");
    }
    return _tail->value;
}

template <class T>
const T& List<T>::front() const {  
    if (is_empty()) {
        throw std::logic_error("List is empty");
    }
    return _head->value;
}

template <class T>
const T& List<T>::back() const {  
    if (is_empty()) {
        throw std::logic_error("List is empty");
    }
    return _tail->value;
}