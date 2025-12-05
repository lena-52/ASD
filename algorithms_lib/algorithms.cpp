#include "algorithms.h"
#include "stack.h"
#include "DSU.h"
#include <stdexcept>
bool check_brackets(const std::string& str) {
    Stack<char> stack(str.length());
    for (size_t i = 0; i < str.length(); ++i) {
        char c = str[i];
        // Åñëè îòêðûâàþùàÿ ñêîáêà, êëàäåì â ñòåê
        if (c == '(' || c == '[' || c == '{') {
            stack.push(c);
        }
        else if (c == ')' || c == ']' || c == '}') {
            // Åñëè ñòåê ïóñò
            if (stack.is_empty()) {
                return false;
            }
            // Èçâëåêàåì âåðõíèé ýëåìåíò ñòåêà
            char top_elem = stack.top();
            stack.pop();

            if ((c == ')' && top_elem != '(') ||(c == ']' && top_elem != '[') || (c == '}' && top_elem != '{')) {
                return false;
            }
        }
    }
    // Â êîíöå àëãîðèòìà, åñëè ñòåê íå ïóñò, òî åñòü íåçàêðûòûå ñêîáêè
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
    // Ìàññèâ íàïðàâëåíèé äëÿ ïðîâåðêè ñîñåäåé
    const int directions[4][2] = { {-1, 0}, /*up*/ {1, 0}, /*down*/ {0, -1}, /*left*/ {0, 1}  /*right*/};

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == 1) { // ÿâëÿåòñÿ ëè òåêóùàÿ ÿ÷åéêà ñóøåé 
                int currentIndex = i * cols + j; // Ïðåîáðàçóåì äâóìåðíûå êîîðäèíàòû [i][j] â îäíîìåðíûé èíäåêñ

                for (int d = 0; d < 4; ++d) {
                    // Âû÷èñëÿåì êîîðäèíàòû ñîñåäíåé ÿ÷åéêè:
                    int ni = i + directions[d][0];
                    int nj = j + directions[d][1];

                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && grid[ni][nj] == 1) {
                        int neighborIndex = ni * cols + nj;
                        // Ïðîâåðÿåì, íàõîäÿòñÿ ëè òåêóùàÿ ÿ÷åéêà è ñîñåä â ðàçíûõ ìíîæåñòâàõ 
                        if (dsu.find(currentIndex) != dsu.find(neighborIndex)) {
                            dsu.unite(currentIndex, neighborIndex);
                        }// Åñëè ÿ÷åéêè â ðàçíûõ ìíîæåñòâàõ, îáúåäèíÿåì èõ
                    }
                }
            }
        }
    }
    // ïîäñ÷èòàåì êîëè÷åñòâî óíèêàëüíûõ îñòðîâîâ
    int islandCount = 0;
    bool* isRoot = new bool[rows * cols](); // Ñîçäàåì ìàññèâ ôëàãîâ äëÿ îòñëåæèâàíèÿ óæå ó÷òåííûõ êîðíåé

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == 1) {
                int index = i * cols + j;
                int root = dsu.find(index);

                if (!isRoot[root]) { // Ïðîâåðÿåì, âñòðå÷àëñÿ ëè ýòîò êîðåíü ðàíüøå
                    isRoot[root] = true; // Ïîìå÷àåì êîðåíü êàê ó÷òåííûé
                    ++islandCount;
                }
            }
        }
    }

    delete[] isRoot;
    return islandCount;
}

