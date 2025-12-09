#include "expression.h"
#include "parser.h"
#include "functions.h"
#include <stdexcept>
#include <sstream>
#include <cmath>
#include <iomanip>
Expression::Expression() : isParsed(false), isPostfixReady(false) {
}

Expression::Expression(const std::string& expr) : originalExpression(expr), isParsed(false), isPostfixReady(false) {
    setExpression(expr);
}

void Expression::setExpression(const std::string& expr) {
    if (expr.empty()) {
        throw std::runtime_error("Выражение не может быть пустым");
    }
    originalExpression = expr;
    variables.clear(); // Очищаем предыдущие значения переменных

    try {
        infixNotation = Parser::parse(expr);
        isParsed = true;

        // Извлекаем имена переменных из списка лексем
        for (auto it = infixNotation.begin(); it != infixNotation.end(); ++it) {
            if ((*it).type == Variable) {
                variables[(*it).name] = std::numeric_limits<double>::quiet_NaN();
            }
        }

        //строим обр польскую запись
        postfixNotation = toPostfix(infixNotation);
        isPostfixReady = true;

    }
    catch (const std::exception&) {
        isParsed = false;
        isPostfixReady = false;
        throw;
    }
}

List<Lexem> Expression::toPostfix(const List<Lexem>& infix) {
    List<Lexem> result;
    Stack<Lexem> operators;

    // Проход по всем лексемам в инфиксной нотации
    for (auto it = infix.begin(); it != infix.end(); ++it) {
        Lexem lex = *it;

        if (lex.isNumber() || lex.isVariable()) {
            result.push_back(lex);
        }
        else if (lex.isFunction()) {
            operators.push(lex);
        }
        else if (lex.type == OpenBracket) {
            operators.push(lex);
        }
        // ')' -> достаем из стека все до ')'
        else if (lex.type == CloseBracket) {
            while (!operators.is_empty() && operators.top().type != OpenBracket) {
                result.push_back(operators.top());
                operators.pop();
            }

            // если стек пуст, не хватает скобки
            if (operators.is_empty()) {
                throw std::runtime_error("Непарные скобки");
            }

            operators.pop(); // Удаляем открывающую скобку из стека

            // Если после скобки в стеке функция - переносим ее в результат
            if (!operators.is_empty() && operators.top().isFunction()) {
                result.push_back(operators.top());
                operators.pop();
            }
        }
        else if (lex.isOperator()) {
            // Переносим операторы с более высоким или равным приоритетом
            while (!operators.is_empty() && operators.top().isOperator() && operators.top().priority >= lex.priority) {
                result.push_back(operators.top());
                operators.pop();
            }
            operators.push(lex); // Помещаем текущий оператор в стек
        }
    }

    // Переносим оставшиеся операторы из стека в результат
    while (!operators.is_empty()) {
        if (operators.top().isBracket()) {
            throw std::runtime_error("Непарные скобки");
        }
        result.push_back(operators.top());
        operators.pop();
    }

    return result;
}

double Expression::evaluatePostfix(const List<Lexem>& postfix, const std::map<std::string, double> &vars) {
    Stack<double> values;   // для хранения промежуточных результатов

    for (auto it = postfix.begin(); it != postfix.end(); ++it) {
        Lexem lex = *it;

        if (lex.isNumber()) {
            values.push(lex.value); // Помещаем значение в стек
        }

        else if (lex.isVariable()) {
            // Ищем значение переменной в переданном словаре
            auto varIt = vars.find(lex.name);
            if (varIt == vars.end()) {
                throw std::runtime_error("Переменная '" + lex.name + "' не определена");
            }
            values.push(varIt->second); // Помещаем значение переменной в стек
        }

        else if (lex.isFunction()) {
            if (values.is_empty()) {
                throw std::runtime_error("Недостаточно операндов для функции");
            }

            // Берем аргумент из стека, удаляем его из стека, помещаем результат функции в стек
            double arg = values.top();
            values.pop();
            values.push(lex.function(arg));
        }

        else if (lex.isOperator()) {
            if (values.size() < 2) {
                throw std::runtime_error("Недостаточно операндов для оператора");
            }

            double b = values.top(); // Второй операнд
            values.pop();
            double a = values.top(); // Первый 
            values.pop();

            double result = 0.0;
            if (lex.name == "+") {
                result = a + b;
            }
            else if (lex.name == "-") {
                result = a - b;
            }
            else if (lex.name == "*") {
                result = a * b;
            }
            else if (lex.name == "/") {
                if (b==0) {
                    throw std::runtime_error("Деление на ноль");
                }
                result = a / b;
            }
            else if (lex.name == "^") {
                result = Functions::my_pow(a, b);
            }

            values.push(result);
        }
    }

    // В стеке должен остаться 1 элемент
    if (values.size() != 1) {
        throw std::runtime_error("Неверное выражение");
    }

    return values.top(); // Возвращаем результат вычисления
}

