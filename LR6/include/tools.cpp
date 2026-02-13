#include <iostream>
#include <cstring>

void show_instructions(int task) {
    switch(task) {
        case 1:
            std::cout << "Задание 1. Вариант 9. Выполнил: Глобаж Станислав" << std::endl;
            std::cout << "Пользователю нужно ввести строку из цифр(в случае, если попадутся нецифровые значения - программа завершит свое исполнение)" << std::endl;
            std::cout << "Программа находит в строке числа, сортирует их и выводит в порядке возрастания" << std::endl;
            break;
        case 2:
            std::cout << "Задание 2. Вариант 9. Выполнил: Глобаж Станислав" << std::endl;
            std::cout << "Пользователю нужно ввести любой текст.\nПрограмма вычисляет, каких букв больше: гласных или согласных?" << std::endl;
            std::cout << "Важное уточнение: программа не учитывает кириллицу(буквы из кириллицы не будут учитываться при подсчетах)" << std::endl;
            break;
        case 3:
            std::cout << "Задание 3. Вариант 9. Выполнил: Глобаж Станислав" << std::endl;
            std::cout << "Пользоваль вводит произвольное количество строк.\nВажное уточнение: программа не обрабатывает кириллицу" << std::endl;
            std::cout << "Программа проверяет строки на то, являются ли они симметрическими(такими, которые справа налево и слева направо читаются одинаково)" << std::endl;
            break;
    }
    std::cout << "Пользователю доступны следующие команды:" << std::endl;
	std::cout << "  0 — выход" << std::endl;
	std::cout << "  1 — запуск" << std::endl;
	std::cout << "  2 — выводит инструкцию по использованию программы\n" << std::endl;
}

bool is_empty_string(char* string) {
    bool flag = true;
    int index = 0;

    while (string[index] != '\0') {
        if (!isspace(string[index])) {
            flag = false;
            break;
        }
    }
    return flag;
}

void clean_input();

int select_task() {
    char task = 0;

    while (task != '1' && task != '2' && task != '3') {
        std::cout << "Введите номер задания: ";
        task = getchar();
        clean_input();

        if (task != '1' && task != '2' && task != '3') {
            std::cout << "Ошибка ввода. Повторите попытку!" << std::endl;
            clean_input();
        }
    }

    return task - '0';
}

void clean_input() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void input(const int max_size, char* string) {
    int i;
    int c;

    for (i = 0; i < max_size - 1 && (c = getchar()) != '\n' && c != EOF; i++) {
        string[i] = (char)c;
    }
    string[i] = '\0';
}

//Задание 1
bool is_string_of_digits(char* string) {
    bool flag = true;
    int index = 0;

    while (string[index] != '\0') {
        if (!isdigit(string[index]) && !isspace(string[index])) {
            flag = false;
            break;
        }
        index++;
    }
    return flag;
}

void divide_string(const int max_size, char* string, int* numbers) {
    int index = 0, numbers_index = 0;

    while(string[index] != '\0') {
        if (!isdigit(string[index])) {
            index++;
            continue;
        }

        int number = 0;

        while(isdigit(string[index])) {
            number = 10 * number + (string[index] - '0');
            index++;
        }
        numbers[numbers_index] = number;
        numbers_index++;
    }

}

int count_numbers(int max_size, char* string) {
    int index = 0, amount = 0;

    while(string[index] != '\0') {
        if (!isdigit(string[index])) {
            index++;
            continue;
        }
        int number = 0;
        while(isdigit(string[index])) {
            index++;
        }
        amount++;
    }
    return amount;
}

void bubble_sort(int* numbers, int length) {
    bool flag;
    int elem = 0;

    for (int i = 0; i < length; i++) {
        flag = true;
        for (int j = 0; j < length - i - 1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                elem = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = elem;
                flag = false;
            }
        }

        if (flag) {
            break;
        }
    }
}

//Задание 2
bool is_in_string(char* string, char element, int size) {
    for (int i = 0; i < size; i++) {
        if (string[i] == element) {
            return true;
        }
    }
    return false;
}

int get_length_of_string(char* string);

int count_vowels(char* string) {
    char vowels[] = {'a', 'e', 'i', 'o', 'u', 'y', '\0'};
    int counter = 0, index = 0;

    std::cout << "Гласные буквы: " << std::endl;
    while (string[index] != '\0') {
        char current_elem = tolower(string[index]);
        if (is_in_string(vowels, current_elem, get_length_of_string(vowels))) {
            std::cout << string[index];
            counter++;
        }
        index++;
    }
    std::cout << std::endl;
    return counter;
}

