#pragma once
#include <string>
#include "list.h"
bool check_brackets(const std::string& str);
int countIslands(int** grid, int rows, int cols);

// 1. заяц-черепаха
template <class T>
bool check_cycle_turtle_rabbit(Node<T>* head) {
    if (head == nullptr || head->next == nullptr) {
        return false;
    }

    Node<T>* turtle = head;   
    Node<T>* rabbit = head;   

    while (rabbit != nullptr && rabbit->next != nullptr) {
        turtle = turtle->next;          
        rabbit = rabbit->next->next;   

        // Если заяц догнал черепаху - есть цикл       
        if (turtle == rabbit) {
            return true;
        }
    }

    return false; // Заяц достиг конца списка - цикла нет
}
//2. разворот указателей
template <class T>
bool check_cycle_with_reverse_pointers(Node<T>* head) {
    if (head == nullptr) {
        return false;
    }

    Node<T>* current = head;
    Node<T>* prev = nullptr;
    Node<T>* next_node = nullptr;
    Node<T>* original_head = head;
    bool has_cycle = false;

    // Разворот списка
    while (current != nullptr) {
        next_node = current->next;
        current->next = prev;
        prev = current;
        current = next_node;

        // Если после разворота мы вернулись к исходной голове - цикл
        if (current == original_head) {
            has_cycle = true;
            break;
        }
    }

    // Восстанавливаем исходный список 

    if (has_cycle) {
        // prev сейчас указывает на узел, с которого начался цикл
         // Находим начало цикла и разрываем его
        Node<T>* cycle_start = prev; 
        Node<T>* temp = cycle_start;

        // Ищем узел, который ссылается на cycle_start, чтобы разорвать цикл
        while (temp != nullptr && temp->next != cycle_start) {
            temp = temp->next;
        }

        if (temp != nullptr) {
            temp->next = nullptr;
        }

        // восстанавливаем исходный список
        current = cycle_start;
        prev = nullptr;
        while (current != nullptr) {
            next_node = current->next;
            current->next = prev;
            prev = current;
            current = next_node;
        }
    }
    else {
        // Если цикла не было, просто восстанавливаем список
        current = prev;
        prev = nullptr;
        while (current != nullptr) {
            next_node = current->next;
            current->next = prev;
            prev = current;
            current = next_node;
        }
    }

    return has_cycle;
}
// 3. Алгоритм с возвратом указателя на место начала цикла
template <class T>
Node<T>* check_cycle_find_node(Node<T>* head) {
    if (head == nullptr || head->next == nullptr) {
        return nullptr;
    }

    Node<T>* turtle = head;
    Node<T>* rabbit = head;
    bool has_cycle = false;

    while (rabbit != nullptr && rabbit->next != nullptr) {
        turtle = turtle->next;
        rabbit = rabbit->next->next;

        if (turtle == rabbit) {
            has_cycle = true;
            break;
        }
    }

    if (!has_cycle) {
        return nullptr;
    }

    // Поиск начала цикла
    turtle = head;
    while (turtle != rabbit) {
        turtle = turtle->next;
        rabbit = rabbit->next;
    }

    // turtle теперь указывает на начало цикла
    return turtle;
}
