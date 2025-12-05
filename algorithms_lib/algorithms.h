#pragma once
#include <string>
#include "list.h"

// ‘ункци€ проверки скобок
bool check_brackets(const std::string& str);
    
// 1. за€ц-черепаха
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

        // ≈сли за€ц догнал черепаху - есть цикл
        if (turtle == rabbit) {
            return true;
        }
    }

    return false;  // «а€ц достиг конца списка - цикла нет
}
//разворот указателей
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
    //разворот списка
    while (current != nullptr) {
        next_node = current->next;
        current->next = prev;
        prev = current;
        current = next_node;

        // ≈сли после разворота мы вернулись к исходной голове - цикл!
        if (current == original_head) {
            has_cycle = true;
            break;
        }
    }

    // восстанавливаем список 

    if (has_cycle) {
        // prev сейчас указывает на узел, с которого началс€ цикл 
        // Ќаходим начало цикла и разрываем его
        Node<T>* cycle_start = prev; 
        Node<T>* temp = cycle_start;

        // »щем узел, который ссылаетс€ на cycle_start, чтобы разорвать цикл
        while (temp != nullptr && temp->next != cycle_start) {
            temp = temp->next;
        }

        if (temp != nullptr) {
            temp->next = nullptr;
        }

        // “еперь восстанавливаем исходный список
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
        // ≈сли цикла не было, просто восстанавливаем список
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
// 3. јлгоритм с возвратом указател€ на место поломки списка
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

    // ѕоиск начала цикла
    turtle = head;
    while (turtle != rabbit) {
        turtle = turtle->next;
        rabbit = rabbit->next;
    }

    // turtle теперь указывает на начало цикла
    return turtle;
}