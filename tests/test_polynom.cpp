#include "polynom.h"
#include "monom.h"
#include <gtest/gtest.h>
#include <cmath>
#include <limits>

TEST(MonomTest, ConstructorsAndBasicMethods) {
    Monom m0;
    EXPECT_DOUBLE_EQ(m0.getCoef(), 0.0);
    EXPECT_EQ(m0.getPx(), 0);
    EXPECT_EQ(m0.getPy(), 0);
    EXPECT_EQ(m0.getPz(), 0);

    Monom m1(3.0, 2, 1, 0);   // 3x²y
    EXPECT_DOUBLE_EQ(m1.getCoef(), 3.0);
    EXPECT_EQ(m1.getPx(), 2);
    EXPECT_EQ(m1.getPy(), 1);
    EXPECT_EQ(m1.getPz(), 0);

    Monom m1_copy(m1);
    EXPECT_TRUE(m1 == m1_copy);

    Monom m_assigned;
    m_assigned = m1;
    EXPECT_TRUE(m1 == m_assigned);

    m_assigned = m_assigned;
    EXPECT_TRUE(m1 == m_assigned);
}

TEST(MonomTest, SimilarityCheck) {
    Monom m1(3.0, 2, 1, 0);   // 3x²y
    Monom m2(2.0, 2, 1, 0);   // 2x²y
    Monom m3(4.0, 0, 0, 3);   // 4z³
    Monom m4(-5.0, 1, 2, 1);  // -5xy²z
    Monom m5(0.0, 3, 2, 1);   

    EXPECT_TRUE(m1.isSimilar(m2));

    EXPECT_FALSE(m1.isSimilar(m3));
    EXPECT_FALSE(m1.isSimilar(m4));
}

TEST(MonomTest, GetDegree) {
    Monom m1(3.0, 2, 1, 0);   // 3x²y
    Monom m3(4.0, 0, 0, 3);   // 4z³
    Monom m4(-5.0, 1, 2, 1);  // -5xy²z
    Monom m5(0.0, 3, 2, 1);  

    EXPECT_EQ(m1.getDegree(), 3);   // 2 + 1 + 0
    EXPECT_EQ(m3.getDegree(), 3);   // 0 + 0 + 3
    EXPECT_EQ(m4.getDegree(), 4);   // 1 + 2 + 1
    EXPECT_EQ(m5.getDegree(), 0);   
}

TEST(MonomTest, ComparisonOperators) {
    Monom m1(3.0, 2, 1, 0);   // 3x²y
    Monom m2(2.0, 2, 1, 0);   // 2x²y

    Monom m1_copy(3.0, 2, 1, 0);
    EXPECT_TRUE(m1 == m1_copy);
    EXPECT_FALSE(m1 != m1_copy);

    EXPECT_TRUE(m1 != m2);
    EXPECT_FALSE(m1 == m2);

    Monom m3(4.0, 0, 0, 3);   // 4z³
    EXPECT_TRUE(m1 != m3);

    Monom zero1(0.0, 0, 0, 0);
    Monom zero2(0.0, 3, 2, 1); 
    EXPECT_TRUE(zero1 == zero2);
}

TEST(MonomTest, ArithmeticOperationsWithSimilarMonomials) {
    Monom m1(3.0, 2, 1, 0);   // 3x²y
    Monom m2(2.0, 2, 1, 0);   // 2x²y
    Monom m5(0.0, 3, 2, 1);  

    Monom sum = m1 + m2;
    EXPECT_DOUBLE_EQ(sum.getCoef(), 5.0);
    EXPECT_TRUE(sum.isSimilar(m1));

    Monom diff = m1 - m2;
    EXPECT_DOUBLE_EQ(diff.getCoef(), 1.0);
    EXPECT_TRUE(diff.isSimilar(m1));
}
TEST(MonomTest, ArithmeticOperationsWithNonSimilarMonomialsThrows) {
    Monom m1(3.0, 2, 1, 0);   // 3x²y
    Monom m3(4.0, 0, 0, 3);   // 4z³
    Monom m4(-5.0, 1, 2, 1);  // -5xy²z
    Monom m5(0.0, 3, 2, 1);  

    EXPECT_THROW(m1 + m3, std::runtime_error);

    EXPECT_THROW(m1 - m3, std::runtime_error);

    EXPECT_NO_THROW(m1 * m3);
    EXPECT_THROW(m1 / m3, std::runtime_error);
}

