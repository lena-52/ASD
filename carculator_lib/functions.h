#pragma once
#include <cmath>

namespace Functions {
    // Реализация sin через ряд Тейлора
    double my_sin(double x);

    // Реализация cos через ряд Тейлора
    double my_cos(double x);

    // Реализация tan через sin/cos
    double my_tg(double x);

    // Абсолютное значение
    double my_abs(double x);

    // Возведение в степень
    double my_pow(double base, double exp);
}