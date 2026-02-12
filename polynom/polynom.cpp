#include "polynom.h"
#include <sstream>
#include <regex>

Polynom::Polynom() {}

// 1 моном
Polynom::Polynom(const Monom& m) {
    if (m.getCoef() != 0.0) {
        monoms.push_back(m);
    }
}

//вектор мономов
Polynom::Polynom(const std::vector<Monom>& mlist) : monoms(mlist) {
    simplify();
    sort();
}

Polynom::Polynom(const Polynom& other) : monoms(other.monoms) {
    simplify();
    sort();
}

Polynom::Polynom(const std::string& str) {
    *this = parse(str);
}

Polynom& Polynom::operator=(const Polynom& other) {
    if (this != &other) {
        monoms = other.monoms;
    }
    return *this;
}

void Polynom::simplify() {
    if (monoms.empty()) return;
    sort();
    // Объединяем подобные мономы
    std::vector<Monom> result;
    // Проходим по всем мономам
    for (size_t i = 0; i < monoms.size(); i++) {
        Monom current = monoms[i];

        if (current.getCoef() == 0.0) continue;

        while (i + 1 < monoms.size() && current.isSimilar(monoms[i + 1])) {
            try {
                current += monoms[i + 1]; // Складываем коэффициенты
            }
            catch (...) {
                // Игнорируем ошибки сложения
            }
            i++;
        }

        // Добавляем только если коэффициент не нулевой
        if (current.getCoef() != 0.0) {
            result.push_back(current);
        }
    }
    monoms = result;
}

void Polynom::sort() {
    std::sort(monoms.begin(), monoms.end(), [](const Monom& a, const Monom& b) { return a < b; });
}

void Polynom::addMonom(const Monom& m) {
    if (m.getCoef() != 0.0) {
        monoms.push_back(m);
        simplify();
    }
}

bool Polynom::operator==(const Polynom& other) const {
    if (monoms.size() != other.monoms.size()) return false;

    for (size_t i = 0; i < monoms.size(); i++) {
        if (monoms[i] != other.monoms[i]) {
            return false;
        }
    }
    return true;
}

bool Polynom::operator!=(const Polynom& other) const {
    return !(*this == other);
}

Polynom Polynom::operator+(const Polynom& other) const {
    Polynom result(*this);
    result += other;
    return result;
}

Polynom Polynom::operator-(const Polynom& other) const {
    Polynom result(*this);
    result -= other;
    return result;
}

Polynom Polynom::operator*(const Polynom& other) const {
    Polynom result;

    for (const auto& m1 : monoms) {
        for (const auto& m2 : other.monoms) {
            try {
                result.addMonom(m1 * m2);
            }
            catch (...) {
            }
        }
    }

    result.simplify();
    return result;
}

Polynom Polynom::operator*(double num) const {
    if (num == 0.0) {
        return Polynom();
    }

    Polynom result;
    for (const auto& m : monoms) {
        result.addMonom(m * num);
    }

    result.simplify();
    return result;
}

Polynom Polynom::operator/(double num) const {
    if (num == 0.0) {
        throw std::runtime_error("Division by zero");
    }

    Polynom result;
    for (const auto& m : monoms) {
        result.addMonom(m / num);
    }

    result.simplify();
    return result;
}

Polynom& Polynom::operator+=(const Polynom& other) {
    for (const auto& m : other.monoms) {
        addMonom(m);
    }
    simplify();
    return *this;
}

Polynom& Polynom::operator-=(const Polynom& other) {
    for (const auto& m : other.monoms) {
        addMonom(-m);
    }
    simplify();
    return *this;
}

Polynom& Polynom::operator*=(const Polynom& other) {
    *this = *this * other;
    return *this;
}

Polynom& Polynom::operator*=(double num) {
    for (auto& m : monoms) {
        m *= num;
    }
    simplify();
    return *this;
}