TEST(MonomTest, Multiplication) {
    Monom m1(3.0, 2, 1, 0);   // 3x²y
    Monom m3(4.0, 0, 0, 3);   // 4z³
    Monom m5(0.0, 3, 2, 1);   

    Monom product = m1 * m3; // (3x²y) * (4z³) = 12x²yz³
    EXPECT_DOUBLE_EQ(product.getCoef(), 12.0);
    EXPECT_EQ(product.getPx(), 2);
    EXPECT_EQ(product.getPy(), 1);
    EXPECT_EQ(product.getPz(), 3);

    Monom zero_product = m1 * m5;
    EXPECT_DOUBLE_EQ(zero_product.getCoef(), 0.0);
    EXPECT_EQ(zero_product.getDegree(), 0);
}

TEST(MonomTest, Division) {
    Monom m1(3.0, 2, 1, 0);   // 3x²y
    Monom m4(-5.0, 1, 2, 1);  // -5xy²z
    Monom m5(0.0, 3, 2, 1);   
    Monom m6(6.0, 3, 2, 1);   // 6x³y²z
    Monom m7(2.0, 1, 1, 1);   // 2xyz

    Monom quotient = m6 / m7; // (6x³y²z) / (2xyz) = 3x²y
    EXPECT_DOUBLE_EQ(quotient.getCoef(), 3.0);
    EXPECT_EQ(quotient.getPx(), 2);
    EXPECT_EQ(quotient.getPy(), 1);
    EXPECT_EQ(quotient.getPz(), 0);

    EXPECT_THROW(m1 / m5, std::runtime_error);

    EXPECT_THROW(m1 / m4, std::runtime_error);
}

TEST(MonomTest, OperationsWithConstants) {
    Monom m1(3.0, 2, 1, 0);   // 3x²y

    Monom multiplied = m1 * 2.0;
    EXPECT_DOUBLE_EQ(multiplied.getCoef(), 6.0);
    EXPECT_TRUE(multiplied.isSimilar(m1));

    Monom divided = m1 / 2.0;
    EXPECT_DOUBLE_EQ(divided.getCoef(), 1.5);

    EXPECT_THROW(m1 / 0.0, std::runtime_error);
}

TEST(MonomTest, CompoundAssignmentOperators) {
    Monom m(3.0, 2, 1, 0);
    Monom similar(2.0, 2, 1, 0);

    m += similar;
    EXPECT_DOUBLE_EQ(m.getCoef(), 5.0);

    m -= similar;
    EXPECT_DOUBLE_EQ(m.getCoef(), 3.0);

    m *= similar;
    EXPECT_DOUBLE_EQ(m.getCoef(), 6.0);
    EXPECT_EQ(m.getPx(), 4);
    EXPECT_EQ(m.getPy(), 2);

    m *= 0.5;
    EXPECT_DOUBLE_EQ(m.getCoef(), 3.0);

    m /= 3.0;
    EXPECT_DOUBLE_EQ(m.getCoef(), 1.0);
}

TEST(MonomTest, UnaryMinus) {
    Monom m1(3.0, 2, 1, 0);   // 3x²y
    Monom m5(0.0, 3, 2, 1); 

    Monom negated = -m1;
    EXPECT_DOUBLE_EQ(negated.getCoef(), -3.0);
    EXPECT_TRUE(negated.isSimilar(m1));

    Monom double_neg = -(-m1);
    EXPECT_TRUE(double_neg == m1);

    Monom zero_neg = -m5;
    EXPECT_DOUBLE_EQ(zero_neg.getCoef(), 0.0);
}

