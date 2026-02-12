#include "polynom.h"
#include "monom.h"
#include <gtest/gtest.h>
#include <cmath>
#include <limits>

TEST(MonomTest, ConstructorsAndBasicMethods) {
    // Конструктор по умолчанию
    Monom m0;
    EXPECT_DOUBLE_EQ(m0.getCoef(), 0.0);
    EXPECT_EQ(m0.getPx(), 0);
    EXPECT_EQ(m0.getPy(), 0);
    EXPECT_EQ(m0.getPz(), 0);

    // Параметризованный конструктор
    Monom m1(3.0, 2, 1, 0);   // 3x²y
    EXPECT_DOUBLE_EQ(m1.getCoef(), 3.0);
    EXPECT_EQ(m1.getPx(), 2);
    EXPECT_EQ(m1.getPy(), 1);
    EXPECT_EQ(m1.getPz(), 0);

    // Конструктор копирования
    Monom m1_copy(m1);
    EXPECT_TRUE(m1 == m1_copy);

    // Оператор присваивания
    Monom m_assigned;
    m_assigned = m1;
    EXPECT_TRUE(m1 == m_assigned);

    // Самоприсваивание
    m_assigned = m_assigned;
    EXPECT_TRUE(m1 == m_assigned);
}

TEST(MonomTest, SimilarityCheck) {
    Monom m1(3.0, 2, 1, 0);   // 3x²y
    Monom m2(2.0, 2, 1, 0);   // 2x²y
    Monom m3(4.0, 0, 0, 3);   // 4z³
    Monom m4(-5.0, 1, 2, 1);  // -5xy²z
    Monom m5(0.0, 3, 2, 1);   // Нулевой моном

    // Подобные мономы
    EXPECT_TRUE(m1.isSimilar(m2));

    // Неподобные мономы
    EXPECT_FALSE(m1.isSimilar(m3));
    EXPECT_FALSE(m1.isSimilar(m4));
}

TEST(MonomTest, GetDegree) {
    Monom m1(3.0, 2, 1, 0);   // 3x²y
    Monom m3(4.0, 0, 0, 3);   // 4z³
    Monom m4(-5.0, 1, 2, 1);  // -5xy²z
    Monom m5(0.0, 3, 2, 1);   // Нулевой моном

    EXPECT_EQ(m1.getDegree(), 3);   // 2 + 1 + 0
    EXPECT_EQ(m3.getDegree(), 3);   // 0 + 0 + 3
    EXPECT_EQ(m4.getDegree(), 4);   // 1 + 2 + 1
    EXPECT_EQ(m5.getDegree(), 0);   // Нулевой моном
}

TEST(MonomTest, ComparisonOperators) {
    Monom m1(3.0, 2, 1, 0);   // 3x²y
    Monom m2(2.0, 2, 1, 0);   // 2x²y

    // Равенство
    Monom m1_copy(3.0, 2, 1, 0);
    EXPECT_TRUE(m1 == m1_copy);
    EXPECT_FALSE(m1 != m1_copy);

    // Неравенство (разные коэффициенты)
    EXPECT_TRUE(m1 != m2);
    EXPECT_FALSE(m1 == m2);

    // Неравенство (разные степени)
    Monom m3(4.0, 0, 0, 3);   // 4z³
    EXPECT_TRUE(m1 != m3);

    // Все нулевые мономы равны
    Monom zero1(0.0, 0, 0, 0);
    Monom zero2(0.0, 3, 2, 1); // Степени игнорируются при нулевом коэффициенте
    EXPECT_TRUE(zero1 == zero2);
}

TEST(MonomTest, ArithmeticOperationsWithSimilarMonomials) {
    Monom m1(3.0, 2, 1, 0);   // 3x²y
    Monom m2(2.0, 2, 1, 0);   // 2x²y
    Monom m5(0.0, 3, 2, 1);   // Нулевой моном

    // Сложение
    Monom sum = m1 + m2;
    EXPECT_DOUBLE_EQ(sum.getCoef(), 5.0);
    EXPECT_TRUE(sum.isSimilar(m1));

    // Вычитание
    Monom diff = m1 - m2;
    EXPECT_DOUBLE_EQ(diff.getCoef(), 1.0);
    EXPECT_TRUE(diff.isSimilar(m1));
}

