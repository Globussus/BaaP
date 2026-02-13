#include <iostream>
#include <string>

void show_instructions(int task) {
    std::cout << "=========================Контекстное меню=========================" << std::endl;
    switch(task) {
        case 1:
            std::cout << "Задание 1. Вариант 9. Выполнил: Глобаж Станислав" << std::endl;
            std::cout << "Пользователю нужно ввести целое число" << std::endl;
            std::cout << "Программма переводит число в прямой код" << std::endl;
            break;
        case 2:
            std::cout << "Задание 2. Вариант 9. Выполнил: Глобаж Станислав" << std::endl;
            std::cout << "Пользователю нужно ввести два целых числа" << std::endl;
            std::cout << "Программа складывает эти числа в формате дополнительного кода" << std::endl;
            std::cout << "  Результат будет выведен в виде прямого кода" << std::endl;
            break;
        case 3:
            std::cout << "Задание 3. Выполнил: Глобаж Станислав" << std::endl;
            std::cout << "Пользователь вводит основание системы счисления и два числа" << std::endl;
            std::cout << "Программа переводит эти числа в заданную систему счисления и находит их сумму и разность" << std::endl;
            break;
        case 4:
            std::cout << "Задание 4. Выполнил: Глобаж Станислав" << std::endl;
            std::cout << "Пользователь вводит два числа (второе число обязано быть простым!)" << std::endl;
            std::cout << "Программа вычисляет, делится ли первое число на второе без остатка" << std::endl;
            break;
        case 5: 
            std::cout << "Задание 5. Выполнил: глобаж Станислав" << std::endl;
            std::cout << "Пользователь вводит номер бочки с ядом (от 1 до 240)" << std::endl;
            std::cout << "Программа за два хода вычисляет номер бочки с ядом" << std::endl;
            break;
    }
    std::cout << std::endl;
    std::cout << "Пользователю доступны следующие команды:" << std::endl;
	std::cout << "  0 — выход" << std::endl;
	std::cout << "  1 — запуск" << std::endl;
	std::cout << "  2 — выводит инструкцию по использованию программы\n" << std::endl;
    std::cout << "==================================================================" << std::endl;
}

int select_task() {
    std::string task;

    while (task != "1" && task != "2" && task != "3" && task != "4" && task != "5") {
        std::cout << "Введите номер задания: ";
        getline(std::cin, task);

        if (task != "1" && task != "2" && task != "3" && task != "4" && task != "5") {
            std::cout << "Ошибка ввода. Повторите попытку!" << std::endl;
        }
    }

    return std::stoi(task);
}

bool is_correct_number(std::string str) { //O(n)
    int size = str.size();

    if (size == 0) {
        return false;
    } else if (size == 1) {
        return (isdigit(str[0]));
    } else {
        bool flag = (isdigit(str[0]) || str[0] == '-');
        if (flag) {
            for (int i = 1; i < size; i++) {
                if (!isdigit(str[i])) {
                    flag = false;
                    break;
                }
            }
        }
        return flag;
    }
}

long long get_length_of_binary(long long number) { //O(log n)
    if (number == 0) return 1;
    
    unsigned long long abs_number = std::abs(number);
    long long bit_length = 0;
    
    while (abs_number > 0) {
        abs_number >>= 1;
        bit_length++;
    }
    
    return bit_length + 1;
}

void decimal_to_binary(unsigned short* array, long long number, const long long length) { //O(n)
    unsigned long long temp = std::abs(number);

    for (long long i = 0; i < length; i++) {
        array[length - i - 1] = (unsigned short)temp % 2;
        temp /= 2;
    }

    if (number < 0) {
        array[0] = 1;
    } else {
        array[0] = 0;
    }
}

void binary_to_twos(unsigned short* array, long long number, const long long length) { //O(n)
    if (number >= 0) {
        decimal_to_binary(array, number, length);
    } else {
        unsigned long long temp = std::abs(number);
        
        for (long long i = 0; i < length; i++) {
            array[length - i - 1] = (unsigned short)temp % 2;
            temp /= 2;
        }
        
        for (long long i = 0; i < length; i++) {
            array[i] = 1 - array[i];
        }
        
        for (long long i = length - 1; i >= 0; i--) {
            if (array[i] == 0) {
                array[i] = 1;
                break;
            }
            array[i] = 0;
        }
    }
}

