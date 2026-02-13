#include <iostream>
#include "../include/InputChecker.h"

void CleanInput() {
    std::cin.clear();
    std::cin.ignore(32767, '\n');
};

void CheckIntInput(int &number, std::string message) {
    while ((std::cin >> number).fail()) {
        if (std::cin.fail()) {
            std::cout <<"Ошибка ввода. Повторите попытку" << std::endl; 
            CleanInput();
        } else {
            break;
        }
        std::cout << message;
    }
    CleanInput();
}

void CheckFloatInput(float &number, std::string message) {
    while ((std::cin >> number).fail()) {
        if (std::cin.fail()) {
            std::cout <<"Ошибка ввода. Повторите попытку" << std::endl; 
            CleanInput();
        } else {
            break;
        }
        std::cout << message;
    }
    CleanInput();
}