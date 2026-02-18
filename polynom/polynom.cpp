#include "polynom.h"
#include <sstream>
#include <regex>
#include <cctype>
#include <iomanip>
#include <cmath>

Polynom::Polynom() {}

// Из монома
Polynom::Polynom(const Monom& m) {
    if (m.getCoef() != 0.0) {
        monoms.push_back(m);
    }
}

// Из вектора мономов
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

    for (size_t i = 0; i < monoms.size(); i++) {
        Monom current = monoms[i];

        if (std::abs(current.getCoef()) < 1e-10) continue; // Игнорируем нулевые

        // Объединяем с последующими подобными
        while (i + 1 < monoms.size() && current.isSimilar(monoms[i + 1])) {
            current += monoms[i + 1];
            i++;
        }

        // Добавляем только если коэффициент не нулевой
        if (std::abs(current.getCoef()) > 1e-10) {
            result.push_back(current);
        }
    }

    monoms = result;
}

void Polynom::sort() {
    std::sort(monoms.begin(), monoms.end(), [](const Monom& a, const Monom& b) {
        return a < b;
        });
}

void Polynom::addMonom(const Monom& m) {
    if (std::abs(m.getCoef()) > 1e-10) {
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
                // Игнорируем ошибки умножения
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

    bool first = true;
    for (const auto& monom : p.monoms) {
        double coef = monom.getCoef();

        if (!first) {
            if (coef > 0) {
                os << " + ";
            }
            else {
                os << " - ";
            }
        }
        else {
            first = false;
            if (coef < 0) {
                os << "-";
            }
        }

        // Создаем моном с положительным коэффициентом для вывода
        double absCoef = std::abs(coef);
        Monom toPrint(absCoef, monom.getPx(), monom.getPy(), monom.getPz());
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
    std::vector<Monom> monoms;
    std::string s = str;

    // Удаляем пробелы
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());

    if (s.empty() || s == "0") {
        return Polynom();
    }

    size_t pos = 0;
    bool positive = true;

    while (pos < s.length()) {
        // Определяем знак
        if (s[pos] == '+') {
            positive = true;
            pos++;
        }
        else if (s[pos] == '-') {
            positive = false;
            pos++;
        }

        // Если дошли до конца, выходим
        if (pos >= s.length()) break;

        // Парсим коэффициент
        double coef = 1.0;
        std::string coefStr;

        // Проверяем, начинается ли с цифры или точки
        if (std::isdigit(s[pos]) || s[pos] == '.') {
            while (pos < s.length() && (std::isdigit(s[pos]) || s[pos] == '.')) {
                coefStr += s[pos];
                pos++;
            }
            if (!coefStr.empty()) {
                coef = std::stod(coefStr);
            }
        }

        if (!positive) {
            coef = -coef;
        }

        // Парсим степени
        int px = 0, py = 0, pz = 0;

        // Парсим x
        if (pos < s.length() && s[pos] == 'x') {
            pos++;
            px = 1;
            if (pos < s.length() && s[pos] == '^') {
                pos++;
                std::string powerStr;
                while (pos < s.length() && std::isdigit(s[pos])) {
                    powerStr += s[pos];
                    pos++;
                }
                if (!powerStr.empty()) {
                    px = std::stoi(powerStr);
                }
            }
        }

        // Парсим y
        if (pos < s.length() && s[pos] == 'y') {
            pos++;
            py = 1;
            if (pos < s.length() && s[pos] == '^') {
                pos++;
                std::string powerStr;
                while (pos < s.length() && std::isdigit(s[pos])) {
                    powerStr += s[pos];
                    pos++;
                }
                if (!powerStr.empty()) {
                    py = std::stoi(powerStr);
                }
            }
        }

        // Парсим z
        if (pos < s.length() && s[pos] == 'z') {
            pos++;
            pz = 1;
            if (pos < s.length() && s[pos] == '^') {
                pos++;
                std::string powerStr;
                while (pos < s.length() && std::isdigit(s[pos])) {
                    powerStr += s[pos];
                    pos++;
                }
                if (!powerStr.empty()) {
                    pz = std::stoi(powerStr);
                }
            }
        }

        // Если нет переменных, это свободный член
        if (px == 0 && py == 0 && pz == 0 && coefStr.empty()) {
            coef = positive ? 1.0 : -1.0;
        }

        monoms.push_back(Monom(coef, px, py, pz));
    }

    return Polynom(monoms);
}

Polynom operator*(double num, const Polynom& p) {
    return p * num;
}