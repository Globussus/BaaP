#include "contextmenu.h"

int chooseTask() {
    char task = 0;
    while (task != '1' && task != '2' && task != '3' && task != '4') {
        std::cout << "Введите номер задания: ";
        task = getchar();
        cleanInput();
        if (task != '1' && task != '2' && task != '3' && task != '4') {
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
            std::cout << "Задание 1. Программа преобразовывает \nвещественное десятичное число в двоичное" << std::endl;
            break;
        case 2:
            std::cout << "Задание 2. Программа считает значение функции Аккермана от переменных m и n" << std::endl;
            break;
        case 3:
            std::cout << "Задание 3. Программа выводит число, записанное теми же цифрами в обратном порядке" << std::endl; 
            break;
        case 4:
            std::cout << "Задание 4. Ханойская башня" << std::endl;
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
    switch(task) {
        case 1: {
            double number;
            std::cout << "Введите число: ";
            if (!(std::cin >> number)) {
                std::cout << "Некорректный ввод!" << std::endl;
                std::cin.clear();
                cleanInput();
                break;
            }
            cleanInput();
            std::cout << "Исходное число в двоичной форме: " << decimalToBinary(number) << std::endl; 
            break;
        }
        case 2: {
            int m, n;
            std::cout << "Введите число m: ";
            if (!(std::cin >> m)) {
                std::cout << "Некорректный ввод!" << std::endl;
                std::cin.clear();
                cleanInput();
                break;
            }
            cleanInput();
            std::cout << "Введите число n: ";
            if (!(std::cin >> n)) {
                std::cout << "Некорректный ввод!" << std::endl;
                std::cin.clear();
                cleanInput();
                break;
            }
            cleanInput();
            if (m > 0 && n > 0) {
                std::cout << "Ackerman(m, n) = " << ackermannsFunction(m, n, 100) << std::endl;
            } else {
                std::cout << "Введите положительные числа!" << std::endl;
            }
            break;
        }
        case 3: {
            int number;
            std::cout << "Введите число: ";
            if (!(std::cin >> number)) {
                std::cout << "Некорректный ввод!" << std::endl;
                std::cin.clear();
                cleanInput();
                break;
            }
            cleanInput();
            std::cout << "Число в обратном порядке: " << reverse(number, 0) << std::endl;
            break; 
        }
        case 4: {
            int number;
            std::cout << "Введите число: ";
            if (!(std::cin >> number)) {
                std::cout << "Некорректный ввод!" << std::endl;
                std::cin.clear();
                cleanInput();
                break;
            }
            cleanInput();
            hanoi(number, 1, 3);
            break;
        }
    }
}
