#include "carculator.h"
#include "parser.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>

void Calculator::run() {
    int choice;
    bool running = true;

    while (running) {
        std::cout << "\n========= МЕНЮ =========\n";
        std::cout << "1. Создать новое выражение\n";
        std::cout << "2. Удалить выражение\n";
        std::cout << "3. Задать переменные\n";
        std::cout << "4. Вычислить значение выражения\n";
        std::cout << "5. Показать все выражения\n";
        std::cout << "0. Выйти\n";
        std::cout << "\nВаш выбор: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод. Введите число:\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        try {
            switch (choice) {
            case 1:
                createExpression();
                break;
            case 2:
                deleteExpression();
                break;
            case 3:
                setVariables();
                break;
            case 4:
                evaluateExpression();
                break;
            case 5:
                displayAllExpressions();
                break;
            case 0:
                running = false;
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "\nОШИБКА: " << e.what() << "\n";
            std::cin.clear();
        }
    }
}

void Calculator::createExpression() {
    std::string expr; 
    std::cout << "\nВведите выражение: ";
    std::getline(std::cin, expr);

    if (expr.empty()) {
        std::cout << "Выражение не может быть пустым\n";
        return;
    }

    try {
        Expression newExpr(expr); // Создание объекта Expression с переданной строкой
        expressions.push_back(newExpr);
        std::cout << "Выражение добавлено\n";
        std::cout << "ID выражения: " << expressions.size() << "\n";

        // Показываем найденные переменные
        auto varNames = newExpr.getVariableNames();
        if (!varNames.empty()) {
            std::cout << "Найдены переменные: ";
            for (size_t i = 0; i < varNames.size(); i++) {
                std::cout << varNames[i];
                if (i < varNames.size() - 1) std::cout << ", ";
            }
            std::cout << "\n";
        }
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка при создании выражения: " << e.what() << "\n";
    }
}

void Calculator::deleteExpression() {
    if (expressions.size() == 0) {
        std::cout << "Нет выражений для удаления\n";
        return;
    }

    displayAllExpressions();

    int id;
    std::cout << "\nВведите ID выражения для удаления (0 для отмены): ";
    if (!(std::cin >> id)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Неверный ввод\n";
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (id == 0) return;

    if (id < 1 || id > expressions.size()) {
        std::cout << "Неверный ID\n";
        return;
    }

    expressions.erase(id - 1, 1);
    std::cout << "Выражение удалено\n";
}

void Calculator::setVariables() {
    if (expressions.size() == 0) {
        std::cout << "Нет доступных выражений\n";
        return;
    }

    displayAllExpressions();

    int id;
    std::cout << "\nВведите ID выражения (0 для отмены): ";
    if (!(std::cin >> id)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Неверный ввод\n";
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (id == 0) return;

    if (id < 1 || id > expressions.size()) {
        std::cout << "Неверный ID\n";
        return;
    }

    Expression& expr = expressions[id - 1];  
    auto varNames = expr.getVariableNames();  // Получение списка переменных

    if (varNames.empty()) {
        std::cout << "В выражении нет переменных\n";
        return;
    }

    std::cout << "\nЗадание переменных для выражения " << id << "\n";
    std::cout << "Выражение: " << expr.getExpression() << "\n\n";

    std::map<std::string, double> vars;  // Словарь для хранения значений переменных
    for (const auto& varName : varNames) {
        double value;
        std::cout << "Введите значение для " << varName << ": ";

        while (!(std::cin >> value)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод. Введите число: ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        vars[varName] = value;  // Сохранение значения в словарь
    }

    expr.setVariables(vars);   // Установка значений переменных в выражение
    std::cout << "\nПеременные заданы\n";
}

void Calculator::evaluateExpression() {
    if (expressions.size() == 0) {
        std::cout << "Нет доступных выражений\n";
        return;
    }

    displayAllExpressions();

    int id;
    std::cout << "\nВведите ID выражения для вычисления (0 для отмены): ";
    if (!(std::cin >> id)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Неверный ввод\n";
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (id == 0) return;

    if (id < 1 || id > expressions.size()) {
        std::cout << "Неверный ID\n";
        return;
    }

    Expression& expr = expressions[id - 1];

    if (!expr.isReady()) {
        std::cout << "Некоторые переменные не заданы. Задать их сейчас? (y/n): ";
        char choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 'y' || choice == 'Y') {
            auto varNames = expr.getVariableNames();
            std::map<std::string, double> vars;

            for (const auto& varName : varNames) {
                double value;
                std::cout << "Введите значение для " << varName << ": ";
                std::cin >> value;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                vars[varName] = value;
            }

            expr.setVariables(vars);
        }
        else {
            return;
        }
    }

    try {
        double result = expr.evaluate();
        std::cout << "\nРЕЗУЛЬТАТ\n";
        std::cout << "Выражение: " << expr.getExpression() << "\n";
        std::cout << "Значения переменных: " << expr.getVariablesString() << "\n";
        // Вывод с точностью 10 знаков
        std::cout << "Результат: " << std::setprecision(10) << result << "\n";
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка вычисления: " << e.what() << "\n";
    }
}

void Calculator::displayAllExpressions() const {
    if (expressions.size() == 0) {
        std::cout << "Нет доступных выражений\n";
        return;
    }

    // Ширина колонок
    const int ID_WIDTH = 5;
    const int EXPR_WIDTH = 40;
    const int VARS_WIDTH = 35;
    const int TOTAL_WIDTH = ID_WIDTH + EXPR_WIDTH + VARS_WIDTH + 6;

    std::cout << std::string(TOTAL_WIDTH, '-') << "\n";

    // Заголовок таблицы
    std::cout << "| " << std::left << std::setw(ID_WIDTH) << "ID" << "| " << std::setw(EXPR_WIDTH) << "ВЫРАЖЕНИЕ" << "| " << std::setw(VARS_WIDTH) << "ЗНАЧЕНИЯ ПЕРЕМЕННЫХ" << "|\n";
    std::cout << std::string(TOTAL_WIDTH, '-') << "\n";

    // Вывод каждой строки таблицы
    for (int i = 0; i < expressions.size(); i++) {
        const Expression& expr = expressions[i];
        // Получение строки с переменными
        std::string varsStr = expr.getVariablesString();

        // Форматируем выражение
        std::string exprStr = expr.getExpression();
        if (exprStr.length() > EXPR_WIDTH - 2) {
            exprStr = exprStr.substr(0, EXPR_WIDTH - 5) + "...";
        }

        // Форматируем строку с переменными
        if (varsStr.length() > VARS_WIDTH - 2) {
            varsStr = varsStr.substr(0, VARS_WIDTH - 5) + "...";
        }

        // Выводим строку
        std::cout << "| " << std::setw(ID_WIDTH) << (i + 1) << "| " << std::setw(EXPR_WIDTH) << exprStr << "| " << std::setw(VARS_WIDTH) << varsStr << "|\n";
    }

    std::cout << std::string(TOTAL_WIDTH, '-') << "\n";
}

