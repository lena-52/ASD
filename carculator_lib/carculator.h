#pragma once
#include "expression.h"
#include "vector.h"
#include <string>
#include <map>

class Calculator {
    TVector<Expression> expressions;

    void createExpression();
    void deleteExpression();
    void setVariables();
    void evaluateExpression();
    void displayAllExpressions() const;
public:
    void run();
};