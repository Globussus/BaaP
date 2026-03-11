#include <iostream>
#include "tools.h"
#include "contextmenu.h"

int main(int argc, char **argv) {
    int task = chooseTask();
    std::string command;

    showMenu(task);

    while(true) {
        std::cout << "Введите команду: ";
        getline(std::cin, command);

        if (command == "1") {
            calculate(task);
        } else if (command == "0") {
            std::cout << "Завершение работы" << std::endl;
            break; 
        } else if (command == "2") {
            showMenu(task);
        } else {
            std::cout << "Программа не обрабатывает введенную команду" << std::endl;
        }
    }
}