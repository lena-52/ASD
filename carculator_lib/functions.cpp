#include "functions.h"
#include <cmath>
#include <limits>
#include <iostream>
const double PI = 3.14159265358979323846;

namespace Functions {

    // Ряд Тейлора для sin(x)  x - x^3/3! + x^5/5! - x^7/7! + ...
    double my_sin(double x) {
        x = fmod(x, 2 * PI); //приведение аргумента к диапазону[0, 2π)

        double result = 0.0;
        double term = x;
        double x_sq = x * x;

        for (int i = 1; i <= 10; i++) {
            result += term;
            term *= -x_sq / ((2 * i) * (2 * i + 1));
        }

        return result;
    }

    // Ряд Тейлора для cos(x) 1 - x^2/2! + x^4/4! - x^6/6! + ...
    double my_cos(double x) {
        x = fmod(x, 2 * PI);

        double result = 1.0;
        double term = 1.0;
        double x_sq = x * x;

        for (int i = 1; i <= 10; i++) {
            term *= -x_sq / ((2 * i - 1) * (2 * i));
            result += term;
        }

        return result;
    }

    // tg(x) = sin(x)/cos(x)
    double my_tg(double x) {
        double cos_val = my_cos(x);
        // Проверка деления на ноль 
        if (fabs(cos_val) < 1e-10) {
            throw std::runtime_error("Тангенс не определен для этого угла");
        }
        return my_sin(x) / cos_val;
    }

    double my_abs(double x) {
        return (x < 0) ? -x : x;
    }

    double my_pow(double base, double exp) {
        // Проверяем, целый ли показатель
        double intpart;
        if (modf(exp, &intpart) != 0.0) { // Если дробная часть не равна 0.0 - показатель не целый
            throw std::runtime_error("Показатель степени должен быть целым");
        }

        int n = static_cast<int>(exp);
        double result = 1.0;
        bool negative = (n < 0); // Флаг отрицательной степени

        if (negative) {   // Если степень отрицательная, работаем с положительной
            n = -n; 
        }

        for (int i = 0; i < n; i++) {
            result *= base;
        }
        //учитываем отрицательную степень
        return negative ? 1.0 / result : result;
    }
}