// Тест арифметических операций с неподобными мономами
TEST(MonomTest, ArithmeticOperationsWithNonSimilarMonomialsThrows) {
    Monom m1(3.0, 2, 1, 0);   // 3x²y
    Monom m3(4.0, 0, 0, 3);   // 4z³
    Monom m4(-5.0, 1, 2, 1);  // -5xy²z
    Monom m5(0.0, 3, 2, 1);   // Нулевой моном

    // Сложение неподобных должно выбрасывать исключение
    EXPECT_THROW(m1 + m3, std::runtime_error);

    // Вычитание неподобных должно выбрасывать исключение
    EXPECT_THROW(m1 - m3, std::runtime_error);

    // Но умножение и деление работают
    EXPECT_NO_THROW(m1 * m3);
    EXPECT_THROW(m1 / m3, std::runtime_error);
}

TEST(MonomTest, Multiplication) {
    Monom m1(3.0, 2, 1, 0);   // 3x²y
    Monom m3(4.0, 0, 0, 3);   // 4z³
    Monom m5(0.0, 3, 2, 1);   // Нулевой моном

    Monom product = m1 * m3; // (3x²y) * (4z³) = 12x²yz³
    EXPECT_DOUBLE_EQ(product.getCoef(), 12.0);
    EXPECT_EQ(product.getPx(), 2);
    EXPECT_EQ(product.getPy(), 1);
    EXPECT_EQ(product.getPz(), 3);

    // Умножение на ноль
    Monom zero_product = m1 * m5;
    EXPECT_DOUBLE_EQ(zero_product.getCoef(), 0.0);
    EXPECT_EQ(zero_product.getDegree(), 0);
}

TEST(MonomTest, Division) {
    Monom m1(3.0, 2, 1, 0);   // 3x²y
    Monom m4(-5.0, 1, 2, 1);  // -5xy²z
    Monom m5(0.0, 3, 2, 1);   // Нулевой моном
    Monom m6(6.0, 3, 2, 1);   // 6x³y²z
    Monom m7(2.0, 1, 1, 1);   // 2xyz

    Monom quotient = m6 / m7; // (6x³y²z) / (2xyz) = 3x²y
    EXPECT_DOUBLE_EQ(quotient.getCoef(), 3.0);
    EXPECT_EQ(quotient.getPx(), 2);
    EXPECT_EQ(quotient.getPy(), 1);
    EXPECT_EQ(quotient.getPz(), 0);

    // Деление на ноль
    EXPECT_THROW(m1 / m5, std::runtime_error);

    // Деление, приводящее к отрицательным степеням
    EXPECT_THROW(m1 / m4, std::runtime_error);
}

TEST(MonomTest, OperationsWithConstants) {
    Monom m1(3.0, 2, 1, 0);   // 3x²y

    // Умножение на константу справа
    Monom multiplied = m1 * 2.0;
    EXPECT_DOUBLE_EQ(multiplied.getCoef(), 6.0);
    EXPECT_TRUE(multiplied.isSimilar(m1));

    // Умножение на константу слева
    Monom multiplied_left = 2.0 * m1;
    EXPECT_DOUBLE_EQ(multiplied_left.getCoef(), 6.0);

    // Деление на константу
    Monom divided = m1 / 2.0;
    EXPECT_DOUBLE_EQ(divided.getCoef(), 1.5);

    // Деление на ноль
    EXPECT_THROW(m1 / 0.0, std::runtime_error);
}

TEST(MonomTest, CompoundAssignmentOperators) {
    Monom m(3.0, 2, 1, 0);
    Monom similar(2.0, 2, 1, 0);

    // +=
    m += similar;
    EXPECT_DOUBLE_EQ(m.getCoef(), 5.0);

    // -=
    m -= similar;
    EXPECT_DOUBLE_EQ(m.getCoef(), 3.0);

    // *=
    m *= similar;
    EXPECT_DOUBLE_EQ(m.getCoef(), 6.0);
    EXPECT_EQ(m.getPx(), 4);
    EXPECT_EQ(m.getPy(), 2);

    // *= с константой
    m *= 0.5;
    EXPECT_DOUBLE_EQ(m.getCoef(), 3.0);

    // /= с константой
    m /= 3.0;
    EXPECT_DOUBLE_EQ(m.getCoef(), 1.0);
}

TEST(MonomTest, UnaryMinus) {
    Monom m1(3.0, 2, 1, 0);   // 3x²y
    Monom m5(0.0, 3, 2, 1);   // Нулевой моном

    Monom negated = -m1;
    EXPECT_DOUBLE_EQ(negated.getCoef(), -3.0);
    EXPECT_TRUE(negated.isSimilar(m1));

    // Двойное отрицание
    Monom double_neg = -(-m1);
    EXPECT_TRUE(double_neg == m1);

    // Отрицание нуля
    Monom zero_neg = -m5;
    EXPECT_DOUBLE_EQ(zero_neg.getCoef(), 0.0);
}

