#pragma once
#include <string>
#include <cmath>

enum TypeLexem {
    Constant,
    Variable,  // Имя переменной
    OpenBracket,
    CloseBracket,
    Function,
    Operator,
    UnOperator,
    OpenedAbs,
    ClosedAbs
};

// Константы для ограничений
const int MAX_VARIABLE_LENGTH = 20;  // Максимальная длина имени переменной

struct Lexem {
    std::string name;
    TypeLexem type;
    double value; // Числовое значение (для констант)
    int priority;
    double (*function)(double);  // Указатель на математическую функцию (для лексем типа Function)

    Lexem(const std::string& _name = "", TypeLexem _type = Constant,double _value = 0.0, int _priority = -1, double(*_function)(double) = nullptr) : name(_name), type(_type), value(_value), priority(_priority), function(_function) {
    }

    bool isOperator() const {
        return type == Operator || type == UnOperator;
    }

    bool isFunction() const {
        return type == Function;
    }

    bool isBracket() const {
        return type == OpenBracket || type == CloseBracket;
    }

    bool isAbs() const {
        return type == OpenedAbs || type == ClosedAbs;
    }

    bool isNumber() const {
        return type == Constant;
    }

    bool isVariable() const {
        return type == Variable;
    }
};