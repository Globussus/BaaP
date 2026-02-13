#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "../include/Library.h"
#include "../include/InputChecker.h"

bool IsEmptyString(char* string) {
    int index = 0;
    while (string[index] != '\0') {
        if (string[index] != ' ') {
            return false;
        }
    }
    return true;
}

bool IsNullObject(library_t book) {
    switch(book.mark_type) {
        case 'l':
            return (IsEmptyString(book.title) && IsEmptyString(book.author) && IsEmptyString(book.publisher) && IsEmptyString(book.mark.letter_mark) && 
                book.registration_number == 0 && book.publishing_year == 0 && book.pages_quantity == 0);
        case 'p':
            return (IsEmptyString(book.title) && IsEmptyString(book.author) && IsEmptyString(book.publisher) && book.mark.percentage == 0 && 
                book.registration_number == 0 && book.publishing_year == 0 && book.pages_quantity == 0);
        default: 
            return false;
    }
}

library_t Initialisation() {
    std::string author, title, publisher;
    int registration_number, publishing_year, pages_quantity;
    char mark_type;
    std::cout << "Введите название книги: ";
    getline(std::cin, title);
    std::cout << "Введите автора книги: ";
    getline(std::cin, author);
    std::cout << "Введите издателя книги: ";
    getline(std::cin, publisher);
    std::cout << "Введите регистрационный номер книги: ";
    CheckIntInput(registration_number, "Введите регистрационный номер книги: ");
    std::cout << "Введите год издания книги: ";
    CheckIntInput(publishing_year, "Введите год издания книги: ");
    std::cout << "Введите кол-во страниц в книге: ";
    CheckIntInput(pages_quantity, "Введите кол-во страниц в книге: ");
    std::cout << "Введите, как именно вы хотите вписать рейтинг книги: l - если хотите записать оценку буквой (A, B, C, D, E, F)\n" \
        " p - если хотите записать оценку в в процентном соотношении (от 0 до 100 %): ";
    std::cin >> mark_type;
    CleanInput();
    switch (mark_type) {
        case 'l': {
            std::string letter_mark;
            std::cout << "Введите буквенную оценку: ";
            getline(std::cin, letter_mark);
            if (letter_mark != "A" && letter_mark != "B" && letter_mark != "C" & letter_mark != "D" && letter_mark != "E" && letter_mark == "F") {
                letter_mark = "F";
            }
            library_t book;
            strcpy(book.title, title.c_str());
            strcpy(book.author, author.c_str());
            strcpy(book.publisher, publisher.c_str());
            strcpy(book.mark.letter_mark, letter_mark.c_str());
            book.registration_number = registration_number;
            book.publishing_year = publishing_year;
            book.pages_quantity = pages_quantity;
            book.mark_type = mark_type;
            return book;
        }
        case 'p': {
            int percentage = 0;
            std::cout << "Введите оценку книги в процентном отношении: ";
            CheckIntInput(percentage, "Введите оценку книги в процентном отношении: ");
            if (percentage < 0 || percentage > 100) {
                percentage = 0;
            }
            library_t book;
            strcpy(book.title, title.c_str());
            strcpy(book.author, author.c_str());
            strcpy(book.publisher, publisher.c_str());
            book.mark.percentage = percentage;
            book.registration_number = registration_number;
            book.publishing_year = publishing_year;
            book.pages_quantity = pages_quantity;
            book.mark_type = mark_type;
            return book;
        }
        default: {
            library_t book;
            strcpy(book.title, title.c_str());
            strcpy(book.author, author.c_str());
            strcpy(book.publisher, publisher.c_str());
            book.registration_number = registration_number;
            book.publishing_year = publishing_year;
            book.pages_quantity = pages_quantity;
            book.mark_type = mark_type;
            return book;
        }
    }
}

library_t* ResizeArray(library_t* array, int &length, int new_length) {
    library_t* new_array = new library_t[new_length];
    int elements_to_copy = (length < new_length) ? length : new_length;
    for (int i = 0; i < elements_to_copy; i++) {
        new_array[i] = array[i];
    }
    delete[] array;
    length = new_length;
    return new_array;
}