void twos_add(unsigned short* first_array, unsigned short* second_array, unsigned short* result, const long long length) { //O(n)
    unsigned short carry = 0;

    for (long long i = length - 1; i >= 0; i--) {
        unsigned short first_bit = first_array[i];
        unsigned short second_bit = second_array[i];
        unsigned short sum = first_bit + second_bit + carry;
        
        result[i] = sum % 2;
        carry = sum / 2;
    }
}

void twos_to_binary(unsigned short* array, const long long length) { //O(n)
    if (array[0] == 1) {
        for (long long i = length - 1; i >= 0; i--) {
            if (array[i] == 1) {
                array[i] = 0;
                break;
            }
            array[i] = 1;
        }
        
        for (long long i = 1; i < length; i++) {
            array[i] = 1 - array[i];
        }
        
        array[0] = 1;
    }
}

long long get_length_of_number(long long number, unsigned int base) { //O(log n)
    if (number == 0) {
        return 1;
    } else if (base == 2) {
        return get_length_of_binary(number);
    }

    unsigned short counter = 0;
    long long temp = (number < 0) ? -number : number;

    while (temp > 0) {
        temp /= base;
        counter++;
    }
    return counter + 1;
}

long long char_to_long_long(char c) {
    long long digit = 0;

    if (c >= '0' && c <= '9') {
        digit = c - '0';
    } else {
        digit = c - 'A' + 10;
    }

    return digit;
}

char long_long_to_char(long long digit) {
    char c;

    if (digit >= 10) {
        c = 'A' + (digit - 10);
    } else {
        c = '0' + digit;
    }

    return c;
}

std::string decimal_to_base(long long number, const long long length, unsigned int base) { // O(n)
    std::string result(length, '0');
    
    if (number == 0) {
        return result; 
    }
    
    if (number > 0) {
        long long temp = number;
        for (long long i = length - 1; i >= 0 && temp > 0; i--) {
            unsigned short digit = temp % base;
            result[i] = long_long_to_char(digit);
            temp /= base;
        }
    } 
    else {
        unsigned long long max_value = 1;
        for (long long i = 0; i < length; i++) {
            max_value *= base;
        }
        
        unsigned long long temp = max_value + number;
        
        for (long long i = length - 1; i >= 0 && temp > 0; i--) {
            unsigned short digit = temp % base;
            result[i] = long_long_to_char(digit);
            temp /= base;
        }
    }
    
    return result;
}

long long base_to_decimal(std::string number, const long long length, unsigned int base) { // O(n)
    long long result = 0;
    long long power = 1;

    for (long long i = length - 1; i >= 0; i--) {
        char c = number[i];
        unsigned short digit = char_to_long_long(c);

        result += digit * power;
        power *= base;
    }
    
    unsigned short first_digit = char_to_long_long(number[0]);
    
    if (first_digit >= (base / 2)) {
        long long max_value = 1;
        for (long long i = 0; i < length; i++) {
            max_value *= base;
        }
        result -= max_value;
    }

    return result;
}

std::string base_addition(std::string first_string, std::string second_string, const long long length, unsigned int base) { //O(n)
    std::string result(length, '0');
    unsigned short carry = 0;

    for (long long i = length - 1; i >= 0; i--) {
        unsigned short first_digit = char_to_long_long(first_string[i]);
        unsigned short second_digit = char_to_long_long(second_string[i]);

        unsigned short sum = first_digit + second_digit + carry;
        unsigned short digit = sum % base;
        
        carry = sum / base;
        result[i] = long_long_to_char(digit);
    }

    return result;
}

bool chech_is_divisor(long long number, long long divisor) { //O(log n)
    long long special_number = (divisor + 1) >> 1;

    if (number < 0) {
        number = ~number + 1;
    }

    while (number > divisor) {
        if (bool(number & 1)) {
            number = special_number + (number >> 1);
        } else {
            number >>= 1;
        }
    }

    return number == divisor;
}

