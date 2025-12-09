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
    std::string originalExpression; 
    List<Lexem> infixNotation; // список лексем
    List<Lexem> postfixNotation;  // обратная польская запись
    std::map<std::string, double> variables; // Содержит значения переменных выражения
    bool isParsed;
    bool isPostfixReady;

    List<Lexem> toPostfix(const List<Lexem>& infix); 
    double evaluatePostfix(const List<Lexem>& postfix, const std::map<std::string, double> &vars); 

public:
    Expression();
    Expression(const std::string& expr);  // Вызывает setExpression() для парсинга

    void setExpression(const std::string& expr);
    void setVariable(const std::string& name, double value);
    void setVariables(const std::map<std::string, double> &vars);

    std::string getExpression() const;
    std::vector<std::string> getVariableNames() const;
    bool hasVariable(const std::string& name) const; // Проверяет, используется ли указанная переменная в выражении
    double getVariableValue(const std::string& name) const;
    std::string getVariablesString() const;   // Возвращает строку со всеми переменными и их значениями

    double evaluate();
    double evaluateWith(const std::map<std::string, double>& vars);

    bool isValid() const; // выражение распарсено или нет
    bool isReady() const; // готово ли выражение к вычислению
};