library_t* FillArray(int &length) {
    std::string flag;
    library_t* array = new library_t[length];
    for (int i = 0; i < length; i++) {
        std::cout << "Книга №" << i + 1 << ":" << std::endl;
        library_t new_object = Initialisation();
        if (IsNullObject(new_object)) {
            std::cout << "Ввод отменен. Завершение ввода" << std::endl;
            array = ResizeArray(array, length, i);
            break;
        }
        array[i] = new_object;
        if (i != length - 1) {
            std::cout << "Желаете ли продолжить ввод(y - если да/n - если нет)?: ";
            std::cin >> flag;
            CleanInput();
        }
        if (flag == "n" || flag == "N") {
            array = ResizeArray(array, length, i + 1);
            break;
        } 
        std::cout << std::endl;
    }
    std::cout << "Завершение ввода" << std::endl;
    return array;
}

void ShowBook(library_t book, int index) {
    if (IsNullObject(book)) {
        return;
    }
    std::cout << "Книга №" << index + 1 << ":" << std::endl;
    std::cout << "Название книги: " << book.title << std::endl;
    std::cout << "Автор книги: " << book.author << std::endl;
    std::cout << "Издатель книги: " << book.publisher << std::endl;
    switch (book.mark_type) {
        case 'l':
            std::cout << "Оценка книги: " << book.mark.letter_mark << std::endl;
            break;
        case 'p':
            std::cout << "Оценка книги: " << book.mark.percentage << " %" << std::endl;
            break;
        default:
            std::cout << "Оценка книги не указана" << std::endl;
            break;
    }
    std::cout << "Регистрационный номер книги: " << book.registration_number << std::endl;
    std::cout << "Год издания книги: " << book.publishing_year << std::endl;
    std::cout << "Количество страниц в книге: " << book.pages_quantity << std::endl;
}

void ShowBookshelve(library_t* array, int length) {
    if (length > 0) {
        int index = 0;
        std::cout << "========================Список книг========================" << std::endl;
        while (index < length) {
            ShowBook(array[index], index);
            index++;
            std::cout << std::endl;
        }
        std::cout << "===========================================================" << std::endl;
    } else {
        std::cout << "Книжная полка пуста" << std::endl;
    }
}

library_t* AddBook(library_t* array, library_t book, int &length) {
    if (!IsNullObject(book)) {
        int old_length = length;
        array = ResizeArray(array, length, old_length + 1);
        array[length - 1] = book;
    }
    return array;
}

bool CompareBooks(library_t book, library_t other_book) {
    if (book.mark_type != book.mark_type) {
        return false;
    }
    if (book.title != other_book.title || 
        book.author != other_book.author || 
        book.publisher != other_book.publisher ||
        book.registration_number != other_book.registration_number ||
        book.publishing_year != other_book.publishing_year ||
        book.pages_quantity != other_book.pages_quantity) {
        return false;
    }
    switch (book.mark_type) {
        case 'l':
            return book.mark.letter_mark == other_book.mark.letter_mark;
        case 'p':
            return book.mark.percentage == other_book.mark.percentage;
        default:
            return false;
    }
}

int FindBookIndex(library_t* array, int length, std::string title) {
    int index = -1;
    for (int i = 0; i < length; i++) {
        if (array[i].title != nullptr && std::string(array[i].title) == title) {
            index = i;
            break;
        }
    }
    return index;
}

library_t* DeleteBook(library_t* array, library_t book, int &length) {
    if (length == 0) {
        std::cout << "Книжная полка пуста!";
        return array;
    }
    library_t* new_array = new library_t[length - 1];
    int current_index = 0;
    for (int i = 0; i < length; i++) {
        if (CompareBooks(book, array[i])) {
            continue;
        }
        new_array[current_index++] = array[i];
    }
    length -= 1;
    delete[] array;
    return new_array;
}

void Sort(library_t* array, int length) {
    bool flag;
    for (int i = 0; i < length; i++) {
        flag = true;
        for (int j = 0; j < length - i - 1; j++) {
            if (std::string(array[j].author) > std::string(array[j + 1].author)) {
                flag = false;
                std::swap(array[j], array[j + 1]);
            }
        }
        if (flag) {
            break;
        }
    }
}

void PrintBookList(library_t* array, int &length, int year) {
    int new_length = 0;
    for (int i = 0; i < length; i++) {
        if (array[i].publishing_year >= year) {
            new_length++;
        }
    }
    if (new_length == 0) {
        std::cout << "В массиве нет книг, выпущенных после " << year << " года!" << std::endl;
    } else {
        const int size = new_length;
        library_t* new_array = new library_t[size];
        int current_index = 0;
        for (int i = 0; i < length; i++) {
            if (array[i].publishing_year >= year) {
                new_array[current_index++] = array[i];
            }
        }
        Sort(new_array, size);
        ShowBookshelve(new_array, size);
        delete[] new_array;
    }
}

