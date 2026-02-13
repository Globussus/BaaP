#include <iostream>
#include "../../include/Library.h"
#include "../../include/InputChecker.h"

std::string ChooseFunction() {
    std::string function;
    std::cout << "Введите функцию: ";
    getline(std::cin, function);
    return function;
}

void Help() {
    std::cout << "==========================================МЕНЮ==========================================" << std::endl;
    std::cout << "Программа создана для взаимодействия с книгами из библиотеки" << std::endl;
    std::cout << "Пользователю доступны следующие команды: " << std::endl;
    std::cout << "  e - Завершение работы" << std::endl;
    std::cout << "  m - Вывод меню" << std::endl;
    std::cout << "  1 - Формирование массива из определенного количества вводимых пользователем книг из библиотеки" << std::endl;
    std::cout << "      Если хотите завершить ввод раньше момента полного заполнения массива - в поле 'название' ничего не вводите" << std::endl;
    std::cout << "  2 - Вывод информации о всех книгах" << std::endl;
    std::cout << "  3 - Функция позволяет добавить в массив новую книгу" << std::endl;
    std::cout << "  4 - Позволяет удалить книгу из массива" << std::endl;
    std::cout << "  5 - Функция выводит список книг, изданных после определенного года, с фамилиями авторов в алфавитном порядке" << std::endl;
    std::cout << "  s - Функция, которая позволяет сохранить список книг в текстовом файле" << std::endl;
    std::cout << "  r - Функция, которая позволяет прочитать из файла список" << std::endl;
    std::cout << "  a - Функция, которая при вводе пользователем книги заменяет ее в записи на новую";
    std::cout << "========================================================================================" << std::endl;
}

int main() {
    library_t* array = nullptr;
    int length = 0;
    std::string function;

    Help();
    std::cout << "Введите длину массива книг: ";
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
                std::cout << "Массив книг пуст!" << std::endl;
                continue;
            }
            ShowBookshelve(array, length);
        } else if (function == "3") {
            library_t new_book = Initialisation();
            array = AddBook(array, new_book, length);
        } else if (function == "4") {
            if (array == nullptr || length == 0) {
                std::cout << "Массив книг пуст!" << std::endl;
                continue;
            }
            std::string title;
            std::cout << "Введите название книги: ";
            getline(std::cin, title);
            int index = FindBookIndex(array, length, title);
            if (index == -1) {
                std::cout << "Данной книги в библиотеке нет!" << std::endl;
            } else {
                std::cout << "Книга с названием " << title << " была удалена из массива книг" << std::endl;
                array = DeleteBook(array, array[index], length);
            }
        } else if (function == "5") {
            int year;
            std::cout << "Введите год: ";
            CheckIntInput(year, "Введите год: ");
            PrintBookList(array, length, year);
        } else if (function == "s") {
            Save(array, length);
        } else if (function == "r") {
            Read(array, length);
        } else if (function == "a") {
            std::string book;
            std::cout << "Введите название книги, которую хотите заменить: ";
            getline(std::cin, book);
            Change(array, length, book);
        } else {
            std::cout << "Данная команда не обрабатывается программой. Повторите попытку!" << std::endl;
        }
        std::cout << std::endl;
    }
    delete[] array;
    return 0;
}