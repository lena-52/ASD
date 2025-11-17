#pragma once
#include <iostream>
#define STEP_OF_CAPACITY 15
int calc_capacity(int size) {
	return (size + STEP_OF_CAPACITY) / STEP_OF_CAPACITY * STEP_OF_CAPACITY;
}
template <class T> class TVector;

template <class T>
std::ostream& operator<<(std::ostream& out, const TVector<T>& vec);

template <class T> class TVector;

template <class T>
std::istream& operator>>(std::istream& in, TVector<T>& vec);

template <class T>
class TVector {
protected:
	T* _data;
	int _size;
	int _capacity;
public:
	class Iterator {
	private:
		T* current;
	public:
		Iterator() : current(nullptr) {}
		Iterator(T* pos) : current(pos) {}
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
			return *current;
		}

		bool operator==(const Iterator& other) const {
			return current == other.current;
		}

		bool operator!=(const Iterator& other) const {
			return current != other.current;
		}

		Iterator& operator++() {
			if (current != nullptr) {
				current++;
			}
			return *this;
		}

		Iterator operator++(int) {
			Iterator tmp = *this;
			++(*this);
			return tmp;
		}

		Iterator& operator--() {
			if (current != nullptr) {
				current--;
			}
			return *this;
		}

		Iterator operator--(int) {
			Iterator tmp = *this;
			--(*this);
			return tmp;
		}
	};
	typedef Iterator iterator;
	TVector();
	TVector(const TVector& other);
	TVector(std::initializer_list<T> data);
	TVector(int size);
	TVector(T* data, int size);
	~TVector();
	inline T* data() const noexcept;
	inline int size() const noexcept;
	inline int capacity() const noexcept;
	inline T& operator[](int indx) noexcept;
	inline const T& operator[](int indx) const noexcept;
	friend std::ostream& operator<< <T>(std::ostream& out, const TVector<T>& vec);
	friend std::istream& operator>> <T>(std::istream& in, TVector<T>& vec);
	void clear();
	TVector& operator=(const TVector& other) noexcept;
	int find(T Val) const;
	bool full() const noexcept;
	void reset_memory();
	void push_front(T number);
	void push_back(T number);
	void insert(int pos, T number);
	void erase(int pos, int count = 1);
	T& front() noexcept;
	T& back() noexcept;
	const T& front() const noexcept;
	const T& back() const noexcept;
	T pop_back();
	T pop_front();

	iterator begin() {
		return iterator(_data);
	}

	iterator end() {
		return iterator(_data + _size);
	}
};

template <class T>
TVector<T>::TVector() :_data(nullptr), _size(0), _capacity(0) {}

template <class T>
TVector<T>::TVector(const TVector<T>& other) : _size(other._size), _capacity(calc_capacity(other._size)) {
	_data = new T[_capacity];
	for (int i = 0; i < _size; i++) {
		_data[i] = other._data[i];
	}
};

template <class T>
TVector<T>::TVector(std::initializer_list<T> data) {
	_size = data.size();
	_capacity = calc_capacity(_size);
	_data = new T[_capacity];
	for (int i = 0; i < _size; i++) {
		_data[i] = *(data.begin() + i);
	}
}

template <class T>
TVector<T>::TVector(int size) {
	if (size >= 0) {
		_size = size;
		_capacity = calc_capacity(size);
		_data = new T[_capacity];
	}
	else {
		throw std::logic_error("size < 0");
	}
}

template <class T>
TVector<T>::TVector(T* data, int size) : _size(size), _capacity(calc_capacity(size)) {
	_data = new T[_capacity];
	for (int i = 0; i < _size; ++i) {
		_data[i] = data[i];
	}
}

template <class T>
TVector<T>::~TVector() {
	clear();
	_size = 0;
	_capacity = 0;
}

template <class T>
inline T* TVector<T>::data() const noexcept {
	return _data;
}

template <class T>
inline int TVector<T>::size() const noexcept {
	return _size;
}

template <class T>
inline int TVector<T>::capacity() const noexcept {
	return _capacity;
}

template <class T>
inline T& TVector<T>::operator[](int indx) noexcept {
	return _data[indx];
}

template <class T>
inline const T& TVector<T>::operator[](int indx) const noexcept {
	return _data[indx];
}

template <class T>
std::ostream& operator<<(std::ostream& out, const TVector<T>& vec) {
	for (int i = 0; i < vec.size(); i++) {
		out << vec[i] << " ";
	}
	return out;
}

template <class T>
std::istream& operator>>(std::istream& in, TVector<T>& vec) {
	vec.clear();

	T value;
	while (in >> value) {
		vec.push_back(value);
	}

	in.clear();
	return in;
}

template <class T>
void TVector<T>::clear() {
	if (_data != nullptr) {
		delete[] _data;
		_data = nullptr;
	}
}

template <class T>
TVector<T>& TVector<T>::operator=(const TVector<T>& other) noexcept {
	if (this == &other) {
		return *this;
	}
	if (_data != nullptr) {
		delete[] _data;
	}
	_size = other._size;
	_capacity = other._capacity;
	_data = new T[_capacity];
	for (int i = 0; i < _size; i++) {
		_data[i] = other._data[i];
	}
	return *this;
}

template<class T>
int TVector<T>::find(T Number) const {
	for (int i = 0; i < _size; i++)
	{
		if (_data[i] == Number)
			return i;
	}
	throw  std::logic_error("Number did not found");
}

template<class T>
bool TVector<T>::full() const noexcept {
	if (_size == _capacity) {
		return true;
	}
	return false;
}

template<class T>
void TVector<T>::reset_memory() {
	_capacity = calc_capacity(_size);
	T* data = new T[_capacity];
	for (int i = 0; i < _size; i++)
	{
		data[i] = _data[i];
	}
	delete[] _data;
	_data = data;
}

template<class T>
void TVector<T>::push_front(T number) {
	if (full())
	{
		reset_memory();
	}
	for (int i = _size; i > 0; i--)
		_data[i] = _data[i - 1];
	_data[0] = number;
	_size++;
}

template<class T>
void TVector<T>::push_back(T number) {
	if (!full())
		_data[_size] = number;
	else {
		reset_memory();
		_data[_size] = number;
	}
	_size++;
}

template<class T>
void TVector<T>::insert(int pos, T number) {
	if (pos <= _size && pos >= 0) {
		if (full()) {
			reset_memory();
		}

		for (int i = _size; i > pos; i--)
			_data[i] = _data[i - 1];
		_data[pos] = number;
		_size++;
	}
	else
		throw std::logic_error("position out of range");
}

template<class T>
void TVector<T>::erase(int pos, int count) {
	if (pos + count > _size || pos < 0 || count <= 0) {
		throw std::logic_error("position or count out of range");
	}
	for (int i = pos; i < _size - count; i++) {
		_data[i] = _data[i + count];
	}
	_size -= count;
	reset_memory();
}

template<class T>
T& TVector<T>::front() noexcept {
	return _data[0];
}

template<class T>
T& TVector<T>::back() noexcept {
	return _data[_size - 1];
}

template<class T>
const T& TVector<T>::front() const noexcept {
	return _data[0];
}

template<class T>
const T& TVector<T>::back() const noexcept {
	return _data[_size - 1];
}

template<class T>
T TVector<T>::pop_back() {
	T pop = _data[_size - 1];
	_size--;
	reset_memory();
	return pop;
}

template<class T>
T TVector<T>::pop_front() {
	T pop = _data[0];
	for (int i = 0; i < _size - 1; i++)
		_data[i] = _data[i + 1];
	--_size;
	reset_memory();
	return pop;
}
