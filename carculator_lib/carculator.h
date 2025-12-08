#pragma once
#include "expression.h"
#include "vector.h"
#include <string>
#include <map>

class Calculator {
private:
    TVector<Expression> expressions;

    // Вспомогательные функции для меню
    void createExpression();
    void deleteExpression();
    void setVariables();
    void evaluateExpression();
    void displayAllExpressions() const;
    static std::map<std::string, double> inputVariables(const std::vector<std::string>& varNames);

public:
    void run();
};