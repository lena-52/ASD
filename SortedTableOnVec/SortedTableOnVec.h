#pragma once
#include"ITable.h"
#include <map>
#include <iostream>
#include <stdexcept>
#include "vector.h"
template<typename TKey, typename TValue>
class SortedTableOnVec : public ITable<TKey, TValue> {
	TVector<std::pair<TKey, TValue>> _rows;
    int find_position(const TKey& Key) const noexcept;     // Бинарный поиск позиции элемента по ключу
    int find_insert_position(const TKey& Key) const noexcept;     // Поиск позиции для вставки 

protected:
    std::ostream& print(std::ostream& out) const override;

public:
    SortedTableOnVec() = default;
    ~SortedTableOnVec() override = default;

    // Запрещаем копирование
    SortedTableOnVec(const SortedTableOnVec&) = delete;
    SortedTableOnVec& operator=(const SortedTableOnVec&) = delete;

    void insert(const TKey& Key, const TValue& Val) override;
    TValue find(const TKey& Key) const override;
    void erase(const TKey& Key) override;
    bool is_empty() const noexcept override;
    bool consist(const TKey& Key) const noexcept override;
    void clear() noexcept;
    int size() const noexcept;

    TKey get_min_key() const;  
    TKey get_max_key() const; 
    std::pair<TKey, TValue> get_by_index(int index) const;  // Получить значение по индексу
    TVector<TKey> get_keys() const;  // Получить все ключи 
    TVector<TValue> get_values() const; // Получить все значения
};

template<typename TKey, typename TValue>
int SortedTableOnVec<TKey, TValue>::find_position(const TKey& Key) const noexcept {
    int left = 0;
    int right = _rows.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (_rows[mid].first == Key) {
            return mid; // ключ найден
        }
        else if (_rows[mid].first < Key) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -left - 1; // возвращаем отрицательное значение, указывающее позицию для вставки
}

template<typename TKey, typename TValue>
int  SortedTableOnVec<TKey, TValue>::find_insert_position(const TKey& Key) const noexcept {
    int left = 0;
    int right = _rows.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (_rows[mid].first == Key) {
            return mid; // ключ уже существует
        }
        else if (_rows[mid].first < Key) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return left; // позиция для вставки нового элемента
}

template<typename TKey, typename TValue>
std::ostream& SortedTableOnVec<TKey, TValue>::print(std::ostream& out) const {
    out << "SortedTableOnVec {";
    for (int i = 0; i < _rows.size(); ++i) {
        if (i > 0) out << ", ";
        out << _rows[i].first << ": " << _rows[i].second;
    }
    out << "}";
    return out;
 }

template<typename TKey, typename TValue>
void  SortedTableOnVec<TKey, TValue>::insert(const TKey& Key, const TValue& Val) {
    int insertPos = find_insert_position(Key);

    // Проверяем, существует ли уже такой ключ
    if (insertPos < _rows.size() && _rows[insertPos].first == Key) {
        // обновляем значение
        _rows[insertPos].second = Val;
    }
    else {
        //вставляем новую пару на правильную позицию
        _rows.insert(insertPos, std::make_pair(Key, Val));
    }
 }

template<typename TKey, typename TValue>
TValue SortedTableOnVec<TKey, TValue>:: find(const TKey& Key) const{
     int pos = find_position(Key);
     if (pos >= 0) {
         return _rows[pos].second;
     }
     throw std::out_of_range("Key not found");
 }


 template<typename TKey, typename TValue>
 void SortedTableOnVec<TKey, TValue>:: erase(const TKey& Key) {
     int pos = find_position(Key);
     if (pos >= 0) {
         _rows.erase(pos);
     }
     else {
         throw std::out_of_range("Key not found");
     }
 }

 template<typename TKey, typename TValue>
 bool SortedTableOnVec<TKey, TValue>::is_empty() const noexcept {
     return _rows.is_empty();

 }

 template<typename TKey, typename TValue>
 bool SortedTableOnVec<TKey, TValue>:: consist(const TKey& Key) const noexcept {
     return find_position(Key) >= 0;
 }

 template<typename TKey, typename TValue>
 void SortedTableOnVec<TKey, TValue>::clear() noexcept {
    _rows.clear();
 }

 template<typename TKey, typename TValue>
 int SortedTableOnVec<TKey, TValue>:: size() const noexcept {
     return _rows.size();
 }

 template<typename TKey, typename TValue>
 TKey SortedTableOnVec<TKey, TValue>::get_min_key() const {
     if (is_empty()) {
         throw std::out_of_range("Table is empty");
     }
     return _rows[0].first;
 }


 template<typename TKey, typename TValue>
 TKey SortedTableOnVec<TKey, TValue>::get_max_key() const {
     if (is_empty()) {
         throw std::out_of_range("Table is empty");
     }
     return _rows[_rows.size() - 1].first;
 }


 template<typename TKey, typename TValue>
 std::pair<TKey, TValue> SortedTableOnVec<TKey, TValue>::get_by_index(int index) const {
     if (index < 0 || index >= _rows.size()) {
         throw std::out_of_range("Index out of range");
     }
     return _rows[index];
 }


 template<typename TKey, typename TValue>
 TVector<TKey> SortedTableOnVec<TKey, TValue>::get_keys() const {
     TVector<TKey> keys;
     for (int i = 0; i < _rows.size(); ++i) {
         keys.push_back(_rows[i].first);
     }
     return keys;
 } 

 template<typename TKey, typename TValue>
 TVector<TValue>  SortedTableOnVec<TKey, TValue>::get_values() const {
     TVector<TValue> values;
     for (int i = 0; i < _rows.size(); ++i) {
         values.push_back(_rows[i].second);
     }
     return values;
 } 