Polynom& Polynom::operator/=(double num) {
    if (num == 0.0) {
        throw std::runtime_error("Division by zero");
    }

    for (auto& m : monoms) {
        m /= num;
    }
    simplify();
    return *this;
}

Polynom Polynom::operator-() const {
    Polynom result;
    for (const auto& m : monoms) {
        result.addMonom(-m);
    }
    return result;
}

double Polynom::evaluate(double x, double y, double z) const {
    double result = 0.0;
    for (const auto& m : monoms) {
        result += m.evaluate(x, y, z);
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Polynom& p) {
    if (p.monoms.empty()) {
        os << "0";
        return os;
    }

    for (size_t i = 0; i < p.monoms.size(); i++) {
        if (i > 0) {
            if (p.monoms[i].getCoef() >= 0) {
                os << " + ";
            }
            else {
                os << " - ";
            }
        }

        double coef = p.monoms[i].getCoef();
        Monom toPrint = (i == 0 || coef < 0) ? p.monoms[i] : Monom(abs(coef),
            p.monoms[i].getPx(), p.monoms[i].getPy(), p.monoms[i].getPz());

        os << toPrint;
    }

    return os;
}

std::istream& operator>>(std::istream& is, Polynom& p) {
    std::string str;
    std::getline(is, str);
    p = Polynom::parse(str);
    return is;
}

std::string Polynom::toString() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

// Парсинг строки 
Polynom Polynom::parse(const std::string& str) {
    std::stringstream ss(str);
    std::vector<Monom> monoms;
    std::string token;

    // Разделяем по знакам + и - (кроме первого)
    std::string current;
    for (char c : str) {
        if ((c == '+' || c == '-') && !current.empty()) {
            // Парсим текущий моном
            std::stringstream monom_ss(current);
            double coef = 1.0;
            int px = 0, py = 0, pz = 0;

            // коэффициент x^степень y^степень z^степень
            monom_ss >> coef;

            size_t pos;
            if ((pos = current.find('x')) != std::string::npos) {
                px = 1;
                if (pos + 1 < current.size() && current[pos + 1] == '^') {
                    px = std::stoi(current.substr(pos + 2));
                }
            }
            if ((pos = current.find('y')) != std::string::npos) {
                py = 1;
                if (pos + 1 < current.size() && current[pos + 1] == '^') {
                    py = std::stoi(current.substr(pos + 2));
                }
            }
            if ((pos = current.find('z')) != std::string::npos) {
                pz = 1;
                if (pos + 1 < current.size() && current[pos + 1] == '^') {
                    pz = std::stoi(current.substr(pos + 2));
                }
            }

            monoms.push_back(Monom(coef, px, py, pz));
            current = (c == '-') ? "-" : "";
        }
        else {
            current += c;
        }
    }

    // Парсим последний моном
    if (!current.empty()) {
        std::stringstream monom_ss(current);
        double coef = 1.0;
        int px = 0, py = 0, pz = 0;

        monom_ss >> coef;

        // Аналогичный парсинг для последнего монома
        size_t pos;
        if ((pos = current.find('x')) != std::string::npos) {
            px = 1;
            if (pos + 1 < current.size() && current[pos + 1] == '^') {
                px = std::stoi(current.substr(pos + 2));
            }
        }
        if ((pos = current.find('y')) != std::string::npos) {
            py = 1;
            if (pos + 1 < current.size() && current[pos + 1] == '^') {
                py = std::stoi(current.substr(pos + 2));
            }
        }
        if ((pos = current.find('z')) != std::string::npos) {
            pz = 1;
            if (pos + 1 < current.size() && current[pos + 1] == '^') {
                pz = std::stoi(current.substr(pos + 2));
            }
        }

        monoms.push_back(Monom(coef, px, py, pz));
    }

    return Polynom(monoms);
}

Polynom operator*(double num, const Polynom& p) {
    return p * num;
}