int count_consonants(char* string) {
    char consonants[] = {'q', 'w', 'r', 't', 'p', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm', '\0'};
    int counter = 0, index = 0;

    std::cout << "Согласные буквы: " << std::endl;
    while (string[index] != '\0') {
        char current_elem = tolower(string[index]);
        if (is_in_string(consonants, current_elem, get_length_of_string(consonants))) {
            std::cout << string[index];
            counter++;
        }
        index++;
    }
    std::cout << std::endl;
    return counter;
}

//Задание 3
char to_lower(char element);

bool check_is_palindrome(char* string, int length) {
    bool flag = true;

    for (int i = 0; i < length; i++) {
        if (to_lower(string[i]) != to_lower(string[length - 1 - i])) {
            flag = false;
            break;
        }
    }
    return flag;
}

void print_reversed_string(char* string, int length) {
    for (int i = 0; i < length; i++) {
        std::cout << string[length - 1 - i];
    }
    std::cout << std::endl;
}

int get_length_of_string(char* string) {
    int counter = 0;
    int index = 0;

    while (string[index] != '\0') {
        counter++;
        index++;
    }
    return counter;
}

int count_spaces(char* string, int length) {
    int counter = 0;

    for (int i = 0; i < length; i++) {
        if (string[i] == ' ') {
            counter++;
        }
    }
    return counter;
}

char to_lower(char element) {
    if (element >= 64 && element <= 90) {
        element += 32;
    }
    return element;
}

void calculate(int task) {
    switch(task) {
        case 1: {
            const int max_size = 80;
            char* string = new char[max_size];

            std::cout << "Введите строку: ";
            input(max_size, string);

            if (!is_empty_string(string)) {
                std::cout << "Исходная строка: ";
                int i = 0;
                while(string[i] != '\0') {
                    std::cout << string[i];
                    i++;
                }
                std::cout << std::endl;

                if (is_string_of_digits(string)) {
                    const int amount = count_numbers(max_size, string);
                    int* numbers = new int[amount];

                    divide_string(max_size, string, numbers);
                    std::cout << "Числа в порядке возрастания: " << std::endl;
                    bubble_sort(numbers, amount);

                    for (int i = 0; i < amount; i++) {
                        std::cout << numbers[i] << ' ';
                    }
                    std::cout << std::endl;

                    delete[] numbers;

                } else {    
                    std::cout << "Строка не состоит исключительно из цифр и пробелов" << std::endl;
                }
            } else {
                std::cout << "Вы ввели пустую строку!" << std::endl;
            }

            delete[] string;
            break;
        }
        case 2: {
            const int max_size = 128;
            char* string = new char[max_size];

            std::cout << "Введите строку: ";
            input(max_size, string);

             if (!is_empty_string(string)) {
                std::cout << "Исходная строка: ";
                int i = 0;
                while (string[i] != '\0') {
                    std::cout << string[i];
                    i++;
                }
                std::cout << std::endl;

                int amount_of_vowels = count_vowels(string);
                std::cout << "Количество гласных букв равно: " << amount_of_vowels << std::endl;
                int amount_of_consonants = count_consonants(string);
                std::cout << "Количество согласных букв равно: " << amount_of_consonants << std::endl;

                if (amount_of_vowels > amount_of_consonants) {
                    std::cout << "Гласных букв в тексте больше!" << std::endl;
                } else if (amount_of_consonants > amount_of_vowels) {
                    std::cout << "Согласных букв в тексте больше!" << std::endl;
                } else {
                    std::cout << "Согласных и гласных букв в тексте одинаковое количество!" << std::endl;
                }
            } else {
                std::cout << "Вы ввели пустую строку!" << std::endl;
            }

            delete[] string;
            break;
        }
        case 3: {
            const int max_size = 128;
            char** string_array = new char* [100] {nullptr};
            int real_string_count = 0;
            
            for(int i = 0; i < 100; i++) {
                string_array[i] = new char [max_size] {};
                std::cout << "Введите строку: ";
                input(max_size, string_array[i]);
                if (is_empty_string(string_array[i])) {
                    delete[] string_array[i];
                    string_array[i] = nullptr;
                    break;
                }
                real_string_count++;
            }

            if (real_string_count > 0) {
                for (int index = 0; index < real_string_count; index++) {
                    const int string_length = get_length_of_string(string_array[index]);

                    std::cout << "Исходная строка: " << std::endl;
                    for (int i = 0; i < string_length; i++) {
                        std::cout << string_array[index][i];
                    }
                    std::cout << std::endl;

                    const int string_copy_size = string_length - count_spaces(string_array[index], string_length);
                    char* string_copy = new char[string_copy_size + 1] {};

                    int copy_index = 0;
                    for (int i = 0; i < string_length; i++) {
                        if (string_array[index][i] != ' ') {
                            string_copy[copy_index++] = string_array[index][i];
                        }
                    }
                    string_copy[string_copy_size] = '\0';

                    if (check_is_palindrome(string_copy, string_copy_size)) {
                        std::cout << "Данная строка является симметричной" << std::endl;
                    } else {
                        std::cout << "Данная строка не является симметричной" << std::endl;
                    }

                    delete[] string_copy;

                    std::cout << "Перевернутая строка: " << std::endl;
                    print_reversed_string(string_array[index], string_length);
                    std::cout << std::endl;
                }

                for (int i = 0; i < 100; i++) {
                    if (string_array[i] != nullptr) {
                        delete[] string_array[i];
                    }
                }
            } else {
                std::cout << "Программа не может начать свою работу, так как вы не ввели непустую строку!" << std::endl;
            }
            delete[] string_array;
        }
    }
}

bool are_equivalent_arrays(int* numbers, int* another, int first_size, int second_size) {
    if (first_size != second_size) {
        return false;
    }

    for (int i = 0; i < first_size; i++) {
        if (numbers[i] != another[i]) {
            return false;
        }
    }
    return true;
}