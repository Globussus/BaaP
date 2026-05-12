#ifndef DEQUE_H
#define DEQUE_H

#include <stdexcept>
#include <string>

struct ListElement {
    ListElement(int elemValue, ListElement* nextElem, ListElement* prevElement) 
        : value(elemValue), next(nextElem), prev(prevElement) {}
    int value;
    ListElement* next;
    ListElement* prev;
};

class Deque {
private:
    ListElement* head;
    ListElement* tail;
    int amount;
    
public:
    Deque() : head(nullptr), tail(nullptr), amount(0) {}
    
    ~Deque() {
        clear();
    }
    
    void pushBack(int value) {
        ListElement *newElement = new ListElement(value, nullptr, nullptr);
        if (isEmpty()) {
            head = tail = newElement;
        } else {
            newElement->prev = tail;
            tail->next = newElement;
            tail = newElement;
        }
        amount++;
    }

    void pushFront(int value) {
        ListElement *newElement = new ListElement(value, nullptr, nullptr);
        if (isEmpty()) {
            head = tail = newElement;
        } else {
            newElement->next = head;
            head->prev = newElement;
            head = newElement;
        }
        amount++;
    }

    int popBack() {
        if (isEmpty()) {
            throw std::runtime_error("Очередь пустая");
        }
        ListElement *temp = tail;
        int value = temp->value;
        
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        
        amount--;
        delete temp;
        return value;
    }

    int popFront() {
        if (isEmpty()) {
            throw std::runtime_error("Очередь пустая");
        }
        ListElement *temp = head;
        int value = temp->value;
        
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        
        amount--;
        delete temp;
        return value;
    }

    bool isEmpty() const { return head == nullptr; }

    int front() const {
        if (isEmpty()) {
            throw std::runtime_error("Очередь пустая");
        }
        return head->value;
    }

    int back() const {
        if (isEmpty()) {
            throw std::runtime_error("Очередь пустая");
        }
        return tail->value;
    }

    int size() const {
        return amount;
    }

    void clear() {
        while (!isEmpty()) {
            popBack();
        }
    }
    
    // Делаем MainWindow другом, чтобы он мог доступиться к head
    friend class MainWindow;
    
    // Метод для решения задачи варианта 7
    void splitByMinMax(Deque& firstRing, Deque& secondRing) {
        if (isEmpty()) return;
        
        // Находим индексы минимального и максимального элементов
        int minIdx = 0, maxIdx = 0;
        int minVal = head->value, maxVal = head->value;
        
        ListElement* current = head;
        int idx = 0;
        while (current != nullptr) {
            if (current->value < minVal) {
                minVal = current->value;
                minIdx = idx;
            }
            if (current->value > maxVal) {
                maxVal = current->value;
                maxIdx = idx;
            }
            current = current->next;
            idx++;
        }
        
        // Определяем границы
        int startIdx = std::min(minIdx, maxIdx);
        int endIdx = std::max(minIdx, maxIdx);
        
        // Распределяем элементы
        current = head;
        idx = 0;
        while (current != nullptr) {
            if (idx > startIdx && idx < endIdx) {
                firstRing.pushBack(current->value);
            } else {
                secondRing.pushBack(current->value);
            }
            current = current->next;
            idx++;
        }
    }
};

#endif