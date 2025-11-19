#include "algorithms.h"
#include "stack.h"

bool check_brackets(const std::string& str) {
    //размер стека = длина строки
    Stack<int> stack(str.length());
    for (int i = 0; i < str.length(); ++i) {
        int c = str[i];
        // Если открывающая скобка, кладем в стек
        if (c == '(' || c == '[' || c == '{')
        {
            stack.push(c);
        }
        else if (c == ')' || c == ']' || c == '}')
        {
            // Если стек пуст
            if (stack.is_empty()) {
                return false;
            }
            // Извлекаем верхний элемент стека
            int top_elem = stack.top();
            stack.pop();

            // Проверяем соответствие скобок
            if ((c == ')' && top_elem != '(') || (c == ']' && top_elem != '[') || (c == '}' && top_elem != '{'))
            {
                return false;
            }
        }
    }
    // в конце алгоритма, если стек не пуст, то есть незакрытые скобки
    return stack.is_empty();
}