TEST(MonomTest, Evaluation) {
    Monom m1(3.0, 2, 1, 0);   // 3x²y
    Monom m4(-5.0, 1, 2, 1);  // -5xy²z
    Monom m5(0.0, 3, 2, 1);  

    // m1 = 3x²y
    double value = m1.evaluate(2.0, 3.0, 5.0); // 3*(2²)*3 = 3*4*3 = 36
    EXPECT_DOUBLE_EQ(value, 36.0);

    // m4 = -5xy²z
    value = m4.evaluate(1.0, 2.0, 3.0); // -5*1*(2²)*3 = -5*1*4*3 = -60
    EXPECT_DOUBLE_EQ(value, -60.0);

    value = m5.evaluate(10.0, 20.0, 30.0);
    EXPECT_DOUBLE_EQ(value, 0.0);

    Monom constant(7.0, 0, 0, 0);
    value = constant.evaluate(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(value, 7.0);

    Monom m(2.0, 3, 0, 0); // 2x³
    value = m.evaluate(-2.0, 0.0, 0.0); // 2*(-8) = -16
    EXPECT_DOUBLE_EQ(value, -16.0);
}

TEST(MonomTest, StringRepresentation) {
    Monom m1(3.0, 2, 1, 0);   // 3x²y
    Monom m3(4.0, 0, 0, 3);   // 4z³
    Monom m4(-5.0, 1, 2, 1);  // -5xy²z
    Monom m5(0.0, 3, 2, 1);   

    EXPECT_EQ(m1.toString(), "3x^2y");
    EXPECT_EQ(m3.toString(), "4z^3");
    EXPECT_EQ(m4.toString(), "-5xy^2z");
    EXPECT_EQ(m5.toString(), "0");

    Monom m(1.0, 1, 0, 0); // x
    EXPECT_EQ(m.toString(), "x");

    Monom m_neg_one(-1.0, 1, 1, 0); // -xy
    EXPECT_EQ(m_neg_one.toString(), "-xy");

    Monom m_const(5.0, 0, 0, 0); // 5
    EXPECT_EQ(m_const.toString(), "5");
}

TEST(MonomTest, ComparisonForSorting) {
    Monom m_a(1.0, 3, 0, 0);  // x³
    Monom m_b(1.0, 2, 2, 0);  // x²y²
    Monom m_c(1.0, 2, 1, 1);  // x²yz
    Monom m_d(1.0, 1, 3, 0);  // xy³
    Monom m_e(1.0, 0, 0, 5);  // z⁵

    // x³ > x²y² > x²yz > xy³ > z⁵
    EXPECT_TRUE(m_a < m_b);
    EXPECT_TRUE(m_b < m_c);
    EXPECT_TRUE(m_c < m_d);
    EXPECT_TRUE(m_d < m_e);

    EXPECT_TRUE(m_b > m_a);
    EXPECT_TRUE(m_e > m_d);
}


TEST(PolynomTest, Constructors) {
    Polynom p1;
    EXPECT_EQ(p1.toString(), "0");

    Monom m1(3.5, 2, 1, 0);
    Polynom p2(m1);
    EXPECT_EQ(p2.toString(), "3.5x^2y");

    Monom m2(0.0, 2, 1, 0);
    Polynom p3(m2);
    EXPECT_EQ(p3.toString(), "0");

    std::vector<Monom> monoms = {
        Monom(2.0, 1, 0, 0),
        Monom(3.0, 0, 1, 0),
        Monom(4.0, 0, 0, 1)
    };
    Polynom p4(monoms);
    EXPECT_EQ(p4.toString(), "2x + 3y + 4z");

    Polynom p5(p4);
    EXPECT_EQ(p5.toString(), "2x + 3y + 4z");

    Polynom p6("2*x + 3*y - 4*z^2");
    EXPECT_EQ(p6.toString(), "2x + 3y - 4z^2");
}

TEST(PolynomTest, AssignmentOperator) {
    Polynom p1("2*x + 3*y");
    Polynom p2;
    p2 = p1;
    EXPECT_EQ(p2.toString(), "2*x + 3*y");
    // Самоприсваивание
    p2 = p2;
    EXPECT_EQ(p2.toString(), "2*x + 3*y");
}

TEST(PolynomTest, Simplify) {
    std::vector<Monom> monoms = {
        Monom(2.0, 1, 0, 0),
        Monom(3.0, 1, 0, 0),
        Monom(-5.0, 1, 0, 0),
        Monom(4.0, 2, 0, 0)
    };
    Polynom p(monoms);
    EXPECT_EQ(p.toString(), "4*x^2"); // 2x + 3x - 5x = 0

    Polynom p2("2*x - 2*x");
    EXPECT_EQ(p2.toString(), "0");
}

TEST(PolynomTest, Sort) {
    std::vector<Monom> monoms = {
        Monom(5.0, 0, 0, 2),
        Monom(2.0, 2, 0, 0),
        Monom(3.0, 1, 1, 0),
        Monom(1.0, 0, 1, 1)
    };
    Polynom p(monoms);
    EXPECT_EQ(p.toString(), "2*x^2 + 3*x*y + 1*y*z + 5*z^2");
}

TEST(PolynomTest, AddMonom) {
    Polynom p;
    p.addMonom(Monom(2.5, 2, 0, 0));
    EXPECT_EQ(p.toString(), "2.5*x^2");

    p.addMonom(Monom(1.5, 2, 0, 0));
    EXPECT_EQ(p.toString(), "4*x^2");

    p.addMonom(Monom(-4.0, 2, 0, 0));
    EXPECT_EQ(p.toString(), "0");

    p.addMonom(Monom(3.0, 1, 1, 0));
    EXPECT_EQ(p.toString(), "3*x*y");
}

TEST(PolynomTest, ComparisonOperators) {
    Polynom p1("2*x + 3*y");
    Polynom p2("2*x + 3*y");
    Polynom p3("2*x + 4*y");

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 != p2);
    EXPECT_TRUE(p1 != p3);
    EXPECT_FALSE(p1 == p3);
}
TEST(PolynomTest, Addition) {
    Polynom p1("2*x + 3*y");
    Polynom p2("4*x - y");
    Polynom result = p1 + p2;
    EXPECT_EQ(result.toString(), "6*x + 2*y");

    Polynom zero;
    result = p1 + zero;
    EXPECT_EQ(result.toString(), "2*x + 3*y");

    Polynom p3("2*x + 5*x");
    Polynom p4("3*x - 2*x");
    result = p3 + p4;
    EXPECT_EQ(result.toString(), "8*x");
}

