#include "./../include/tools.h"
#include "./../include/contextmenu.h"
#include <iostream>
#include <memory>
#include <chrono>
#include <stdexcept>

int chooseTask() {
    char task = 0;
    while (task != '1' && task != '2' && task != '3') {
        std::cout << "Введите номер задания: ";
        task = getchar();
        cleanInput();
        if (task != '1' && task != '2' && task != '3') {
            std::cout << "Ошибка ввода. Повторите попытку!" << std::endl;
        }
    }
    return task - '0';
}

void cleanInput() {
    std::cin.clear();
    std::cin.ignore(32657, '\n');
}

void showMenu(int task) {
    std::cout << "=========================Контекстное меню=========================" << std::endl;
    switch(task) {
        case 1:
            std::cout << "Задание 1. Бинарный поиск" << std::endl;
            break;
        case 2:
            std::cout << "Задание 2. Интерполяционная сортировка" << std::endl;
            break;
        case 3:
            std::cout << "Задание 3. Программа выводит число, записанное теми же цифрами в обратном порядке" << std::endl; 
            break;
    }
    std::cout << std::endl;
    std::cout << "Пользователю доступны следующие команды:" << std::endl;
	std::cout << "  0 — выход" << std::endl;
	std::cout << "  1 — запуск" << std::endl;
	std::cout << "  2 — выводит инструкцию по использованию программы\n" << std::endl;
    std::cout << "==================================================================" << std::endl;
}

void calculate(int task) {
    switch (task) {
        case 1: {
            try {
                int n;
                std::cout << "Введите число n: ";
                if (!(std::cin >> n)) {
                    throw std::runtime_error("Некорректный ввод");
                }
                cleanInput();
                std::unique_ptr<int[]> array = std::make_unique<int[]>(n);
                std::unique_ptr<int[]> arrayCopy = std::make_unique<int[]>(n);
                std::cout << "Исходный массив:" << std::endl;
                for (int i = 0; i < n; i++) {
                    array[i] = rand() % 100;
                    std::cout << array[i] << " ";
                }
                std::cout << std::endl << std::endl;

                std::copy(array.get(), array.get() + n, arrayCopy.get());
                auto start = std::chrono::high_resolution_clock::now();
                heapSort(arrayCopy, n);
                auto end = std::chrono::high_resolution_clock::now();
                float heap_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                std::cout << "Исходный массив после сортировки кучей: ";
                for (int i = 0; i < n; i++) {
                    std::cout << arrayCopy[i] << " ";
                }
                std::cout << std::endl;
                std::cout << "Время исполнения сортировки кучей: " << heap_duration << " мск" << std::endl << std::endl;
                
                std::copy(array.get(), array.get() + n, arrayCopy.get());
                start = std::chrono::high_resolution_clock::now();
                mergeSort(arrayCopy, 0, n - 1);
                end = std::chrono::high_resolution_clock::now();
                float merge_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                std::cout << "Исходный массив после сортировки слиянием: ";
                for (int i = 0; i < n; i++) {
                    std::cout << arrayCopy[i] << " ";
                }
                std::cout << std::endl;
                std::cout << "Время исполнения сортировки слиянием: " << merge_duration << " мск" << std::endl << std::endl;

                std::copy(array.get(), array.get() + n, arrayCopy.get());
                start = std::chrono::high_resolution_clock::now();
                quickSort(arrayCopy, 0, n - 1);
                end = std::chrono::high_resolution_clock::now();
                float quick_sort_duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                std::cout << "Исходный массив после быстрой сортировки: ";
                for (int i = 0; i < n; i++) {
                    std::cout << arrayCopy[i] << " ";
                }
                std::cout << std::endl;
                std::cout << "Время исполнения быстрой сортировки: " << quick_sort_duration << " мск" << std::endl << std::endl;

                break;
            } catch (std::runtime_error &error) {
                std::cout << error.what() << std::endl;
                cleanInput();
                break;
            }
        }
    }
}
