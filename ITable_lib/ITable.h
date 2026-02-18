#pragma once
#include<iostream>
#include"vector.h"
template<typename TKey, typename TValue>
class ITable {
protected:
	virtual std::ostream& print(std::ostream& out) const = 0;
public:
	virtual void insert(const TKey& Key, const TValue& Val) = 0;
	virtual TValue find(const TKey& Key) const = 0;
	virtual void erase(const TKey& Key) = 0;
	virtual bool is_empty() const noexcept = 0;
	virtual bool consist(const TKey& Key) const noexcept = 0;
	virtual ~ITable() {}
	friend std::ostream& operator<<(std::ostream& out, const ITable& table) {
		return table.print(out);
	}
};
