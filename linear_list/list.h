#include <iostream>

template <class T>
struct Node { //для описания 1 элемента
    T value;
    Node<T>* next;
    Node(T value, Node<T>* next = nullptr) : value(value), next(next) {}
};

template <class T>
class List {
    Node<T>* _head; //указатель на верх массива
    int _count;
    Node<T>* _tail;

public:
    class Iterator {
        Node<T>* current;
    public:
        Iterator() : current(nullptr) {}
        Iterator(Node<T>* pos = nullptr) : current(pos) {}
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

        const T& operator*() const {
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
    void insert(Node<T>* node, const T& val); //эффективно
    void pop_front();
    void pop_back();
    void erase(Node<T>* node);
    void clear();

    bool is_empty() const;
    int size() const;
    Node<T>* find(const T& val);
    Node<T>* get_head() const;
    Node<T>* get_tail() const;
    T& front();
    T& back();
    const T& back() const;
    const T& front() const;

};

template <class T>
List<T>::List() : _head(nullptr), _count(0), _tail(nullptr) {}

template <class T>
List<T>::List(const List& other) : _head(nullptr), _count(0), _tail(nullptr) {
    Node<T>* current = other._head;
    while (current != nullptr) {
        push_back(current->value);
        current = current->next;
    }
}

template <class T>
List<T>& List<T>::operator=(const List& other) {
    if (this != &other) {
        clear();
        Node<T>* current = other._head;
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
    Node<T>* node = new Node<T>(val, _head); //создали звено, которое указывает на head
    _head = node;
    if (_tail == nullptr) {
        _tail = node;
    }
    _count++;
}

template <class T>
void List<T>::push_back(const T& val) noexcept {
    Node<T>* node = new Node<T>(val);
    if (is_empty()) {
        _head = node;
        _tail = node;
    }
    else {
        _tail->next = node;
        _tail = node;
    }
    _count++;
}

template <class T>
void List<T>::insert(int pos, const T& val) {
    if (pos < 0 || pos > _count) {
        throw std::logic_error("Position out of range");
    }

    if (pos == 0) {
        push_front(val);
    }
    else if (pos == _count) {
        push_back(val);
    }
    else {
        Node<T>* current = _head;
        for (int i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        insert(current, val);
    }
}

template <class T>
void List<T>::insert(Node<T>* node, const T& val) {
    if (node == nullptr) {
        throw std::logic_error("Node cannot be null");
    }
    Node<T>* new_node = new Node<T>(val, node->next);
    node->next = new_node;
    if (_tail == node) {
        _tail = new_node;
    }
    _count++;
}

template <class T>
void List<T>::pop_front() {
    if (is_empty()) {
        throw std::logic_error("Cannot pop from empty list");
    }
    Node<T>* temp = _head;
    _head = _head->next;
    if (_head == nullptr) {
        _tail = nullptr;
    }
    delete temp;
    _count--;
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
        Node<T>* current = _head;
        while (current->next != _tail) {
            current = current->next;
        }
        delete _tail;
        _tail = current;
        _tail->next = nullptr;
    }
    _count--;
}

template <class T>
void List<T>::erase(Node<T>* node) {
    if (node == nullptr || is_empty()) {
        throw std::logic_error("Node cannot be null");
    }

    if (node == _head) {
        pop_front();
        return;
    }

    Node<T>* current = _head;
    while (current != nullptr && current->next != node) {
        current = current->next;
    }

    if (current == nullptr) {
        throw std::logic_error("Node not found in list");
    }

    current->next = node->next;
    if (node == _tail) {
        _tail = current;
    }
    delete node;
    _count--;
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
int List<T>::size() const {
    return _count;
}

template <class T>
Node<T>* List<T>::find(const T& val) {
    Node<T>* current = _head;
    while (current != nullptr) {
        if (current->value == val) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template <class T>
Node<T>* List<T>::get_head() const {
    return _head;
}

template <class T>
Node<T>* List<T>::get_tail() const {
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
const T& List<T>::back() const {
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