TEST(MonomTest, Evaluation) {
    Monom m1(3.0, 2, 1, 0);   // 3x²y
    Monom m4(-5.0, 1, 2, 1);  // -5xy²z
    Monom m5(0.0, 3, 2, 1);   // Нулевой моном

    // m1 = 3x²y
    double value = m1.evaluate(2.0, 3.0, 5.0); // 3*(2²)*3 = 3*4*3 = 36
    EXPECT_DOUBLE_EQ(value, 36.0);

    // m4 = -5xy²z
    value = m4.evaluate(1.0, 2.0, 3.0); // -5*1*(2²)*3 = -5*1*4*3 = -60
    EXPECT_DOUBLE_EQ(value, -60.0);

    // Нулевой моном
    value = m5.evaluate(10.0, 20.0, 30.0);
    EXPECT_DOUBLE_EQ(value, 0.0);

    // Степени 0
    Monom constant(7.0, 0, 0, 0);
    value = constant.evaluate(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(value, 7.0);

    // Отрицательные значения переменных
    Monom m(2.0, 3, 0, 0); // 2x³
    value = m.evaluate(-2.0, 0.0, 0.0); // 2*(-8) = -16
    EXPECT_DOUBLE_EQ(value, -16.0);
}

TEST(MonomTest, StringRepresentation) {
    Monom m1(3.0, 2, 1, 0);   // 3x²y
    Monom m3(4.0, 0, 0, 3);   // 4z³
    Monom m4(-5.0, 1, 2, 1);  // -5xy²z
    Monom m5(0.0, 3, 2, 1);   // Нулевой моном

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

// Тест операторов сравнения для сортировки
TEST(MonomTest, ComparisonForSorting) {
    // Проверка лексикографического порядка
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

    // Обратные проверки
    EXPECT_TRUE(m_b > m_a);
    EXPECT_TRUE(m_e > m_d);
}

class PolynomTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Создаем тестовые полиномы
        poly1.addMonom(Monom(3.0, 2, 1, 0));  // 3x²y
        poly1.addMonom(Monom(2.0, 0, 0, 3));  // 2z³
        poly1.addMonom(Monom(-1.0, 1, 0, 1)); // -xz

        poly2.addMonom(Monom(1.0, 2, 1, 0));  // x²y
        poly2.addMonom(Monom(-2.0, 0, 0, 3)); // -2z³
        poly2.addMonom(Monom(3.0, 1, 0, 1));  // 3xz

        poly3.addMonom(Monom(1.0, 1, 0, 0));  // x
        poly3.addMonom(Monom(1.0, 0, 1, 0));  // y
    }

    Polynom poly1, poly2, poly3;
    Polynom empty_poly;
};

TEST_F(PolynomTest, Constructors) {
    // Конструктор по умолчанию
    EXPECT_TRUE(empty_poly.isEmpty());

    // Конструктор из монома
    Polynom from_monom(Monom(5.0, 1, 2, 0));
    EXPECT_FALSE(from_monom.isEmpty());
    EXPECT_EQ(from_monom.getMonoms().size(), 1);

    // Конструктор из вектора мономов
    std::vector<Monom> monoms = { Monom(1.0, 1, 0, 0), Monom(2.0, 0, 1, 0) };
    Polynom from_vector(monoms);
    EXPECT_EQ(from_vector.getMonoms().size(), 2);

    // Конструктор копирования
    Polynom copy(poly1);
    EXPECT_TRUE(poly1 == copy);

    // Оператор присваивания
    Polynom assigned;
    assigned = poly1;
    EXPECT_TRUE(poly1 == assigned);

    // Самоприсваивание
    assigned = assigned;
    EXPECT_TRUE(poly1 == assigned);
}

TEST_F(PolynomTest, Simplification) {
    Polynom p;
    p.addMonom(Monom(2.0, 2, 0, 0));  // 2x²
    p.addMonom(Monom(3.0, 1, 1, 0));  // 3xy
    p.addMonom(Monom(-2.0, 2, 0, 0)); // -2x² (должен сократиться)
    p.addMonom(Monom(1.0, 1, 1, 0));  // xy (должен объединиться с 3xy)

    // После упрощения должно быть: 4xy
    EXPECT_EQ(p.getMonoms().size(), 1);
    EXPECT_TRUE(p.getMonoms()[0] == Monom(4.0, 1, 1, 0));

    // Полином только с нулевыми мономами должен стать пустым
    Polynom zero_poly;
    zero_poly.addMonom(Monom(0.0, 3, 2, 1));
    zero_poly.addMonom(Monom(0.0, 1, 0, 0));
    EXPECT_TRUE(zero_poly.isEmpty());
}

