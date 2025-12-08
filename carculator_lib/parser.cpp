#include "parser.h"
#include "functions.h"
#include "stack.h"
#include <sstream>
#include <iomanip>

namespace Parser {
    bool isValidVariableName(const std::string& name) {
        if (name.empty()) {
            return false;
        }

        // Проверка длины
        if (name.length() > MAX_VARIABLE_LENGTH) {
            return false;
        }

        // Не может начинаться с цифры
        if (isdigit(static_cast<unsigned char>(name[0]))) {
            return false;
        }

        // Проверка символов
        for (char c : name) {
            unsigned char uc = static_cast<unsigned char>(c);
            if (!(isalnum(uc) || c == '_')) {
                return false;
            }
        }
        return true;
    }

    bool isFunctionName(const std::string& name) {
        return name == "sin" || name == "cos" || name == "tg" || name == "abs";
    }

    int getOperatorPriority(const std::string& op, bool isUnary) {
        if (isUnary) return 4;

        if (op == "^") return 3;
        if (op == "*" || op == "/") return 2;
        if (op == "+" || op == "-") return 1;

        return 0;
    }

    double parseNumber(const std::string& str, size_t& pos) {
        size_t start = pos;

        // Парсим только целые числа
        while (pos < str.length() && isdigit(static_cast<unsigned char>(str[pos]))) {
            pos++;
        }

        // Если после цифр идет буква или подчеркивание - это ошибка 
        if (pos < str.length() && (isalpha(static_cast<unsigned char>(str[pos])) || str[pos] == '_')) {
            size_t errorStart = pos;
            // Продолжаем считывать весь некорректный идентификатор
            while (pos < str.length() && (isalnum(static_cast<unsigned char>(str[pos])) || str[pos] == '_')) {
                pos++;
            }
            std::string invalidIdent = str.substr(start, pos - start);
            throwParseError(str, start, "Идентификатор не может начинаться с цифры: '" + invalidIdent + "'");
        }

        // Проверяем, нет ли точки 
        if (pos < str.length() && str[pos] == '.') {
            throwParseError(str, pos, "Вещественные числа не поддерживаются. Используйте только целые числа.");
        }

        std::string numStr = str.substr(start, pos - start);

        if (numStr.empty()) {
            throwParseError(str, start, "Ожидалось число");
        }

        return std::stod(numStr);
    }

    std::string parseIdentifier(const std::string& str, size_t& pos) {
        size_t start = pos;

        // Идентификатор должен начинаться с буквы или подчеркивания
        if (pos < str.length() && (isalpha(static_cast<unsigned char>(str[pos])) || str[pos] == '_')) {
            pos++;
            // Продолжаем пока буквы, цифры или подчеркивания
            while (pos < str.length() && (isalnum(static_cast<unsigned char>(str[pos])) || str[pos] == '_')) {
                pos++;
            }
        }

        return str.substr(start, pos - start);
    }

    void throwParseError(const std::string& expr, size_t pos, const std::string& msg) {
        std::string error = "Ошибка в позиции " + std::to_string(pos + 1) + ":\n";
        error += "Введенное выражение: " + expr + "\n";
        error += std::string(pos + 19, ' ') + "^\n";
        error += msg;
        throw std::runtime_error(error);
    }

    std::string getErrorContext(const std::string& expr, size_t pos) {
        size_t start = (pos > 20) ? pos - 20 : 0;
        size_t end = (pos + 20 < expr.length()) ? pos + 20 : expr.length();
        return "..." + expr.substr(start, end - start) + "...";
    }

    void processUnaryMinus(List<Lexem>& lexems) {
        List<Lexem> result;
        bool prevIsOperator = true;
        bool prevIsOpenBracket = true;

        for (auto it = lexems.begin(); it != lexems.end(); ++it) {
            Lexem lex = *it;

            if (lex.name == "-" && (prevIsOperator || prevIsOpenBracket ||
                lexems.is_empty() || it == lexems.begin())) {
                // Это унарный минус
                result.push_back(Lexem("0", Constant, 0.0));
                result.push_back(Lexem("-", Operator, 0.0, getOperatorPriority("-", false)));
            }
            else {
                result.push_back(lex);
            }

            // Обновляем флаги для следующей итерации
            prevIsOperator = (lex.type == Operator || lex.type == UnOperator ||
                lex.isFunction());
            prevIsOpenBracket = (lex.type == OpenBracket || lex.type == OpenedAbs);
        }

        lexems = result;
    }

