#pragma once
#define STEP_OF_CAPACITY 15
#include<iostream>

template<typename T>
class TVector {
    T* _data;
    int _size;
    int _capacity;
public:
    class Iterator {
    private:
        T* _ptr;
    public:
        Iterator() : _ptr(nullptr) {}
        Iterator(T* ptr) : _ptr(ptr) {}

        Iterator& operator++() {  // Префиксный инкремент - перемещает итератор на следующий элемент
            ++_ptr;
            return *this;
        }

        Iterator operator++(int) {  // Постфиксный инкремент - возвращает старую позицию перед перемещением
            Iterator temp = *this;
            ++_ptr;
            return temp;
        }

        Iterator& operator--() {
            --_ptr;
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            --_ptr;
            return temp;
        }

        Iterator& operator+=(int n) {
            _ptr += n;
            return *this;
        }

        Iterator& operator-=(int n) {
            _ptr -= n;
            return *this;
        }

        T& operator*() const {   // Оператор разыменования - возвращает ссылку на текущий элемент
            return *_ptr;
        }

        T* operator->() const {
            return _ptr;
        }

        bool operator==(const Iterator& other) const {
            return _ptr == other._ptr;
        }

        bool operator!=(const Iterator& other) const {
            return _ptr != other._ptr;
        }

        Iterator operator+(int n) const {
            return Iterator(_ptr + n);
        }

        Iterator operator-(int n) const {
            return Iterator(_ptr - n);
        }

        int operator-(const Iterator& other) const {
            return _ptr - other._ptr;
        }
    };

    Iterator begin() const {
        return Iterator(_data);
    }

    Iterator end() const {
        return Iterator(_data + _size);
    }

    TVector();
    TVector(int size);
    TVector(std::initializer_list<T> data);
    TVector(const TVector<T>& other);

    ~TVector();

    inline T* data() const noexcept;
    inline int size() const noexcept;
    inline int capacity() const noexcept;
    inline const T& front() const;
    inline const T& back() const;
    inline T& front();
    inline T& back();

    void erase(int pos, int count = 1);  // Удаляет элементы начиная с позиции pos
    void push_back(const T& value);
    void push_front(const T& value);
    void pop_back();
    void pop_front();
    void insert(int pos, const T& value);
    void resize(int new_size);
    void repacking(int new_capacity);
    void clear();
    bool is_empty() const noexcept;
    bool is_full() const noexcept;
    int find(T val);

    inline T& operator[](int index);
    inline const T& operator[](int index) const;
    TVector<T>& operator=(const TVector<T>& other);

    template<typename T>
    friend std::ostream& operator<<(std::ostream& out, const TVector<T>& dmass);

    template<typename T>
    friend std::istream& operator>>(std::istream& in, TVector<T>& vec);
};

template<typename T>
TVector<T>::TVector() : _data(nullptr), _size(0), _capacity(0) {}

template<typename T>
TVector<T>::TVector(const TVector<T>& other) {
    _size = other._size;
    _capacity = other._capacity;
    _data = new T[_capacity];
    for (int i = 0; i < _size; ++i) {
        _data[i] = other._data[i];
    }
}

template<typename T>
inline T* TVector<T>::data() const noexcept
{
    return _data;
}

template<typename T>
inline int TVector<T>::size() const noexcept
{
    return _size;
}

template<typename T>
inline int TVector<T>::capacity() const noexcept
{
    return _capacity;
}

template<typename T>
TVector<T>::TVector(int size) {
    if (size < 0) {
        throw std::logic_error("Size cannot be negative");
    }
    _capacity = (size + STEP_OF_CAPACITY - 1) / STEP_OF_CAPACITY * STEP_OF_CAPACITY;
    if (_capacity == 0) {
        _capacity = STEP_OF_CAPACITY;
    }
    _size = size;
    _data = new T[_capacity];
    for (int i = 0; i < size; i++)
    {
        _data[i] = T();
    }
}

template<typename T>
TVector<T>::TVector(std::initializer_list<T> data) {
    _size = data.size();
    _capacity = (_size + STEP_OF_CAPACITY - 1) / STEP_OF_CAPACITY * STEP_OF_CAPACITY;
    if (_capacity == 0) {
        _capacity = STEP_OF_CAPACITY;
    }
    _data = new T[_capacity];
    for (int i = 0; i < _size; i++)
    {
        _data[i] = *(data.begin() + i);
    }
}

template<typename T>
inline const T& TVector<T>::front() const {
    if (_size < 1)
    {
        throw std::logic_error("Vector is empty");
    }
    return _data[0];
}

template<typename T>
inline const T& TVector<T>::back() const {
    if (_size < 1)
    {
        throw std::logic_error("Vector is empty");
    }
    return _data[_size - 1];
}

template<typename T>
inline T& TVector<T>::front() {
    if (_size < 1)
    {
        throw std::logic_error("Vector is empty");
    }
    return _data[0];
}

template<typename T>
inline T& TVector<T>::back() {
    if (_size < 1)
    {
        throw std::logic_error("Vector is empty");
    }
    return _data[_size - 1];
}

