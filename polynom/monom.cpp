#include "monom.h"

Monom::Monom(double c, int x, int y, int z) : coef(c), px(x), py(y), pz(z) {
    if (c == 0) {
        px = py = pz = 0; 
    }
}

Monom::Monom(const Monom& other) : coef(other.coef), px(other.px), py(other.py), pz(other.pz) {}

Monom& Monom::operator=(const Monom& other) {
    if (this != &other) {
        coef = other.coef;
        px = other.px;
        py = other.py;
        pz = other.pz;
    }
    return *this;
}

bool Monom::isSimilar(const Monom& other) const {
    return (px == other.px && py == other.py && pz == other.pz);
}

int Monom::getDegree() const {
    return px + py + pz;
}

void Monom::simplify() {
    if (coef == 0.0) {
        px = py = pz = 0;
    }
}

bool Monom::operator==(const Monom& other) const {
    if (coef == 0 && other.coef == 0) return true;
    return (coef == other.coef && px == other.px && py == other.py && pz == other.pz);
}

bool Monom::operator!=(const Monom& other) const {
    return !(*this == other);
}

Monom Monom::operator+(const Monom& other) const {
    if (!isSimilar(other)) {
        throw std::runtime_error("Cannot add non-similar monomials");
    }
    return Monom(coef + other.coef, px, py, pz);
}

Monom Monom::operator-(const Monom& other) const {
    if (!isSimilar(other)) {
        throw std::runtime_error("Cannot subtract non-similar monomials");
    }
    return Monom(coef - other.coef, px, py, pz);
}

Monom Monom::operator*(const Monom& other) const {
    return Monom(coef * other.coef, px + other.px,py + other.py, pz + other.pz);
}

Monom Monom::operator/(const Monom& other) const {
    if (other.coef == 0) {
        throw std::runtime_error("Division by zero");
    }

    // Проверка, что степени делятся без остатка
    if (px < other.px || py < other.py || pz < other.pz) {
        throw std::runtime_error("negative powers would result");
    }

    return Monom(coef / other.coef,px - other.px,py - other.py,pz - other.pz);
}

Monom Monom::operator*(double num) const {
    return Monom(coef * num, px, py, pz);
}

Monom Monom::operator/(double num) const {
    if (num == 0) {
        throw std::runtime_error("Division by zero");
    }
    return Monom(coef / num, px, py, pz);
}

Monom& Monom::operator+=(const Monom& other) {
    if (!isSimilar(other)) {
        throw std::runtime_error("Cannot add non-similar monomials");
    }
    coef += other.coef;
    simplify();
    return *this;
}

Monom& Monom::operator-=(const Monom& other) {
    if (!isSimilar(other)) {
        throw std::runtime_error("Cannot subtract non-similar monomials");
    }
    coef -= other.coef;
    simplify();
    return *this;
}

Monom& Monom::operator*=(const Monom& other) {
    coef *= other.coef;
    px += other.px;
    py += other.py;
    pz += other.pz;
    return *this;
}

Monom& Monom::operator/=(const Monom& other) {
    if (other.coef == 0) {
        throw std::runtime_error("Division by zero");
    }

    if (px < other.px || py < other.py || pz < other.pz) {
        throw std::runtime_error("negative powers would result");
    }

    coef /= other.coef;
    px -= other.px;
    py -= other.py;
    pz -= other.pz;
    return *this;
}

Monom& Monom::operator*=(double num) {
    coef *= num;
    simplify();
    return *this;
}

Monom& Monom::operator/=(double num) {
    if (num == 0) {
        throw std::runtime_error("Division by zero");
    }
    coef /= num;
    simplify();
    return *this;
}

Monom Monom::operator-() const {
    return Monom(-coef, px, py, pz);
}

double Monom::evaluate(double x, double y, double z) const {
    return coef * pow(x, px) * pow(y, py) * pow(z, pz);
}

std::ostream& operator<<(std::ostream& os, const Monom& m) {
    os << m.toString();
    return os;
}

std::istream& operator>>(std::istream& is, Monom& m) {
    std::string str;
    is >> str;

    std::stringstream ss(str);
    ss >> m.coef;

    m.px = m.py = m.pz = 0;

    return is;
}

std::string Monom::toString() const {
    std::stringstream ss;

    if (coef == 0.0) {
        return "0";
    }

    if (coef == 1.0 && (px != 0 || py != 0 || pz != 0)) {
        // Не выводим 1
    }
    else if (coef == -1.0 && (px != 0 || py != 0 || pz != 0)) {
        ss << "-";
    }
    else {
        ss << coef;
    }

    // Выводим x
    if (px != 0) {
        ss << "x";
        if (px != 1) {
            ss << "^" << px;
        }
    }

    // Выводим y
    if (py != 0) {
        ss << "y";
        if (py != 1) {
            ss << "^" << py;
        }
    }

    // Выводим z
    if (pz != 0) {
        ss << "z";
        if (pz != 1) {
            ss << "^" << pz;
        }
    }

    // Если все степени 0, выводим только коэффициент
    if (px == 0 && py == 0 && pz == 0) {
        ss.str("");
        ss << coef;
    }

    return ss.str();
}

// Операторы сравнения для сортировки
bool Monom::operator<(const Monom& other) const {
    // Сначала сравниваем степень x
    if (px != other.px) {
        return px > other.px; // Большая степень x идет раньше
    }
    // Если степени x равны, сравниваем степень y
    if (py != other.py) {
        return py > other.py; // Большая степень y идет раньше
    }
    // Если степени x и y равны, сравниваем степень z
    if (pz != other.pz) {
        return pz > other.pz; // Большая степень z идет раньше
    }
    return false;
}

bool Monom::operator>(const Monom& other) const {
    return other < *this;
}

Monom operator*(double num, const Monom& m) {
    return m * num;
}