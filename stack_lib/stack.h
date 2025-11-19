#include <iostream>
template<class T>
class Stack {
	T* _data;
	int _size;
	int _top;
public:
	Stack(int size = 100);
	Stack(const Stack& other);
	Stack& operator=(const Stack& other);
	~Stack();

	void push(const T& val);
	void pop();
	inline T top() const;
	inline bool is_empty() const noexcept;
	inline bool is_full() const noexcept;
	void clear() noexcept;
	int size() const noexcept;
};


template<class T>
Stack<T>::Stack(int size) : _size(size), _top(-1) {
	_data = new T[_size];
}

template<class T>
Stack<T>::Stack(const Stack& other) : _size(other._size), _top(other._top) {
	_data = new T[_size];
	for (int i = 0; i <= _top; ++i) {
		_data[i] = other._data[i];
	}
}

template<class T>
int Stack<T>::size() const noexcept {
	return _top + 1;
}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
	if (this != &other) {
		delete[] _data;
		_size = other._size;
		_top = other._top;
		_data = new T[_size];
		for (int i = 0; i <= _top; ++i) {
			_data[i] = other._data[i];
		}
	}
	return *this;
}

template<class T>
Stack<T>::~Stack() {
	delete[] _data;
}

template<class T>
void Stack<T>::push(const T& val) {
	if (is_full()) {
		throw std::logic_error("Stack is full");
	}
	_data[++_top] = val;
}

template<class T>
void Stack<T>::pop() {
	if (is_empty()) {
		throw std::logic_error("Stack is empty");
	}
	--_top;
}

template<class T>
T Stack<T>::top() const {
	if (is_empty()) {
		throw std::logic_error("Stack is empty");
	}
	return _data[_top];
}

template<class T>
bool Stack<T>::is_empty() const noexcept {
	return _top == -1;
}

template<class T>
bool Stack<T>::is_full() const noexcept {
	return _top == _size - 1;
}

template<class T>
void Stack<T>::clear() noexcept {
	_top = -1;
}