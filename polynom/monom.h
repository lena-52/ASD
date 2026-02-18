#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <stdexcept>

class Monom {
    double coef; // коэффициент
    int px, py, pz;   // степени переменных x, y, z
    void simplify();
public:
    Monom(double c = 0.0, int x = 0, int y = 0, int z = 0);
    Monom(const Monom& other);

    // Проверка подобия
    bool isSimilar(const Monom& other) const;

    int getDegree() const;
    double getCoef() const {
        return coef;
    }
    int getPx() const {
        return px;
    }
    int getPy() const { 
        return py; 
    }
    int getPz() const { 
        return pz;
    }

    bool operator==(const Monom& other) const;
    bool operator!=(const Monom& other) const;

    Monom operator+(const Monom& other) const;
    Monom operator-(const Monom& other) const;
    Monom operator*(const Monom& other) const;
    Monom operator/(const Monom& other) const;

    Monom operator*(double num) const;
    Monom operator/(double num) const;

    Monom& operator+=(const Monom& other);
    Monom& operator-=(const Monom& other);
    Monom& operator*=(const Monom& other);
    Monom& operator/=(const Monom& other);
    Monom& operator*=(double num);
    Monom& operator/=(double num);
    Monom& operator=(const Monom& other);
    Monom operator-() const;

    // Вычисление значения в точке
    double evaluate(double x, double y, double z) const;

    friend std::ostream& operator<<(std::ostream& os, const Monom& m);
    friend std::istream& operator>>(std::istream& is, Monom& m);

    std::string toString() const;

    // Функциидля сортировки
    bool operator<(const Monom& other) const;
    bool operator>(const Monom& other) const;
};

// умножениe на константу 
Monom operator*(double num, const Monom& m);

