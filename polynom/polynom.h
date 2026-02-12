#pragma once
#include "monom.h"
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

class Polynom {
    std::vector<Monom> monoms; // Список мономов
    void sort();
public:
    Polynom();
    Polynom(const Monom& m);
    Polynom(const std::vector<Monom>& mlist);
    Polynom(const Polynom& other);
    Polynom(const std::string& str);

    Polynom& operator=(const Polynom& other);

    const std::vector<Monom>& getMonoms() const { 
        return monoms;
    }
    bool isEmpty() const {
        return monoms.empty();
    }

    void simplify(); // Упрощение полинома

    void addMonom(const Monom& m);

    bool operator==(const Polynom& other) const;
    bool operator!=(const Polynom& other) const;
    Polynom operator+(const Polynom& other) const;
    Polynom operator-(const Polynom& other) const;
    Polynom operator*(const Polynom& other) const;

    Polynom operator*(double num) const;
    Polynom operator/(double num) const;

    Polynom& operator+=(const Polynom& other);
    Polynom& operator-=(const Polynom& other);
    Polynom& operator*=(const Polynom& other);
    Polynom& operator*=(double num);
    Polynom& operator/=(double num);

    Polynom operator-() const;

    double evaluate(double x, double y, double z) const;

    friend std::ostream& operator<<(std::ostream& os, const Polynom& p);
    friend std::istream& operator>>(std::istream& is, Polynom& p);

    std::string toString() const;
    static Polynom parse(const std::string& str);
};

Polynom operator*(double num, const Polynom& p);