void Expression::setVariable(const std::string& name, double value) {
    // Проверка, что переменная существует в выражении
    if (variables.find(name) == variables.end()) {
        throw std::runtime_error("Переменная '" + name + "' не используется в выражении");
    }
    variables[name] = value;
}

void Expression::setVariables(const std::map<std::string, double>& vars) {
    // Проходим по всем парам ключ-значение в переданном словаре
    for (const auto& pair : vars) {
        // Если переменная существует в выражении - обновляем ее значение
        if (variables.find(pair.first) != variables.end()) {
            variables[pair.first] = pair.second;
        }
    }
}

double Expression::evaluate() {
    if (!isParsed) {
        throw std::runtime_error("Выражение не распарсено");
    }

    //  Проверка, что все переменные определены  (не имеют значения NaN)
    for (const auto& pair : variables) {
        if (std::isnan(pair.second)) {
            throw std::runtime_error("Переменная '" + pair.first + "' не определена");
        }
    }

    return evaluatePostfix(postfixNotation, variables);
}

// Вычисление выражения с временными значениями переменных
double Expression::evaluateWith(const std::map<std::string, double>& vars) {
    if (!isParsed) {
        throw std::runtime_error("Выражение не распарсено");
    }

    // Создаем копию текущих значений переменных
    std::map<std::string, double> allVars = variables;  

    // Обновляем значения переменными из переданного словаря
    for (const auto& pair : vars) {
        if (allVars.find(pair.first) != allVars.end()) {
            allVars[pair.first] = pair.second;
        }
    }

    return evaluatePostfix(postfixNotation, allVars);  // Вычисление значения выражения с обновленными переменными
}

std::string Expression::getExpression() const {
    return originalExpression;
}

std::vector<std::string> Expression::getVariableNames() const {
    std::vector<std::string> names;  // Список имен переменных
    for (const auto& pair : variables) {
        names.push_back(pair.first);
    }
    return names;
}

// Проверка наличия переменной в выражении
bool Expression::hasVariable(const std::string& name) const {
    return variables.find(name) != variables.end();
}

double Expression::getVariableValue(const std::string& name) const {
    auto it = variables.find(name);  // Поиск переменной в словаре
    if (it == variables.end()) {
        throw std::runtime_error("Переменная '" + name + "' не найдена в выражении");
    }
    return it->second;
}

std::string Expression::getVariablesString() const {
    if (variables.empty()) {
        return "нет переменных";
    }

    std::ostringstream oss;
    // Флаг первого элемента для правильной расстановки запятых
    bool first = true; 

    for (const auto& pair : variables) {
        if (!first) {
            // Добавляем запятую перед всеми, кроме первой переменной
            oss << ", "; 
        }

        oss << pair.first << " = ";

        if (std::isnan(pair.second)) {
            oss << "?";
        }
        else {
            // Проверяем, является ли значение целым числом
            if (std::fabs(pair.second - std::floor(pair.second)) < 1e-10) {
                oss << static_cast<int>(pair.second);
            }
            else { 
                // Если дробное - выводим с двумя знаками после запятой
                oss << std::fixed << std::setprecision(2) << pair.second;
            }
        }

        first = false;
    }

    return oss.str(); // Возвращаем отформатированную строку
}

bool Expression::isValid() const {
    return isParsed;
}

bool Expression::isReady() const {
    if (!isParsed) {
        return false;
    }

    // Проверяем, что у всех переменных есть значения 
    for (const auto& pair : variables) {
        if (std::isnan(pair.second)) {
            return false;
        }
    }
    return true;
}