bool check_is_alive(unsigned short* array, long long barrel) { //O(n)
    unsigned short index = 0;

    while (array[index] != 0) {
        if (array[index] == barrel) {
            return false;
        }
        index++;
    }

    return true;
}

void clear_array(unsigned short* array) { //O(n)
    unsigned short index = 0;

    while (array[index] != 0) {
        array[index++] = 0;
    }
}

void calculate(int task) {
    switch(task) {
        case 1: { //O(log n + k)
            std::string str;

            std::cout << "Введите число: ";
            getline(std::cin, str);
        
            if (is_correct_number(str)) {
                std::cout << "Число в десятичной системе: " << std::endl;
                std::cout << str << std::endl;

                long long number = std::stoll(str);
                const long long length = get_length_of_binary(number);
                unsigned short* array = new unsigned short[length];
            
                decimal_to_binary(array, number, length);
                std::cout << "Число, записанное в прямом коде: ";
                for (int i = 0; i < length; i++) { 
                    std::cout << array[i] << "";
                }
                std::cout << std::endl;

                delete[] array;
            } else {
                std::cout << "Вы не ввели корректное число!" << std::endl;
            }
            break;
        }
        case 2: { //O(k + log n)
            std::string first_str, second_str;

            std::cout << "Введите первое число: ";
            getline(std::cin, first_str);
            std::cout << "Введите второе число: ";
            getline(std::cin, second_str);
        
            if (is_correct_number(first_str) && is_correct_number(second_str)) { 
                std::cout << "Первое число в десятичной системе: " << std::endl;
                std::cout << first_str << std::endl;

                std::cout << "Второе число в десятичной системе: " << std::endl;
                std::cout << second_str << std::endl;

                long long first_number = std::stoll(first_str), second_number = std::stoll(second_str);
                const long long first_length = get_length_of_binary(first_number);
                const long long second_length = get_length_of_binary(second_number); 
                const long long length = std::max(first_length, second_length) + 1;
                
                unsigned short* first_array = new unsigned short[length];
                unsigned short* second_array = new unsigned short[length];

                binary_to_twos(first_array, first_number, length);
                binary_to_twos(second_array, second_number, length);

                for (long long i = 0; i < length; i++) {
                    std::cout << first_array[i];
                }
                std::cout << " +" << std::endl;

                for (long long i = 0; i < length; i++) {
                    std::cout << second_array[i];
                }
                std::cout << std::endl;

                for(long long i = 0; i < length; i++) {
                    std::cout << "-";
                }
                std::cout << std::endl;

                unsigned short* result = new unsigned short[length];

                twos_add(first_array, second_array, result, length);
                
                for (long long i = 0; i < length; i++) {
                    std::cout << result[i];
                }
                std::cout << std::endl;

                twos_to_binary(result, length);
                std::cout << "Результат сложения чисел при переводе в прямой код: ";
                for (long long i = 0; i < length; i++) {
                    std::cout << result[i];
                }
                std::cout << std::endl;

                delete[] first_array;
                delete[] second_array;
                delete[] result;
            } else {
                std::cout << "Вы не ввели корректное число!" << std::endl;
            }
            break;
        }
        case 3: { //O(log n1 + log n2 + k)
            std::string str_base;
            std::cout << "Введите систему счисления (от 2 до 36): ";
            getline(std::cin, str_base);

            if (!is_correct_number(str_base) || std::stoi(str_base) < 2 || std::stoi(str_base) > 36) {
                std::cout << "Вы ввели некорректное основание системы счисления!" << std::endl;
                break;
            }

            unsigned int base = std::stoi(str_base);
            std::string first_string, second_string;

            std::cout << "Введите первое число: ";
            getline(std::cin, first_string);
            std::cout << "Введите второе число: ";
            getline(std::cin, second_string);

            if (is_correct_number(first_string) && is_correct_number(second_string)) {
                long long first_number = std::stoll(first_string), second_number = std::stoll(second_string);
                long long first_length = get_length_of_number(first_number, base);
                long long second_length = get_length_of_number(second_number, base);
                const long long length = std::max(first_length, second_length) + 1;

                std::string first_string = decimal_to_base(first_number, length, base);
                std::string second_string = decimal_to_base(second_number, length, base);
                std::string minus_second_string = decimal_to_base(-second_number, length, base);
                
                std::cout << "Первое число в системе счисления с основанием " << base << ": ";
                std::cout << first_string << std::endl;
                std::cout << "Второе число в системе счисления с основанием " << base << ": ";
                std::cout << second_string << std::endl << std::endl;

                std::string sum = base_addition(first_string, second_string, length, base);
                std::string sub = base_addition(first_string, minus_second_string, length, base);

                std::cout << first_string << "+" << std::endl;
                std::cout << second_string << std::endl;
                
                for (long long i = 0; i < length; i++) {
                    std::cout << "-";
                }
                std::cout << std::endl << sum << std::endl;
                std::cout << "Сумма в десятичной системе: " << base_to_decimal(sum, length, base) << std::endl << std::endl;

                std::cout << first_string << "-" << std::endl;
                std::cout << second_string << std::endl;
                
                for (long long i = 0; i < length; i++) {
                    std::cout << "-";
                }
                std::cout << std::endl << sub << std::endl;
                std::cout << "Разность в десятичной системе: " << base_to_decimal(sub, length, base) << std::endl;

            } else {
                std::cout << "Вы не ввели корректное число!" << std::endl;
            }
            break;
        }
        case 4: { //O(k + log n)
            std::string str_number, str_divisor;

            std::cout << "Введите число: ";
            getline(std::cin, str_number);
            std::cout << "Введите делитель: ";
            getline(std::cin, str_divisor);

            if (is_correct_number(str_number) && is_correct_number(str_divisor)) {
                long long number = std::stoll(str_number), divisor = std::stoll(str_divisor);

                if (chech_is_divisor(number, divisor)) {
                    std::cout << "Число " << number << " делится на " << divisor << " без остатка" << std::endl;
                } else {
                    std::cout << "Число " << number << " не делится на " << divisor << " без остатка" << std::endl;
                }
            }

            break;
        }
        case 5: { //O(k) если учитывать функцию проверки ввода. Иначе - O(1)
            std::string str_barrel;

            std::cout << "Введите номер бочки: ";
            getline(std::cin, str_barrel);

            if (is_correct_number(str_barrel)) {
                long long barrel = std::stoll(str_barrel);

                if (barrel <= 0 || barrel > 240) {
                    std::cout << "Номер бочки должен быть натуральным числом от 1 до 240" << std::endl;
                    break;
                }

                bool first_flag = true, second_flag = true, third_flag = true, fourth_flag = true, fifth_flag = true;
                unsigned short first_index = 0, second_index = 0, third_index = 0, fourth_index = 0, fifth_index = 0;
                std::string ternary_number = decimal_to_base(barrel, 6, 3);
                std::string result = "000000";

                unsigned short* first_barrels = new unsigned short[240] {};
                unsigned short* second_barrels = new unsigned short[240] {};
                unsigned short* third_barrels = new unsigned short[240] {};
                unsigned short* fourth_barrels = new unsigned short[240] {};
                unsigned short* fifth_barrels = new unsigned short[240] {};

                std::cout << "==================================================================" << std::endl;
                std::cout << "День первый:" << std::endl;

                for (unsigned short i = 1; i <= 240; i++) {
                    std::string guess = decimal_to_base(i, 6, 3);

                    if (guess[1] == '1') {
                        first_barrels[first_index++] = i;
                    }
                    if (guess[2] == '1') {
                        second_barrels[second_index++] = i;
                    }
                    if (guess[3] == '1') {
                        third_barrels[third_index++] = i;
                    }
                    if (guess[4] == '1') {
                        fourth_barrels[fourth_index++] = i;
                    }
                    if (guess[5] == '1') {
                        fifth_barrels[fifth_index++] = i;
                    } 
                }

                first_flag = check_is_alive(first_barrels, barrel);
                second_flag = check_is_alive(second_barrels, barrel);
                third_flag = check_is_alive(third_barrels, barrel);
                fourth_flag = check_is_alive(fourth_barrels, barrel);
                fifth_flag = check_is_alive(fifth_barrels, barrel);

                bool is_dead_first = false, is_dead_second = false, is_dead_third = false, is_dead_fourth = false, is_dead_fifth = false;

                if (first_flag && second_flag && third_flag && fourth_flag && fifth_flag) {
                    std::cout << "В первый день все выжили" << std::endl;
                }
                if (!first_flag) {
                    std::cout << "Первый раб погиб" << std::endl;
                    result[1] = '1';
                    is_dead_first = true;
                }
                if (!second_flag) {
                    std::cout << "Второй раб погиб" << std::endl;
                    result[2] = '1';
                    is_dead_second = true;
                }
                if (!third_flag) {
                    std::cout << "Третий раб погиб" << std::endl;
                    result[3] = '1';
                    is_dead_third = true;
                }
                if (!fourth_flag) {
                    std::cout << "Четвертый раб погиб" << std::endl;
                    result[4] = '1';
                    is_dead_fourth = true;
                }
                if (!fifth_flag) {
                    std::cout << "Пятый раб погиб" << std::endl;
                    result[5] = '1';
                    is_dead_fifth = true;
                }

                clear_array(first_barrels);
                clear_array(second_barrels);
                clear_array(third_barrels);
                clear_array(fourth_barrels);
                clear_array(fifth_barrels);

                first_index = second_index = third_index = fourth_index = fifth_index = 0;
                
                std::cout << std::endl << "День второй: " << std::endl;

                for (unsigned short i = 1; i <= 240; i++) {
                    std::string guess = decimal_to_base(i, 6, 3);

                    if (guess[1] == '2' && first_flag) {
                        first_barrels[first_index++] = i;
                    }
                    if (guess[2] == '2' && second_flag) {
                        second_barrels[second_index++] = i;
                    }
                    if (guess[3] == '2' && third_flag) {
                        third_barrels[third_index++] = i;
                    }
                    if (guess[4] == '2' && fourth_flag) {
                        fourth_barrels[fourth_index++] = i;
                    }
                    if (guess[5] == '2' && fifth_flag) {
                        fifth_barrels[fifth_index++] = i;
                    } 
                }

                if (!is_dead_first) {
                    first_flag = check_is_alive(first_barrels, barrel);
                }
                if (!is_dead_second) {
                    second_flag = check_is_alive(second_barrels, barrel);
                }
                if (!is_dead_third) {
                    third_flag = check_is_alive(third_barrels, barrel);
                }
                if (!is_dead_fourth) {
                    fourth_flag = check_is_alive(fourth_barrels, barrel);
                }
                if (!is_dead_fifth) {
                    fifth_flag = check_is_alive(fifth_barrels, barrel);
                }

                if (first_flag && second_flag && third_flag && fourth_flag && fifth_flag) {
                    std::cout << "Во второй день все выжили" << std::endl;
                }
                if (!first_flag && !is_dead_first) {
                    std::cout << "Первый раб погиб" << std::endl;
                    result[1] = '2';
                }
                if (!second_flag && !is_dead_second) {
                    std::cout << "Второй раб погиб" << std::endl;
                    result[2] = '2';
                }
                if (!third_flag && !is_dead_third) {
                    std::cout << "Третий раб погиб" << std::endl;
                    result[3] = '2';
                }
                if (!fourth_flag && !is_dead_fourth) {
                    std::cout << "Четвертый раб погиб" << std::endl;
                    result[4] = '2';
                }
                if (!fifth_flag && !is_dead_fifth) {
                    std::cout << "Пятый раб погиб" << std::endl;
                    result[5] = '2';
                }

                long long guess = base_to_decimal(result, 6, 3);
                std::cout << "Бочка с ядом это бочка под номером " << guess << std::endl;
                std::cout << "==================================================================" << std::endl;

                delete[] first_barrels;
                delete[] second_barrels;
                delete[] third_barrels;
                delete[] fourth_barrels;
                delete[] fifth_barrels;
            } else {
                std::cout << "Вы ввели некорректный номер бочки" << std::endl;
            }
            break;
        }
    }
};