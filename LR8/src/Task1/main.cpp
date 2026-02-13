#include <iostream>
#include "../../include/Production.h"
#include "../../include/InputChecker.h"

std::string ChooseFunction() {
    std::string function;
    std::cout << "Введите функцию: ";
    getline(std::cin, function);
    return function;
}

void Help() {
    std::cout << "==========================================МЕНЮ==========================================" << std::endl;
    std::cout << "Программа предназначена для взаимодействия пользователя с информацией о продукции цехов завода" << std::endl;
    std::cout << "Пользователю доступны следующие команды: " << std::endl;
    std::cout << "  e - Завершение работы" << std::endl;
    std::cout << "  m - Вывод меню" << std::endl;
    std::cout << "  1 - Формирование массива из определенного кол-ва вводимых пользователем товаров с цехов завода." << std::endl;
    std::cout << "      Если хотите завершить ввод раньше момента полного заполнения массива - в поле 'имя' ничего не вводите" << std::endl;
    std::cout << "  2 - Вывод информации о всех товарах" << std::endl;
    std::cout << "  3 - Функция позволяет добавить в массив новый товар" << std::endl;
    std::cout << "  4 - Осуществляет поиск товара по названию и выводит информацию о нем" << std::endl;
    std::cout << "  5 - Позволяет удалить товар из массива" << std::endl;
    std::cout << "  6 - Функция, позволяющая изменить название товара" << std::endl;
    std::cout << "  7 - Функция, которая выводит товары в порядке убывания количества выпущенной продукции" << std::endl;
    std::cout << "  w - Функция, которая позволяет записать структуру в бинарный файл" << std::endl;
    std::cout << "  r - Функция, которая считывает запись файла из бинарного файла" << std::endl;
    std::cout << "  a - Функция, которая при вводе пользователем названия элемента меняет его в записи" << std::endl;
    std::cout << "========================================================================================" << std::endl;
}

int main() {
    production_t* array = nullptr;
    int length = 0;
    std::string function;

    Help();
    std::cout << "Введите длину массива товаров: ";
    std::cin >> length;
    CleanInput();
    while (true) {
        function = ChooseFunction();
        if (function == "e") {
            std::cout << "Завершение работы" << std::endl;
            break;
        } else if (function == "m") {
            Help();
        } else if (function == "1") {
            array = FillArray(length);
        } else if (function == "2") {
            if (array == nullptr || length == 0) {
                std::cout << "Массив пуст!" << std::endl;
                continue;
            }
            ShowStructObjects(array, length);
        } else if (function == "3") {
            production_t new_object = CreateObject();
            array = PutObjectToArray(array, new_object, length);
        } else if (function == "4") {
            if (array == nullptr || length == 0) {
                std::cout << "Массив пуст!" << std::endl;
                continue;
            }
            std::string name;
            std::cout << "Введите название товара: ";
            getline(std::cin, name);
            int index = FindObjectIndex(array, length, name);
            if (index == -1) {
                std::cout << "Данный объект не был найден среди товаров" << std::endl;
            } else {
                ShowObject(array[index], index);
            }
        } else if (function == "5") {
            if (array == nullptr || length == 0) {
                std::cout << "Массив пуст!" << std::endl;
                continue;
            }
            std::string name;
            std::cout << "Введите название товара: ";
            getline(std::cin, name);
            int index = FindObjectIndex(array, length, name);
            if (index == -1) {
                std::cout << "Данный объект не был найден среди товаров" << std::endl;
            } else {
                std::cout << "Объект с имененем " << name << " был удален из массива товаров" << std::endl;
                array = DeleteObject(array, array[index], length);
            }
        } else if (function == "6") {
            if (array == nullptr || length == 0) {
                std::cout << "Массив пуст!" << std::endl;
                continue;
            }
            std::string name;
            std::cout << "Введите название товара: ";
            getline(std::cin, name);
            int index = FindObjectIndex(array, length, name);
            if (index == -1) {
                std::cout << "Данный объект не был найден среди товаров" << std::endl;
            }  else {  
                std::string new_name;
                std::cout << "Введите новое название товара: ";
                getline(std::cin, new_name);
                ChangeObject(array, length, array[index], new_name);
            } 
        } else if (function == "7") {
            if (array == nullptr || length == 0) {
                std::cout << "Массив пуст!" << std::endl;
                continue;
            }
            ShowObjectsQuantity(array, length);
        } else if (function == "w") {
            Save(array, length);
        } else if (function == "r") {
            Read(array, length);
        } else if (function == "a") {
            std::string name; 
            std::cout << "Введите название изменяемого в записи товара: ";
            getline(std::cin, name);
            ChangeEntry(array, length, name);
        }else {
            std::cout << "Данная команда не обрабатывается программой. Повторите попытку!" << std::endl;
        }
        std::cout << std::endl;

    }
    delete[] array;
    return 0;
}