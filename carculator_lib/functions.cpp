#include "functions.h"
#include <cmath>
#include <limits>
#include <iostream>

namespace Functions {

    // Ряд Тейлора для sin(x)
    double my_sin(double x) {
        const double PI = 3.14159265358979323846;
        x = fmod(x, 2 * PI);

        double result = 0.0;
        double term = x;
        double x_sq = x * x;
        int n = 1;

        for (int i = 1; i <= 10; i++) {
            result += term;
            term *= -x_sq / ((2 * i) * (2 * i + 1));
        }

        return result;
    }

    // Ряд Тейлора для cos(x)
    double my_cos(double x) {
        const double PI = 3.14159265358979323846;
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
        if (fabs(cos_val) < 1e-10) {
            throw std::runtime_error("Тангенс не определен для этого угла");
        }
        return my_sin(x) / cos_val;
    }

    // Абсолютное значение
    double my_abs(double x) {
        return (x < 0) ? -x : x;
    }

    // Возведение в степень (только для целых показателей)
    double my_pow(double base, double exp) {
        // Проверяем, целый ли показатель
        double intpart;
        if (modf(exp, &intpart) != 0.0) {
            throw std::runtime_error("Возведение в степень поддерживается только для целых показателей");
        }

        int n = static_cast<int>(exp);
        double result = 1.0;
        bool negative = (n < 0);

        if (negative) n = -n;

        for (int i = 0; i < n; i++) {
            result *= base;
        }

        return negative ? 1.0 / result : result;
    }
}