// Тест сортировки мономов в полиноме
TEST_F(PolynomTest, Sorting) {
    Polynom p;
    // Добавляем в произвольном порядке
    p.addMonom(Monom(1.0, 0, 2, 1));  // y²z
    p.addMonom(Monom(2.0, 0, 2, 0));  // 2y²
    p.addMonom(Monom(1.0, 1, 1, 0));  // xy
    p.addMonom(Monom(6.0, 0, 0, 0));  // 6

    const auto& monoms = p.getMonoms();
    // Должны быть отсортированы: xy, y²z, 2y², 6
    EXPECT_EQ(monoms.size(), 4);

    // Проверяем порядок
    EXPECT_TRUE(monoms[0] == Monom(1.0, 1, 1, 0));   // xy (первый - наибольшая степень x)
    EXPECT_TRUE(monoms[1] == Monom(1.0, 0, 2, 1));   // y²z
    EXPECT_TRUE(monoms[2] == Monom(2.0, 0, 2, 0));   // 2y²
    EXPECT_TRUE(monoms[3] == Monom(6.0, 0, 0, 0));   // 6
}

TEST_F(PolynomTest, Addition) {
    Polynom sum = poly1 + poly2;

    // poly1: 3x²y + 2z³ - xz
    // poly2: x²y - 2z³ + 3xz
    // sum: 4x²y + 0z³ + 2xz = 4x²y + 2xz

    EXPECT_EQ(sum.getMonoms().size(), 2);

    // Проверяем наличие мономов
    bool has_4x2y = false, has_2xz = false;
    for (const auto& m : sum.getMonoms()) {
        if (m == Monom(4.0, 2, 1, 0)) has_4x2y = true;
        if (m == Monom(2.0, 1, 0, 1)) has_2xz = true;
    }
    EXPECT_TRUE(has_4x2y);
    EXPECT_TRUE(has_2xz);

    // Сложение с пустым полиномом
    Polynom sum_with_empty = poly1 + empty_poly;
    EXPECT_TRUE(poly1 == sum_with_empty);

    // Оператор +=
    Polynom p = poly1;
    p += poly2;
    EXPECT_TRUE(p == sum);
}

TEST_F(PolynomTest, Subtraction) {
    Polynom diff = poly1 - poly2;

    // poly1: 3x²y + 2z³ - xz
    // poly2: x²y - 2z³ + 3xz
    // diff: 2x²y + 4z³ - 4xz

    bool has_2x2y = false, has_4z3 = false, has_minus_4xz = false;
    for (const auto& m : diff.getMonoms()) {
        if (m == Monom(2.0, 2, 1, 0)) has_2x2y = true;
        if (m == Monom(4.0, 0, 0, 3)) has_4z3 = true;
        if (m == Monom(-4.0, 1, 0, 1)) has_minus_4xz = true;
    }
    EXPECT_TRUE(has_2x2y);
    EXPECT_TRUE(has_4z3);
    EXPECT_TRUE(has_minus_4xz);

    // Вычитание самого себя дает пустой полином
    Polynom self_diff = poly1 - poly1;
    EXPECT_TRUE(self_diff.isEmpty());

    // Оператор -=
    Polynom p = poly1;
    p -= poly2;
    EXPECT_TRUE(p == diff);
}

TEST_F(PolynomTest, Multiplication) {
    // poly3: x + y
    Polynom square = poly3 * poly3; // (x + y)² = x² + 2xy + y²

    EXPECT_EQ(square.getMonoms().size(), 3);

    // Проверяем все мономы
    bool has_x2 = false, has_2xy = false, has_y2 = false;
    for (const auto& m : square.getMonoms()) {
        if (m == Monom(1.0, 2, 0, 0)) has_x2 = true;
        if (m == Monom(2.0, 1, 1, 0)) has_2xy = true;
        if (m == Monom(1.0, 0, 2, 0)) has_y2 = true;
    }
    EXPECT_TRUE(has_x2);
    EXPECT_TRUE(has_2xy);
    EXPECT_TRUE(has_y2);

    // Умножение на пустой полином
    Polynom empty_product = poly1 * empty_poly;
    EXPECT_TRUE(empty_product.isEmpty());

    // Умножение на константу
    Polynom doubled = poly3 * 2.0;
    bool has_2x = false, has_2y = false;
    for (const auto& m : doubled.getMonoms()) {
        if (m == Monom(2.0, 1, 0, 0)) has_2x = true;
        if (m == Monom(2.0, 0, 1, 0)) has_2y = true;
    }
    EXPECT_TRUE(has_2x);
    EXPECT_TRUE(has_2y);

    // Умножение константы на полином слева
    Polynom tripled = 3.0 * poly3;
    bool has_3x = false, has_3y = false;
    for (const auto& m : tripled.getMonoms()) {
        if (m == Monom(3.0, 1, 0, 0)) has_3x = true;
        if (m == Monom(3.0, 0, 1, 0)) has_3y = true;
    }
    EXPECT_TRUE(has_3x);
    EXPECT_TRUE(has_3y);
}

