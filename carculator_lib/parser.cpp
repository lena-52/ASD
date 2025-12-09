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

        if (name.length() > MAX_VARIABLE_LENGTH) {
            return false;
        }

        // Не может начинаться с цифры
        if (isdigit(static_cast<unsigned char>(name[0]))) {
            return false;
        }

        // Проверка символов - только английские буквы, цифры и подчеркивание
        for (char c : name) {
            unsigned char uc = static_cast<unsigned char>(c);
            if (!((uc >= 'A' && uc <= 'Z') || (uc >= 'a' && uc <= 'z') || (uc >= '0' && uc <= '9') || c == '_')) {
                return false;
            }
        }
        return true;
    }

    bool isFunctionName(const std::string& name) {
        return name == "sin" || name == "cos" || name == "tg" || name == "abs";
    }

    void throwParseError(const std::string& expr, size_t pos, const std::string& msg) {
        std::string error = "Ошибка в позиции " + std::to_string(pos + 1) + ":\n";
        error += "Введенное выражение: " + expr + "\n";
        error += std::string(pos + 21, ' ') + "^\n";
        error += msg;
        throw std::runtime_error(error);
    }

    int getOperatorPriority(const std::string& op, bool isUnary) {
        if (isUnary) return 4;

        if (op == "^") return 3;
        if (op == "*" || op == "/") return 2;
        if (op == "+" || op == "-") return 1;

        return 0;
    }

    int parseNumber(const std::string& str, size_t& pos) {
        size_t start = pos;

        // Считываем все цифры подряд
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

        std::string numStr = str.substr(start, pos - start); //подстрока с числом

        if (numStr.empty()) { //если не считалось ни одной цифры
            throwParseError(str, start, "Ожидалось число");
        }
        // Преобразуем строку в целое число
        return std::stoi(numStr);
    }

    std::string parseIdentifier(const std::string& str, size_t& pos) {
        size_t start = pos;

        // Проверяем, что первый символ - английская буква или подчеркивание
        if (pos < str.length() && ((str[pos] >= 'A' && str[pos] <= 'Z') || (str[pos] >= 'a' && str[pos] <= 'z') || str[pos] == '_')) {
            pos++;
            // считываем, пока английские буквы, цифры или подчеркивания
            while (pos < str.length() && ((str[pos] >= 'A' && str[pos] <= 'Z') || (str[pos] >= 'a' && str[pos] <= 'z') || (str[pos] >= '0' && str[pos] <= '9') || str[pos] == '_')) {
                pos++;
            }
        }

        return str.substr(start, pos - start);
    }

    void processUnaryMinus(List<Lexem>& lexems) {
        List<Lexem> result;
        bool prevIsOperator = true;
        bool prevIsOpenBracket = true;

        // Проходим по всем лексемам
        for (auto it = lexems.begin(); it != lexems.end(); ++it) {
            Lexem lex = *it;

            if (lex.name == "-" && (prevIsOperator || prevIsOpenBracket ||
                lexems.is_empty() || it == lexems.begin())) {
                // Это унарный минус
                result.push_back(Lexem("0", Constant, 0.0));
                result.push_back(Lexem("-", Operator, 0.0, getOperatorPriority("-", false))); // Бинарный минус
            }
            else {
                // остальные лексемы добавляем как есть
                result.push_back(lex);
            }

            // Обновляем флаги для следующей итерации
            prevIsOperator = (lex.type == Operator || lex.type == UnOperator || lex.isFunction());
            prevIsOpenBracket = (lex.type == OpenBracket || lex.type == OpenedAbs);
        }

        lexems = result;// Заменяем исходный список обработанным
    }

    void processAbsoluteValue(List<Lexem>& lexems) {
        List<Lexem> result;
        int count = 0;  // для отслеживания вложенности модулей

        for (auto it = lexems.begin(); it != lexems.end(); ++it) {
            Lexem lex = *it;

            if (lex.type == OpenedAbs) {
                result.push_back(Lexem("abs", Function, 0.0, 0, Functions::my_abs));
                result.push_back(Lexem("(", OpenBracket));
                count++;  // Отмечаем начало модуля
            }
            else if (lex.type == ClosedAbs) {
                if (count <= 0) {
                    throw std::runtime_error("Непарная закрывающая скобка модуля |");
                }
                count--; // Закрываем модуль
                result.push_back(Lexem(")", CloseBracket));
            }
            else {
                result.push_back(lex);
            }
        }
        //в конце, если счетчик выше нуля, не хватает закрывающей скобки
        if (count > 0) {
            throw std::runtime_error("Непарная открывающая скобка модуля |");
        }

        lexems = result;
    }

    //проверка, что после определенных элементов может идти определенный элемент
    bool isValidNextAfter(const Lexem& prev, const Lexem& current) {

        if (prev.isNumber() || prev.isVariable() || prev.type == CloseBracket || prev.type == ClosedAbs) {
            if (current.type == OpenBracket || current.type == OpenedAbs || current.isFunction() || current.isNumber() || current.isVariable()) {
                return false;
            }
        }

        if (prev.type == OpenBracket || prev.type == OpenedAbs) {
            if (current.type == CloseBracket || current.type == ClosedAbs || (current.isOperator() && current.name != "-")) {
                return false;
            }
        }

        if (prev.isOperator() && prev.name != "-") {
            if (current.type == CloseBracket || current.type == ClosedAbs || (current.isOperator() && current.name != "-")) {
                return false;
            }
        }

        return true;
    }

    List<Lexem> parse(const std::string& expression) {
        List<Lexem> lexems;
        size_t pos = 0;
        size_t length = expression.length();

        Lexem prevLexem("", Constant, 0.0); // Предыдущая лексема для проверки последовательностей
        bool havePrev = false; // Есть ли предыдущая лексема

        while (pos < length) {
            char current = expression[pos];

            if (static_cast<unsigned char>(current) > 127) {
                throwParseError(expression, pos,std::string("Недопустимый символ. Разрешены только английские буквы, цифры, операторы и скобки."));
            }

            unsigned char uc = static_cast<unsigned char>(current);

            // Пропускаем пробелы
            if (isspace(uc)) {
                pos++;
                continue;
            }

            // числа
            if (isdigit(uc)) {
                int intValue = parseNumber(expression, pos);
                Lexem newLexem("", Constant, static_cast<double>(intValue));// Создаем лексему константы

                // Проверка последовательности  с предыдущим элементом
                if (havePrev && !isValidNextAfter(prevLexem, newLexem)) {
                    throwParseError(expression, pos, "Неверное выражение");
                }

                lexems.push_back(newLexem); // Добавляем лексему в список
                prevLexem = newLexem; // Запоминаем как предыдущую
                havePrev = true;
                continue;
            }

            // переменные или функции (только английские буквы)
            if (isalpha(uc) || current == '_') {
                std::string ident = parseIdentifier(expression, pos);

                // Проверяем, является ли идентификатор функцией
                if (isFunctionName(ident)) {
                    // Проверяем, что после функции идет открывающая скобка
                    if (pos >= length || expression[pos] != '(') {
                        throwParseError(expression, pos - ident.length(),
                            "После функции '" + ident + "' должна идти открывающая скобка");
                    }

                    double (*func)(double);
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

                    Lexem newLexem(ident, Function, 0.0, 0, func); // Создаем лексему функции

                    // Проверка последовательности с предыдущим
                    if (havePrev && !isValidNextAfter(prevLexem, newLexem)) {
                        throwParseError(expression, pos - ident.length(), "Неверное выражение");
                    }

                    lexems.push_back(newLexem);
                    prevLexem = newLexem;
                    havePrev = true;
                }
                else {
                    //если не функция, то это переменная. проверяем ее имя
                    if (!isValidVariableName(ident)) {
                        if (ident.empty()) {
                            throwParseError(expression, pos, "Неверный идентификатор переменной");
                        }
                        if (isdigit(static_cast<unsigned char>(ident[0]))) {
                            throwParseError(expression, pos - ident.length(), "Имя переменной не может начинаться с цифры: '" + ident + "'");
                        }
                        if (ident.length() > MAX_VARIABLE_LENGTH) {
                            throwParseError(expression, pos - ident.length(), "Слишком длинное имя переменной. Максимум " + std::to_string(MAX_VARIABLE_LENGTH) + " символов");
                        }

                        for (char c : ident) {
                            unsigned char uc_char = static_cast<unsigned char>(c);
                            if (uc_char > 127) {
                                throwParseError(expression, pos - ident.length(), "Имя переменной содержит недопустимые символы. Разрешены только английские буквы, цифры и подчеркивание.");
                            }
                        }

                        throwParseError(expression, pos - ident.length(), "Недопустимое имя переменной: '" + ident + "'. Разрешены только английские буквы, цифры и символ _");
                    }
                    Lexem newLexem(ident, Variable); // Создаем лексему переменной

                    // Проверка последовательности с предыдущим
                    if (havePrev && !isValidNextAfter(prevLexem, newLexem)) {
                        throwParseError(expression, pos - ident.length(), "Неверное выражение");
                    }

                    lexems.push_back(newLexem);
                    prevLexem = newLexem;
                    havePrev = true;
                }
                continue;
            }

            // Операторы
            if (current == '+' || current == '-' || current == '*' || current == '/' || current == '^') {
                std::string op;
                op.push_back(current); // Преобразуем char в string
                Lexem newLexem(op, Operator, 0.0, getOperatorPriority(op, false)); // Создаем лексему оператора

                // Проверка последовательности с предыдущим
                if (havePrev && !isValidNextAfter(prevLexem, newLexem)) {
                    throwParseError(expression, pos,  "Неверное выраэение");
                }

                lexems.push_back(newLexem);
                pos++;
                prevLexem = newLexem;
                havePrev = true;
                continue;
            }

            // Скобки
            if (current == '(' || current == '[' || current == '{') {
                Lexem newLexem("(", OpenBracket);

                // Проверка последовательности
                if (havePrev && !isValidNextAfter(prevLexem, newLexem)) {
                    throwParseError(expression, pos, "Неверное выражение ");
                }

                lexems.push_back(newLexem);
                pos++;
                prevLexem = newLexem;
                havePrev = true;
                continue;
            }

            if (current == ')' || current == ']' || current == '}') {
                Lexem newLexem(")", CloseBracket);

                // Проверка последовательности
                if (havePrev && !isValidNextAfter(prevLexem, newLexem)) {
                    throwParseError(expression, pos, "Неверное выражение");
                }

                lexems.push_back(newLexem);
                pos++;
                prevLexem = newLexem;
                havePrev = true;
                continue;
            }

            // модуль
            if (current == '|') {
                bool isOpening = true;

                if (!lexems.is_empty()) {  // Если перед | стоит число, переменная или закрывающая скобка, то это закрывающая скобка модуля
                    Lexem last = lexems.back();
                    if (last.isNumber() || last.isVariable() || last.type == CloseBracket || last.type == ClosedAbs) {
                        isOpening = false;
                    }
                }

                Lexem newLexem;
                if (isOpening) {
                    newLexem = Lexem("|", OpenedAbs);

                    // Проверка последовательности
                    if (havePrev && !isValidNextAfter(prevLexem, newLexem)) {
                        throwParseError(expression, pos,  "НЕверное выражение");
                    }
                }
                else {
                    newLexem = Lexem("|", ClosedAbs);

                    // Проверка последовательности
                    if (havePrev && !isValidNextAfter(prevLexem, newLexem)) {
                        throwParseError(expression, pos, "Неверное выражение ");
                    }
                }

                lexems.push_back(newLexem);
                pos++;
                prevLexem = newLexem;
                havePrev = true;
                continue;
            }

            throwParseError(expression, pos, std::string("Неизвестный символ: '") + current + "'. Разрешены только: + - * / ^ ( ) [ ] { } | и английские буквы/цифры");
        }

        //преобразование -x -> 0 - x
        processUnaryMinus(lexems);

        // преобразование |x| -> abs(x)
        processAbsoluteValue(lexems);

        return lexems;
    }

}