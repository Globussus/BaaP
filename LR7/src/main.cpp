#include <iostream>
#include <string>
#include "../include/tools.h"

int main() {
    int task = select_task();
    std::string command;

    show_instructions(task);

    while(true) {
        std::cout << "Введите команду: ";
        getline(std::cin, command);

        if (command == "1") {
            calculate(task);
        } else if (command == "0") {
            std::cout << "Завершение работы" << std::endl;
            break; 
        } else if (command == "2") {
            show_instructions(task);
        } else {
            std::cout << "Программа не обрабатывает введенную команду" << std::endl;
        }
    }
}