#pragma once
#include <string>
#include "list.h"
bool check_brackets(const std::string& str);
int countIslands(int** grid, int rows, int cols);

// 1. çàÿö-÷åðåïàõà
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

        // Åñëè çàÿö äîãíàë ÷åðåïàõó - åñòü öèêë
        if (turtle == rabbit) {
            return true;
        }
    }

    return false;  // Çàÿö äîñòèã êîíöà ñïèñêà - öèêëà íåò
}
//ðàçâîðîò óêàçàòåëåé
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
    //ðàçâîðîò ñïèñêà
    while (current != nullptr) {
        next_node = current->next;
        current->next = prev;
        prev = current;
        current = next_node;

        // Åñëè ïîñëå ðàçâîðîòà ìû âåðíóëèñü ê èñõîäíîé ãîëîâå - öèêë!
        if (current == original_head) {
            has_cycle = true;
            break;
        }
    }

    // âîññòàíàâëèâàåì ñïèñîê 

    if (has_cycle) {
        // prev ñåé÷àñ óêàçûâàåò íà óçåë, ñ êîòîðîãî íà÷àëñÿ öèêë 
        // Íàõîäèì íà÷àëî öèêëà è ðàçðûâàåì åãî
        Node<T>* cycle_start = prev; 
        Node<T>* temp = cycle_start;

        // Èùåì óçåë, êîòîðûé ññûëàåòñÿ íà cycle_start, ÷òîáû ðàçîðâàòü öèêë
        while (temp != nullptr && temp->next != cycle_start) {
            temp = temp->next;
        }

        if (temp != nullptr) {
            temp->next = nullptr;
        }

        // Òåïåðü âîññòàíàâëèâàåì èñõîäíûé ñïèñîê
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
        // Åñëè öèêëà íå áûëî, ïðîñòî âîññòàíàâëèâàåì ñïèñîê
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
// 3. Àëãîðèòì ñ âîçâðàòîì óêàçàòåëÿ íà ìåñòî ïîëîìêè ñïèñêà
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

    // Ïîèñê íà÷àëà öèêëà
    turtle = head;
    while (turtle != rabbit) {
        turtle = turtle->next;
        rabbit = rabbit->next;
    }

    // turtle òåïåðü óêàçûâàåò íà íà÷àëî öèêëà
    return turtle;
}
