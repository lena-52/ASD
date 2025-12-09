#pragma once
#include "lexem.h"
#include "list.h"
#include <string>
#include <cctype>
#include <stdexcept>

namespace Parser {
    // Вспомогательные функции
    bool isValidVariableName(const std::string& name);
    bool isFunctionName(const std::string& name);
    int getOperatorPriority(const std::string& op, bool isUnary);
    int parseNumber(const std::string& str, size_t& pos);  // Только целые числа
    std::string parseIdentifier(const std::string& str, size_t& pos);

    // Преобразует строковое выражение в список лексем 
    List<Lexem> parse(const std::string& expression);

    // Функции для обработки унарного минуса и модуля
    void processUnaryMinus(List<Lexem>& lexems);
    void processAbsoluteValue(List<Lexem>& lexems);

    //  функции для обработки ошибок
    void throwParseError(const std::string& expr, size_t pos, const std::string& msg);
}