TEST(PolynomTest, Subtraction) {
    Polynom p1("2*x + 3*y");
    Polynom p2("4*x - y");
    Polynom result = p1 - p2;
    EXPECT_EQ(result.toString(), "-2*x + 4*y");

    Polynom zero;
    result = p1 - zero;
    EXPECT_EQ(result.toString(), "2*x + 3*y");
}

TEST(PolynomTest, Multiplication) {
    Polynom p1("2*x + 3*y");
    Polynom p2("4*x - y");
    Polynom result = p1 * p2;
    EXPECT_EQ(result.toString(), "8*x^2 + 12*x*y - 2*x*y - 3*y^2");

    Polynom zero;
    result = p1 * zero;
    EXPECT_EQ(result.toString(), "0");

    Polynom p3("2*x");
    Polynom p4("3*y");
    result = p3 * p4;
    EXPECT_EQ(result.toString(), "6*x*y");
}

TEST(PolynomTest, MultiplicationByScalar) {
    Polynom p("2*x + 3*y - 4*z");

    Polynom result = p * 2.0;
    EXPECT_EQ(result.toString(), "4*x + 6*y - 8*z");

    result = p * 0.0;
    EXPECT_EQ(result.toString(), "0");

    result = p * (-1.5);
    EXPECT_EQ(result.toString(), "-3*x - 4.5*y + 6*z");

    result = 2.0 * p;
    EXPECT_EQ(result.toString(), "4*x + 6*y - 8*z");
}

