#pragma once
#include "lexem.h"
#include "list.h"
#include "stack.h"
#include "vector.h"
#include <string>
#include <map>
#include <vector>
#include <limits>

class Expression {
private:
    std::string originalExpression;
    List<Lexem> infixNotation;
    List<Lexem> postfixNotation;
    std::map<std::string, double> variables;
    bool isParsed;
    bool isPostfixReady;

    // Вспомогательные функции
    List<Lexem> toPostfix(const List<Lexem>& infix);
    double evaluatePostfix(const List<Lexem>& postfix,
        const std::map<std::string, double>& vars);

public:
    Expression();
    Expression(const std::string& expr);

    // Установка выражения
    void setExpression(const std::string& expr);

    // Установка значений переменных
    void setVariable(const std::string& name, double value);
    void setVariables(const std::map<std::string, double>& vars);

    // Получение информации
    std::string getExpression() const;
    std::vector<std::string> getVariableNames() const;
    bool hasVariable(const std::string& name) const;
    double getVariableValue(const std::string& name) const;
    std::string getVariablesString() const;  // Новый метод для получения строки со значениями

    // Вычисление
    double evaluate();
    double evaluateWith(const std::map<std::string, double>& vars);

    // Проверки
    bool isValid() const;
    bool isReady() const; // все переменные заданы
};