    void processAbsoluteValue(List<Lexem>& lexems) {
        List<Lexem> result;
        Stack<int> absStack;

        for (auto it = lexems.begin(); it != lexems.end(); ++it) {
            Lexem lex = *it;

            if (lex.type == OpenedAbs) {
                result.push_back(Lexem("abs", Function, 0.0, 0, Functions::my_abs));
                result.push_back(Lexem("(", OpenBracket));
                absStack.push(1);
            }
            else if (lex.type == ClosedAbs) {
                if (absStack.is_empty()) {
                    throw std::runtime_error("Непарная закрывающая скобка модуля |");
                }
                absStack.pop();
                result.push_back(Lexem(")", CloseBracket));
            }
            else {
                result.push_back(lex);
            }
        }

        if (!absStack.is_empty()) {
            throw std::runtime_error("Непарная открывающая скобка модуля |");
        }

        lexems = result;
    }

    List<Lexem> parse(const std::string& expression) {
        List<Lexem> lexems;
        size_t pos = 0;
        size_t length = expression.length();

        while (pos < length) {
            char current = expression[pos];
            unsigned char uc = static_cast<unsigned char>(current);

            // Пропускаем пробелы
            if (isspace(uc)) {
                pos++;
                continue;
            }

            // Числа (начинаются с цифры)
            if (isdigit(uc)) {
                double value = parseNumber(expression, pos);
                lexems.push_back(Lexem("", Constant, value));
                continue;
            }

            // переменные или функции (начинаются с буквы или подчеркивания)
            if (isalpha(uc) || current == '_') {
                std::string ident = parseIdentifier(expression, pos);

                // Если идентификатор пустой (хотя такого быть не должно)
                if (ident.empty()) {
                    throwParseError(expression, pos, "Ожидался идентификатор");
                }

                // Проверяем, является ли идентификатор функцией
                if (isFunctionName(ident)) {
                    // Проверяем, что после функции идет открывающая скобка
                    if (pos >= length || expression[pos] != '(') {
                        throwParseError(expression, pos - ident.length(),
                            "После функции '" + ident + "' должна идти открывающая скобка '('");
                    }

                    double (*func)(double) = nullptr;
                    if (ident == "sin") {
                        func = Functions::my_sin;
                    }
                    else if (ident == "cos") {
                        func = Functions::my_cos;
                    }
                    else if (ident == "tg") {
                        func = Functions::my_tg;
                    }
                    else if (ident == "abs") {
                        func = Functions::my_abs;
                    }

                    lexems.push_back(Lexem(ident, Function, 0.0, 0, func));
                }
                else {
                    // Это переменная - проверяем ее имя
                    if (!isValidVariableName(ident)) {
                        if (ident.empty()) {
                            throwParseError(expression, pos,
                                "Неверный идентификатор переменной");
                        }
                        if (isdigit(static_cast<unsigned char>(ident[0]))) {
                            throwParseError(expression, pos - ident.length(),
                                "Имя переменной не может начинаться с цифры: '" + ident + "'");
                        }
                        if (ident.length() > MAX_VARIABLE_LENGTH) {
                            throwParseError(expression, pos - ident.length(),
                                "Слишком длинное имя переменной. Максимум " +
                                std::to_string(MAX_VARIABLE_LENGTH) + " символов: '" + ident + "'");
                        }
                        throwParseError(expression, pos - ident.length(),
                            "Недопустимое имя переменной: '" + ident +
                            "'. Разрешены только буквы, цифры и символ _");
                    }
                    lexems.push_back(Lexem(ident, Variable));
                }
                continue;
            }

            // Операторы
            if (current == '+' || current == '-' || current == '*' || current == '/' || current == '^') {
                std::string op(1, current);
                lexems.push_back(Lexem(op, Operator, 0.0, getOperatorPriority(op, false)));
                pos++;
                continue;
            }

            // Скобки
            if (current == '(' || current == '[' || current == '{') {
                lexems.push_back(Lexem("(", OpenBracket));
                pos++;
                continue;
            }

            if (current == ')' || current == ']' || current == '}') {
                lexems.push_back(Lexem(")", CloseBracket));
                pos++;
                continue;
            }

            // модуль
            if (current == '|') {
                bool isOpening = true;

                if (!lexems.is_empty()) {
                    Lexem last = lexems.back();
                    if (last.isNumber() || last.isVariable() ||
                        last.type == CloseBracket || last.type == ClosedAbs) {
                        isOpening = false;
                    }
                }

                if (isOpening) {
                    lexems.push_back(Lexem("|", OpenedAbs));
                }
                else {
                    lexems.push_back(Lexem("|", ClosedAbs));
                }
                pos++;
                continue;
            }

            // Неизвестный символ
            throwParseError(expression, pos,
                std::string("Неизвестный символ: '") + current + "'");
        }

        // Обработка унарного минуса
        processUnaryMinus(lexems);

        // Обработка модуля
        processAbsoluteValue(lexems);

        return lexems;
    }
}
