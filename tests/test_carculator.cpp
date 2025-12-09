#include <gtest/gtest.h>
#include "parser.h"
#include "expression.h"
#include "functions.h"
#include <cmath>

TEST(ExpressionTest, ConstructorAndBasicEvaluation) {
    Expression expr("2 + 3 * 4");
    EXPECT_TRUE(expr.isValid());
    EXPECT_DOUBLE_EQ(expr.evaluate(), 14);
}

TEST(ExpressionTest, ExpressionWithVariables) {
    Expression expr("x + y * 2");
    EXPECT_TRUE(expr.isValid());
    EXPECT_FALSE(expr.isReady()); 

    expr.setVariable("x", 3);
    expr.setVariable("y", 4);
    EXPECT_TRUE(expr.isReady());
    EXPECT_DOUBLE_EQ(expr.evaluate(), 11);
}

TEST(ExpressionTest, EvaluateWithTemporaryValues) {
    Expression expr("a + b");
    expr.setVariable("a", 1);
    expr.setVariable("b", 2);

    std::map<std::string, double> tempVars = { {"a", 5}, {"b", 10} };
    EXPECT_DOUBLE_EQ(expr.evaluateWith(tempVars), 15);
}


TEST(ExpressionTest, GetVariableNames) {
    Expression expr("x + y + z");
    auto vars = expr.getVariableNames();
    EXPECT_EQ(vars.size(), 3);
}


TEST(ParserTest, ParseInvalidExpressionThrows) {
    EXPECT_THROW(Parser::parse("2 + * 3"), std::runtime_error);
}

TEST(ExpressionTest, DivisionByZeroThrows) {
    Expression expr("1 / 0");
    EXPECT_THROW(expr.evaluate(), std::runtime_error);
}


TEST(ExpressionTest, UndefinedVariableThrows) {
    Expression expr("x + 1");
    EXPECT_THROW(expr.evaluate(), std::runtime_error);
}

TEST(ExpressionTest, SetInvalidVariableThrows) {
    Expression expr("x + 1");
    EXPECT_THROW(expr.setVariable("y", 5), std::runtime_error);
}

TEST(ExpressionTest, UnaryMinus) {
    Expression expr("-5 + 3");
    EXPECT_DOUBLE_EQ(expr.evaluate(), -2);
}

TEST(ExpressionTest, GetOriginalExpression) {
    std::string exprStr = "x * y + 5";
    Expression expr(exprStr);
    EXPECT_EQ(expr.getExpression(), exprStr);
}
