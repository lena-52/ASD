#include "algorithms.h"
#include "stack.h"
#include "DSU.h"
#include <stdexcept>
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



int countIslands(int** grid, int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::logic_error("index out of range");
    }

    if (grid == nullptr) {
        throw std::logic_error("no data");
    }

    DSU dsu(rows * cols);
    // Массив направлений для проверки соседей
    const int directions[4][2] = { {-1, 0}, /*up*/ {1, 0}, /*down*/ {0, -1}, /*left*/ {0, 1}  /*right*/};

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == 1) { // является ли текущая ячейка сушей 
                int currentIndex = i * cols + j; // Преобразуем двумерные координаты [i][j] в одномерный индекс

                for (int d = 0; d < 4; ++d) {
                    // Вычисляем координаты соседней ячейки:
                    int ni = i + directions[d][0];
                    int nj = j + directions[d][1];

                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && grid[ni][nj] == 1) {
                        int neighborIndex = ni * cols + nj;
                        // Проверяем, находятся ли текущая ячейка и сосед в разных множествах 
                        if (dsu.find(currentIndex) != dsu.find(neighborIndex)) {
                            dsu.unite(currentIndex, neighborIndex);
                        }// Если ячейки в разных множествах, объединяем их
                    }
                }
            }
        }
    }
    // подсчитаем количество уникальных островов
    int islandCount = 0;
    bool* isRoot = new bool[rows * cols](); // Создаем массив флагов для отслеживания уже учтенных корней

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == 1) {
                int index = i * cols + j;
                int root = dsu.find(index);

                if (!isRoot[root]) { // Проверяем, встречался ли этот корень раньше
                    isRoot[root] = true; // Помечаем корень как учтенный
                    ++islandCount;
                }
            }
        }
    }

    delete[] isRoot;
    return islandCount;
}