template<typename T>
inline T& TVector<T>::operator[](int index)
{
    if (index < 0 || index >= _size) {
        throw std::logic_error("Index out of range");
    }
    return _data[index];
}

template<typename T>
inline const T& TVector<T>::operator[](int index) const
{
    if (index < 0 || index >= _size) {
        throw std::logic_error("Index out of range");
    }
    return _data[index];
}

template<typename T>
TVector<T>::~TVector() {
    if (_data != nullptr) {
        delete[] _data;
        _data = nullptr;
    }
}

template<typename T>
bool TVector<T>::is_empty() const noexcept {
    return _size == 0;
}

template<typename T>
bool TVector<T>::is_full() const noexcept {
    return _size == _capacity;
}
template<typename T>
void TVector<T>::insert(int pos, const T& value) {
    if (pos < 0 || pos > _size) {
        throw std::logic_error("Insert position out of range");
    }

    // Проверка необходимости увеличения емкости
    if (_size >= _capacity) {
        int new_capacity = (_capacity == 0) ? STEP_OF_CAPACITY : _capacity + STEP_OF_CAPACITY;
        T* new_data = new T[new_capacity];

        for (int i = 0; i < pos; ++i) {
            new_data[i] = std::move(_data[i]);
        }

        new_data[pos] = value;

        for (int i = pos; i < _size; ++i) {
            new_data[i + 1] = std::move(_data[i]);
        }

        delete[] _data;
        _data = new_data;
        _capacity = new_capacity;
    }
    else {
        for (int i = _size - 1; i >= pos; --i) {
            _data[i + 1] = std::move(_data[i]);
        }

        _data[pos] = value;
    }

    ++_size;
}

template<typename T>
void TVector<T>::repacking(int capacity) { //  Перепаковка с новой емкостью
    if (capacity < _size) {
        throw std::logic_error("capacity cannot be less than current size");
    }
    T* data = new T[capacity];

    // Переносим существующие элементы
    for (int i = 0; i < _size; ++i) {
        data[i] = std::move(_data[i]);
    }
    delete[] _data;
    _data = data;
    _capacity = capacity;
}

template<typename T>
void TVector<T>::push_back(const T& value) {
    // Если места нет - увеличиваем емкость
    if (_size >= _capacity) {
        int new_capacity = (_capacity == 0) ? STEP_OF_CAPACITY : _capacity + STEP_OF_CAPACITY;
        T* new_data = new T[new_capacity];

        // Копируем старые элементы
        for (int i = 0; i < _size; ++i) {
            new_data[i] = std::move(_data[i]);
        }

        // Освобождаем старую память
        delete[] _data;
        _data = new_data;
        _capacity = new_capacity;
    }

    // Добавляем новый элемент
    _data[_size] = value;
    ++_size;
}

template<typename T>
void TVector<T>::push_front(const T& value) {
    insert(0, value);
}

template<typename T>
void TVector<T>::pop_back() {
    if (_size == 0) {
        throw std::logic_error("empty vector");
    }
    --_size;
}

template<typename T>
void TVector<T>::pop_front() {
    if (_size == 0) {
        throw std::logic_error("empty vector");
    }

    // Начинаем с первого элемента и двигаем все элементы влево
    for (int i = 1; i < _size; ++i) {
        _data[i - 1] = std::move(_data[i]);
    }
    --_size;
}

template<typename T>
void TVector<T>::resize(int size) {
    resize(size, T());
}

template<typename T>
void TVector<T>::clear() {
    if (_data != nullptr) {
        delete[]_data;
        _data = nullptr;
    }
}

template<typename T>
TVector<T>& TVector<T>::operator=(const TVector<T>& other)
{
    if (this != &other) {
        delete[] _data;
        _size = other._size;
        _capacity = other._capacity;
        _data = new T[_capacity];

        for (int i = 0; i < _size; ++i) {
            _data[i] = other._data[i];
        }
    }
    return *this;
}

template<typename T>
void TVector<T>::erase(int pos, int count) {
    if (pos < 0 || pos >= _size) {
        throw std::logic_error("Position is out of range");
    }
    if (count < 0) {
        throw std::logic_error("Count cannot be negative");
    }

    int actual_count = std::min(count, _size - pos);
    if (actual_count == 0) return;

    // Сдвигаем элементы влево, перекрывая удаляемые элементы
    for (int i = pos; i < _size - actual_count; ++i) {
        _data[i] = std::move(_data[i + actual_count]);
    }

    _size -= actual_count;
}

template<typename T>
int TVector<T>::find(T val) {
    for (int i = 0; i < _size; ++i) {
        if (_data[i] == val) {
            return i;
        }
    }
    return -1;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const TVector<T>& data) {
    for (int i = 0; i < data.size(); i++) {
        out << data[i] << " ";
    }
    return out;
}

template<typename T>
std::istream& operator>>(std::istream& in, TVector<T>& vec) {
    for (int i = 0; i < vec._size; ++i) {
        in >> vec._data[i];
    }
    return in;
}