TEST(PolynomTest, DivisionByScalar) {
    Polynom p("4*x + 6*y - 8*z");

    Polynom result = p / 2.0;
    EXPECT_EQ(result.toString(), "2*x + 3*y - 4*z");

    result = p / (-2.0);
    EXPECT_EQ(result.toString(), "-2*x - 3*y + 4*z");

    EXPECT_THROW(p / 0.0, std::runtime_error);
}

TEST(PolynomTest, CompoundAssignment) {
    Polynom p1("2*x + 3*y");
    Polynom p2("4*x - y");

    p1 += p2;
    EXPECT_EQ(p1.toString(), "6*x + 2*y");

    p1 -= p2;
    EXPECT_EQ(p1.toString(), "2*x + 3*y");

    p1 *= p2;
    EXPECT_EQ(p1.toString(), "8*x^2 + 12*x*y - 2*x*y - 3*y^2");

    Polynom p3("2*x");
    p3 *= 3.0;
    EXPECT_EQ(p3.toString(), "6*x");

    p3 /= 2.0;
    EXPECT_EQ(p3.toString(), "3*x");

    EXPECT_THROW(p3 /= 0.0, std::runtime_error);
}

TEST(PolynomTest, UnaryMinus) {
    Polynom p("2*x - 3*y + 4*z");
    Polynom neg = -p;
    EXPECT_EQ(neg.toString(), "-2*x + 3*y - 4*z");

    Polynom zero;
    neg = -zero;
    EXPECT_EQ(neg.toString(), "0");
}

TEST(PolynomTest, Evaluate) {
    Polynom p("2*x + 3*y - 4*z");

    EXPECT_DOUBLE_EQ(p.evaluate(1, 1, 1), 2 * 1 + 3 * 1 - 4 * 1); // = 1
}

TEST(PolynomTest, StreamOperators) {
    Polynom p("2*x + 3*y");

    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "2*x + 3*y");

    std::stringstream ss2("4*x^2 - 5*y*z");
    ss2 >> p;
    EXPECT_EQ(p.toString(), "4*x^2 - 5*y*z");

    Polynom zero;
    ss.str("");
    ss << zero;
    EXPECT_EQ(ss.str(), "0");
}

TEST(PolynomTest, ToString) {
    Polynom p1("2*x + 3*y - 4*z");
    EXPECT_EQ(p1.toString(), "2*x + 3*y - 4*z");

    Polynom p2;
    EXPECT_EQ(p2.toString(), "0");

    Polynom p3("x + y + z");
    EXPECT_EQ(p3.toString(), "1*x + 1*y + 1*z");
}

TEST(PolynomTest, Parse) {
    // Простые полиномы
    Polynom p1 = Polynom::parse("2*x + 3*y");
    EXPECT_EQ(p1.toString(), "2*x + 3*y");

    // Полином с отрицательными коэффициентами
    Polynom p2 = Polynom::parse("2*x - 3*y + 4*z");
    EXPECT_EQ(p2.toString(), "2*x - 3*y + 4*z");

    // Полином со степенями
    Polynom p3 = Polynom::parse("2*x^2 + 3*x*y - 4*z^3");
    EXPECT_EQ(p3.toString(), "2*x^2 + 3*x*y - 4*z^3");

    // Полином с коэффициентом 1
    Polynom p4 = Polynom::parse("x + y + z");
    EXPECT_EQ(p4.toString(), "1*x + 1*y + 1*z");

    // Пустой полином
    Polynom p5 = Polynom::parse("");
    EXPECT_EQ(p5.toString(), "0");
}