TEST_F(PolynomTest, DivisionByConstant) {
    Polynom p;
    p.addMonom(Monom(4.0, 2, 0, 0));  // 4x²
    p.addMonom(Monom(2.0, 1, 1, 0));  // 2xy

    Polynom divided = p / 2.0;

    bool has_2x2 = false, has_xy = false;
    for (const auto& m : divided.getMonoms()) {
        if (m == Monom(2.0, 2, 0, 0)) has_2x2 = true;
        if (m == Monom(1.0, 1, 1, 0)) has_xy = true;
    }
    EXPECT_TRUE(has_2x2);
    EXPECT_TRUE(has_xy);

    // Деление на ноль должно выбрасывать исключение
    EXPECT_THROW(p / 0.0, std::runtime_error);
}

TEST_F(PolynomTest, UnaryMinus) {
    Polynom negated = -poly1;

    // Все коэффициенты должны быть противоположными
    const auto& orig_monoms = poly1.getMonoms();
    const auto& neg_monoms = negated.getMonoms();

    EXPECT_EQ(orig_monoms.size(), neg_monoms.size());

    for (size_t i = 0; i < orig_monoms.size(); i++) {
        EXPECT_DOUBLE_EQ(neg_monoms[i].getCoef(), -orig_monoms[i].getCoef());
        EXPECT_TRUE(neg_monoms[i].isSimilar(orig_monoms[i]));
    }

    // Двойное отрицание
    Polynom double_neg = -(-poly1);
    EXPECT_TRUE(poly1 == double_neg);
}

//  вычисление значения полинома
TEST_F(PolynomTest, Evaluation) {
    // poly3: x + y
    double value = poly3.evaluate(2.0, 3.0, 5.0); // 2 + 3 = 5
    EXPECT_DOUBLE_EQ(value, 5.0);

    // Пустой полином
    value = empty_poly.evaluate(1.0, 2.0, 3.0);
    EXPECT_DOUBLE_EQ(value, 0.0);

    // Полином с отрицательными значениями
    Polynom p;
    p.addMonom(Monom(2.0, 1, 0, 0));  // 2x
    p.addMonom(Monom(-3.0, 0, 1, 0)); // -3y
    value = p.evaluate(-1.0, 2.0, 0.0); // 2*(-1) + (-3)*2 = -2 - 6 = -8
    EXPECT_DOUBLE_EQ(value, -8.0);
}

TEST_F(PolynomTest, InputOutputOperators) {
    EXPECT_NO_THROW(std::cout << poly3);

    std::stringstream ss;
    EXPECT_NO_THROW(ss << poly3);

    EXPECT_FALSE(ss.str().empty());
}

TEST_F(PolynomTest, StringParsing) {
    // Простой тест парсинга
    Polynom p("2x^2 + 3y - 4z");
    EXPECT_FALSE(p.isEmpty());

    // Проверяем, что мономы были добавлены
    EXPECT_GT(p.getMonoms().size(), 0);

    // Тест для константы
    Polynom constant("5");
    EXPECT_FALSE(constant.isEmpty());

    // Тест для пустой строки или строки только с нулями
    Polynom empty("");
}

TEST_F(PolynomTest, EdgeCases) {
    // Полином с очень большими/маленькими коэффициентами
    Polynom extreme;
    extreme.addMonom(Monom(1e308, 1, 0, 0));
    extreme.addMonom(Monom(-1e308, 1, 0, 0));

    // После упрощения должен получиться пустой полином
    extreme.simplify();
    EXPECT_TRUE(extreme.isEmpty());

    // Много мономов
    Polynom large;
    for (int i = 0; i < 100; i++) {
        large.addMonom(Monom(1.0, i % 3, (i + 1) % 3, (i + 2) % 3));
    }
    EXPECT_NO_THROW(large.simplify());
}