std::string ChangeString(char* string, char sign, char new_sign) {
    std::string string_copy = (std::string) string;
    for (int i = 0; i < string_copy.length(); i++) {
        if (string_copy[i] == sign) {
            string_copy[i] = new_sign;
        }
    }
    return string_copy;
}

void Save(library_t* array, int length) {
    std::fstream file;
    file.open("library.txt", std::ios::out);
    for (int i = 0; i < length; i++) {
        std::stringstream ss;
        ss << ChangeString(array[i].title, ' ', '_') << ' ' << ChangeString(array[i].author, ' ', '_') << ' ' << ChangeString(array[i].publisher, ' ', '_') 
            << ' ' << array[i].registration_number << ' ' << array[i].publishing_year << ' ' << array[i].pages_quantity << ' ' << array[i].mark_type;
        switch (array[i].mark_type) {
            case 'l':
                ss << ' ' << array[i].mark.letter_mark;
                break;
            case 'p':
                ss << ' ' << array[i].mark.percentage;
                break;
        }
        file << std::setw(MAX_STRING_SIZE * 3) << std::setfill(' ') << std::left << ss.str() << std::endl;
    }
    file.close();
}

void Read(library_t* &array, int &length) {
    std::fstream file;
    std::string line;
    file.open("library.txt", std::ios::in);
    if (file.good()) {
        if (array != nullptr) {
            delete[] array;
            array = nullptr;
            length = 0;
        }
        while(getline(file, line)) {
            length++;
        }
        file.clear();
        file.seekg(0, file.beg);
        array = new library_t[length];
        for (int i = 0; i < length; i++) {
            std::string title, author, publisher;
            file >> title >> author >> publisher >> array[i].registration_number >> array[i].publishing_year >> array[i].pages_quantity >> array[i].mark_type;
            strncpy(array[i].title, title.c_str(), sizeof(array[i].title) - 1);
            array[i].title[sizeof(array[i].title) - 1] = '\0';
            ChangeString(array[i].title, '_', ' ');
            
            strncpy(array[i].author, author.c_str(), sizeof(array[i].author) - 1);
            array[i].author[sizeof(array[i].author) - 1] = '\0';
            ChangeString(array[i].author, '_', ' ');
            
            strncpy(array[i].publisher, publisher.c_str(), sizeof(array[i].publisher) - 1);
            array[i].publisher[sizeof(array[i].publisher) - 1] = '\0';
            ChangeString(array[i].publisher, '_', ' ');
            switch (array[i].mark_type) {
                case 'l': 
                    file >> array[i].mark.letter_mark;
                    break;
                case 'p':
                    file >> array[i].mark.percentage;
                    break;
            }
        }
        file.close();
    }
}

void Change(library_t* array, int length, std::string name) {
    int book_index = FindBookIndex(array, length, name);
    if (book_index == -1) {
        std::cout << "Запись не найдена" << std::endl;
        return;
    }
    std::fstream file;
    file.open("library.txt", std::ios::in | std::ios::out);
    if (file.good()) {
        int size = 0;
        std::string line;
        while (getline(file, line)) {
            size++;
        }
        file.clear();
        file.seekg(0, file.beg);
        if (book_index < size) {
            std::cout << "Книга №" << book_index + 1 << ":" << std::endl;
            library_t new_book = Initialisation();
            array[book_index] = new_book;
            std::stringstream ss, line;
            ss << ChangeString(new_book.title, ' ', '_') << ' ' << ChangeString(new_book.author, ' ', '_') << ' ' << ChangeString(new_book.publisher, ' ', '_') 
                << ' ' << new_book.registration_number << ' ' << new_book.publishing_year << ' ' << new_book.pages_quantity << ' ' << new_book.mark_type;
            switch (new_book.mark_type) {
                case 'l':
                    ss << ' ' << new_book.mark.letter_mark;
                    break;
                case 'p':
                    ss << ' ' << new_book.mark.percentage;
                    break;
            }
            line << std::setw(MAX_STRING_SIZE * 3) << std::setfill(' ') << std::left << ss.str() << std::endl;
            file.seekg(book_index * line.str().size(), file.beg);
            file.write(line.str().c_str(), line.str().size());
        } else {
            std::cout << "Количество книг в записи меньше чем индекс введенной книги!" << std::endl;
        }
        file.close();
    }
}