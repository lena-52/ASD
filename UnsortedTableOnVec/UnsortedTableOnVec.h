#pragma once
#include"ITable.h"
#include <map>
#include <iostream>
#include <stdexcept>
#include "vector.h"
template<typename TKey, typename TValue>
class UnsortedTableOnVec :public ITable<TKey, TValue> {
	TVector<std::pair<TKey, TValue>> _rows; // хранилище данных - вектор пар "ключ-значение"
    int find_position(const TKey& Key) const noexcept;  // для поиска позиции элемента по ключу
protected:
    std::ostream& print(std::ostream& out) const override;
public:
    // Запрещаем копирование
    UnsortedTableOnVec(const UnsortedTableOnVec&) = delete;
    UnsortedTableOnVec& operator=(const UnsortedTableOnVec&) = delete;

	~UnsortedTableOnVec() = default;
	UnsortedTableOnVec() = default;
	void insert(const TKey& Key, const TValue& Val) override;
	TValue find(const TKey& Key) const override;
    void erase(const TKey& Key) override;
    bool is_empty() const noexcept override;
	bool consist(const TKey& Key) const noexcept override;

    void clear() noexcept;
    int size() const noexcept;
};

template<typename TKey, typename TValue>
int UnsortedTableOnVec<TKey, TValue>::find_position(const TKey& Key) const noexcept {
    for (int i = 0; i < _rows.size(); ++i) {
        if (_rows[i].first == Key) {
            return i;
        }
    }
    return -1;
}

template<typename TKey, typename TValue>
std::ostream& UnsortedTableOnVec<TKey, TValue>::print(std::ostream& out) const {
    out << "UnsortedTableOnVec {";
    for (int i = 0; i < _rows.size(); ++i) {
        if (i > 0) out << ", ";
        out << _rows[i].first << ": " << _rows[i].second;
    }
    out << "}";
    return out;
}

template<typename TKey, typename TValue>
void UnsortedTableOnVec<TKey, TValue>::insert(const TKey& Key, const TValue& Val)  {
    int pos = find_position(Key);
    if (pos != -1) {
        // Если ключ уже существует, обновляем значение
        _rows[pos].second = Val;
    }
    else {
        // Иначе добавляем новую пару
        _rows.push_back(std::make_pair(Key, Val));
    }
}
template<typename TKey, typename TValue>
TValue UnsortedTableOnVec<TKey, TValue>::find(const TKey& Key) const {
    int pos = find_position(Key);
    if (pos != -1) {
        return _rows[pos].second;
    }
    throw std::logic_error("Key not found");
}

template<typename TKey, typename TValue>
void UnsortedTableOnVec<TKey, TValue>::erase(const TKey& Key) {
    int pos = find_position(Key);
    if (pos != -1) {
        _rows.erase(pos);
    }
    else {
        throw std::logic_error("Key not found");
    }
}

template<typename TKey, typename TValue>
bool UnsortedTableOnVec<TKey, TValue>::is_empty() const noexcept {
    return _rows.is_empty();
}

template<typename TKey, typename TValue>
bool UnsortedTableOnVec<TKey, TValue>::consist(const TKey& Key) const noexcept {
    return find_position(Key) != -1;
}

template<typename TKey, typename TValue>
int UnsortedTableOnVec<TKey, TValue>::size() const noexcept {
    return _rows.size();
}

template<typename TKey, typename TValue>
void UnsortedTableOnVec<TKey, TValue>::clear() noexcept {
    _rows.clear();
}

