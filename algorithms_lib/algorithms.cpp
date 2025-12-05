#include "algorithms.h"
#include "stack.h"
bool check_brackets(const std::string& str) {
    Stack<char> stack(str.length());
    for (size_t i = 0; i < str.length(); ++i) {
        char c = str[i];
        // Если открывающая скобка, кладем в стек
        if (c == '(' || c == '[' || c == '{') {
            stack.push(c);
        }
        else if (c == ')' || c == ']' || c == '}') {
            // Если стек пуст
            if (stack.is_empty()) {
                return false;
            }
            // Извлекаем верхний элемент стека
            char top_elem = stack.top();
            stack.pop();

            if ((c == ')' && top_elem != '(') ||(c == ']' && top_elem != '[') || (c == '}' && top_elem != '{')) {
                return false;
            }
        }
    }
    // В конце алгоритма, если стек не пуст, то есть незакрытые скобки
    return stack.is_empty();
}




