#include <iostream>
#include <cstring>
#include <gtest/gtest.h>
#include "../include/tools.h"

TEST(Task1, test1) {
    const int length = 2;
    const int max_size = 80;
    char* string = new char[length];

    for (int i = 0; i < length  - 1; i++) {
        string[i] = ' ';
    }
    string[1] = '\0';

    ASSERT_EQ(true, is_string_of_digits(string));
    ASSERT_EQ(0, count_numbers(max_size, string));

    delete[] string;
}

TEST(Task1, test2) {
    const int length = 2;
    const int max_size = 80;
    char* string = new char[length];

    for (int i = 0; i < length - 1; i++) {
        string[i] = '1';
    }
    string[1] = '\0';

    ASSERT_EQ(true, is_string_of_digits(string));

    const int amount = count_numbers(max_size, string);
    ASSERT_EQ(1, amount);

    int* numbers = new int[1];
    divide_string(max_size, string, numbers);
    delete[] string;
    bubble_sort(numbers, amount);

    int* new_array = new int[1];
    for (int i = 0; i < 1; i++) {
        new_array[i] = 1;
    }
    ASSERT_EQ(true, are_equivalent_arrays(numbers, new_array, amount, 1));

    delete[] numbers;
    delete[] new_array;
}

TEST(Task1, test3) {
    const int length = 6;
    const int max_size = 80;
    char* string = new char[length];

    for (int i = 0; i < length - 1; i++) {
        string[i] = (i + 1) + '0';
    }
    string[5] = '\0';

    ASSERT_EQ(true, is_string_of_digits(string));

    const int amount = count_numbers(max_size, string);
    ASSERT_EQ(1, amount);

    int* numbers = new int[amount];
    divide_string(max_size, string, numbers);

    delete[] string;
    bubble_sort(numbers, amount);

    int* new_array = new int[amount];
    for (int i = 0; i < amount; i++) {
        new_array[i] = numbers[i];
    }
    ASSERT_EQ(true, are_equivalent_arrays(numbers, new_array, amount, amount));

    delete[] numbers;
    delete[] new_array;
}

TEST(Task1, test4) {
    const int length = 5;
    const int max_size = 80;
    char* string = new char[length];

    for (int i = 0; i < length - 1; i++) {
        if (i % 2 == 1) {
            string[i] = ' ';
        } else {
            string[i] = (i + 1) + '0';
        }
    }
    string[4] = '\0';

    ASSERT_EQ(true, is_string_of_digits(string));

    const int amount = count_numbers(max_size, string);
    ASSERT_EQ(2, amount);

    int* numbers = new int[amount];
    divide_string(max_size, string, numbers);

    delete[] string;
    bubble_sort(numbers, amount);

    int* new_array = new int[amount];
    for (int i = 0; i < amount; i++) {
        new_array[i] = 1 + 2 * i;
    }
    ASSERT_EQ(true, are_equivalent_arrays(numbers, new_array, amount, amount));

    delete[] numbers;
    delete[] new_array;
}

TEST(Task1, test5) {
    const int length = 8;
    const int max_size = 80;
    char* string = new char[length];

    for (int i = 0; i < length - 1; i++) {
        if (i == 3) {
            string[i] = ' ';
        } else {
            string[i] = 2 * 2 + '0';
        }
    }
    string[7] = '\0';

    ASSERT_EQ(true, is_string_of_digits(string));

    const int amount = count_numbers(max_size, string);
    ASSERT_EQ(2, amount);

    int* numbers = new int[amount];
    divide_string(max_size, string, numbers);

    delete[] string;
    bubble_sort(numbers, amount);

    int* new_array = new int[amount];
    for (int i = 0; i < amount; i++) {
        new_array[i] = 444; 
    }

    ASSERT_EQ(true, are_equivalent_arrays(numbers, new_array, amount, amount));

    delete[] numbers;
    delete[] new_array;
}

TEST(Task1, test6) {
    const int length = 4;
    const int max_size = 80;
    char* string = new char[length];

    for (int i = 0; i < length - 1; i++) {
        if (i % 2 == 1) {
            string[i] = ' ';
        } else {
            string[i] = 1 + '0';
        }
    }
    string[3] = '\0';

    ASSERT_EQ(true, is_string_of_digits(string));

    const int amount = count_numbers(max_size, string);
    ASSERT_EQ(2, amount);

    int* numbers = new int[amount];
    divide_string(max_size, string, numbers);

    delete[] string;
    bubble_sort(numbers, amount);

    int* new_array = new int[amount];
    for (int i = 0; i < amount; i++) {
        new_array[i] = 1; 
    }

    ASSERT_EQ(true, are_equivalent_arrays(numbers, new_array, amount, amount));

    delete[] numbers;
    delete[] new_array;
}

TEST(Task1, test7) {
    const int length = 5;
    const int max_size = 80;
    char* string = new char[length];

    for (int i = 0; i < length - 1; i++) {
        if (i % 4 == 3) {
            string[i] = ' ';
        } else {
            string[i] = 1 + '0';
        }
    }
    string[4] = '\0';

    ASSERT_EQ(true, is_string_of_digits(string));

    const int amount = count_numbers(max_size, string);
    ASSERT_EQ(1, amount);

    int* numbers = new int[amount];
    divide_string(max_size, string, numbers);

    delete[] string;
    bubble_sort(numbers, amount);

    int* new_array = new int[amount];
    for (int i = 0; i < amount; i++) {
        new_array[i] = 111; 
    }

    ASSERT_EQ(true, are_equivalent_arrays(numbers, new_array, amount, amount));

    delete[] numbers;
    delete[] new_array;
}

TEST(Task1, test8) {
    const int length = 10;
    const int max_size = 80;
    char* string = new char[length];

    for (int i = 0; i < length - 1; i++) {
        if ((i + 1) % 3 == 0) {
            string[i] = ' ';
        } else {
            string[i] = 2 + '0';
        }
    }
    string[9] = '\0';

    ASSERT_EQ(true, is_string_of_digits(string));

    const int amount = count_numbers(max_size, string);
    ASSERT_EQ(3, amount);

    int* numbers = new int[amount];
    divide_string(max_size, string, numbers);

    delete[] string;
    bubble_sort(numbers, amount);

    int* new_array = new int[amount];
    for (int i = 0; i < amount; i++) {
        new_array[i] = 22; 
    }

    ASSERT_EQ(true, are_equivalent_arrays(numbers, new_array, amount, amount));

    delete[] numbers;
    delete[] new_array;
}

TEST(Task1, test9) {
    const int length = 8;
    const int max_size = 80;
    char* string = new char[length];

    for (int i = 0; i < length - 1; i++) {
        if (i % 2 == 1) {
            string[i] = ' ';
        } else {
            string[i] = 9 + '0';
        }
    }
    string[7] = '\0';

    ASSERT_EQ(true, is_string_of_digits(string));

    const int amount = count_numbers(max_size, string);
    ASSERT_EQ(4, amount);

    int* numbers = new int[amount];
    divide_string(max_size, string, numbers);

    delete[] string;
    bubble_sort(numbers, amount);

    int* new_array = new int[amount];
    for (int i = 0; i < amount; i++) {
        new_array[i] = 9; 
    }

    ASSERT_EQ(true, are_equivalent_arrays(numbers, new_array, amount, amount));

    delete[] numbers;
    delete[] new_array;
}

TEST(Task1, test10) {
    const int length = 6;
    const int max_size = 80;
    char* string = new char[length];

    for (int i = 0; i < length - 1; i++) {
        if (i == 4) {
            string[i] = ' ';
        } else {
            string[i] = 6 + '0';
        }
    }
    string[5] = '\0';

    ASSERT_EQ(true, is_string_of_digits(string));

    const int amount = count_numbers(max_size, string);
    ASSERT_EQ(1, amount);

    int* numbers = new int[amount];
    divide_string(max_size, string, numbers);

    delete[] string;
    bubble_sort(numbers, amount);

    int* new_array = new int[amount];
    for (int i = 0; i < amount; i++) {
        new_array[i] = 6666; 
    }

    ASSERT_EQ(true, are_equivalent_arrays(numbers, new_array, amount, amount));

    delete[] numbers;
    delete[] new_array;
}

TEST(Task2, test1) {
    const int size = 2;
    char* string = new char[size];

    string[0] = ' ';
    string[1] = '\0';

    int amount_of_vowels = count_vowels(string);
    ASSERT_EQ(0, amount_of_vowels);
    int amount_of_consonants = count_consonants(string);
    ASSERT_EQ(0, amount_of_consonants);

    delete[] string;
}

TEST(Task2, test2) {
    const int size = 2;
    char* string = new char[size];

    string[0] = 'a';
    string[1] = '\0';
    
    int amount_of_vowels = count_vowels(string);
    ASSERT_EQ(1, amount_of_vowels);
    int amount_of_consonants = count_consonants(string);
    ASSERT_EQ(0, amount_of_consonants);

    delete[] string;
}

TEST(Task2, test3) {
    const int size = 5;
    char* string = new char[size];

    for (int i = 0; i < size; i++) {
        if (i % 2 == 0) {
            string[i] = 'a';
        } else {
            string[i] = 'b';
        }
    }

    string[4] = '\0';
    
    int amount_of_vowels = count_vowels(string);
    ASSERT_EQ(2, amount_of_vowels);
    int amount_of_consonants = count_consonants(string);
    ASSERT_EQ(2, amount_of_consonants);

    delete[] string;
}

TEST(Task2, test4) {
    const int size = 5;
    char* string = new char[size];

    for (int i = 0; i < size; i++) {
        if (i % 2 == 0) {
            string[i] = 'a';
        } else {
            string[i] = 'b';
        }
    }

    string[4] = '\0';
    
    int amount_of_vowels = count_vowels(string);
    ASSERT_EQ(2, amount_of_vowels);
    int amount_of_consonants = count_consonants(string);
    ASSERT_EQ(2, amount_of_consonants);

    delete[] string;
}

TEST(Task2, test5) {
    const int size = 8;
    char* string = new char[size];

    for (int i = 0; i < size; i++) {
        if (i % 3 == 0) {
            string[i] = 'a';
        } else {
            string[i] = 'b';
        }
    }

    string[7] = '\0';
    
    int amount_of_vowels = count_vowels(string);
    ASSERT_EQ(3, amount_of_vowels);
    int amount_of_consonants = count_consonants(string);
    ASSERT_EQ(4, amount_of_consonants);

    delete[] string;
}

TEST(Task2, test6) {
    const int size = 6;
    char* string = new char[size];

    for (int i = 0; i < size; i++) {
        string[i] = 'z';
    }

    string[5] = '\0';
    
    int amount_of_vowels = count_vowels(string);
    ASSERT_EQ(0, amount_of_vowels);
    int amount_of_consonants = count_consonants(string);
    ASSERT_EQ(5, amount_of_consonants);

    delete[] string;
}

TEST(Task2, test7) {
    const int size = 10;
    char* string = new char[size];

    for (int i = 0; i < size; i++) {
        string[i] = 'a';
    }

    string[9] = '\0';
    
    int amount_of_vowels = count_vowels(string);
    ASSERT_EQ(9, amount_of_vowels);
    int amount_of_consonants = count_consonants(string);
    ASSERT_EQ(0, amount_of_consonants);

    delete[] string;
}

TEST(Task2, test8) {
    const int size = 7;
    char* string = new char[size];

    for (int i = 0; i < size; i++) {
        string[i] = 'a';
    }

    string[6] = '\0';
    
    int amount_of_vowels = count_vowels(string);
    ASSERT_EQ(6, amount_of_vowels);
    int amount_of_consonants = count_consonants(string);
    ASSERT_EQ(0, amount_of_consonants);

    delete[] string;
}

TEST(Task2, test9) {
    const int size = 6;
    char* string = new char[size];

    for (int i = 0; i < size; i++) {
        if (i == 2 || i == 4) {
            string[i] = 'u';
        } else if (i == 1 || i == 3) {
            string[i] = 'b';
        }
    }

    string[5] = '\0';
    
    int amount_of_vowels = count_vowels(string);
    ASSERT_EQ(2, amount_of_vowels);
    int amount_of_consonants = count_consonants(string);
    ASSERT_EQ(2, amount_of_consonants);

    delete[] string;
}

TEST(Task2, test10) {
    const int size = 10;
    char* string = new char[size];

    for (int i = 0; i < size; i++) {
        if (i == 5 || i == 6) {
            string[i] = 'o';
        } else {
            string[i] = 'v';
        }
    }
    string[9] = '\0';
    
    int amount_of_vowels = count_vowels(string);
    ASSERT_EQ(2, amount_of_vowels);
    int amount_of_consonants = count_consonants(string);
    ASSERT_EQ(7, amount_of_consonants);

    delete[] string;
}

TEST(Task3, test1) {
    const int max_size = 128;
    char** string_array = new char* [1] {nullptr};
    int real_string_count = 0;
    
    for (int i = 0; i < 1; i++) {
        string_array[i] = new char [max_size] {};
        string_array[i][0] = 'a';
        string_array[i][1] = '\0';
        if (is_empty_string(string_array[i])) {
            delete[] string_array[i];
            string_array[i] = nullptr;
            break;
        }
        real_string_count++;
    }

    ASSERT_EQ(true, check_is_palindrome(string_array[0], 1));
    ASSERT_EQ(0, count_spaces(string_array[0], 1));

    for (int i = 0; i < 1; i++) {
        if (string_array[i] != nullptr) {
            delete[] string_array[i];
        }
    }
    delete[] string_array;
}

TEST(Task3, test2) {
    const int strings_amount = 3;
    const int max_size = 128;
    char** string_array = new char* [strings_amount] {nullptr};
    
    for (int i = 0; i < strings_amount; i++) {
        string_array[i] = new char [max_size] {};
        for (int j = 0; j < 10; j++) {
            string_array[i][j] = 'b';
        }
        string_array[i][10] = '\0';
        ASSERT_EQ(true, check_is_palindrome(string_array[i], get_length_of_string(string_array[i])));
        ASSERT_EQ(0, count_spaces(string_array[i], get_length_of_string(string_array[i])));
    }

    for (int i = 0; i < strings_amount; i++) {
        if (string_array[i] != nullptr) {
            delete[] string_array[i];
        }
    }
    delete[] string_array;
}

TEST(Task3, test3) {
    const int strings_amount = 5;
    const int max_size = 128;
    char** string_array = new char* [strings_amount] {nullptr};
    
    for (int i = 0; i < strings_amount; i++) {
        string_array[i] = new char [max_size] {};
        for (int j = 0; j < 20; j++) {
            if (j == 0 || j == 19) {
                string_array[i][j] = 'a';
            } else {
                string_array[i][j] = 'b';
            }
        }
        string_array[i][20] = '\0';
        ASSERT_EQ(true, check_is_palindrome(string_array[i], get_length_of_string(string_array[i])));
        ASSERT_EQ(0, count_spaces(string_array[i], get_length_of_string(string_array[i])));
    }

    for (int i = 0; i < strings_amount; i++) {
        if (string_array[i] != nullptr) {
            delete[] string_array[i];
        }
    }
    delete[] string_array;
}

TEST(Task3, test4) {
    const int strings_amount = 4;
    const int max_size = 128;
    char** string_array = new char* [strings_amount] {nullptr};
    
    for (int i = 0; i < strings_amount; i++) {
        string_array[i] = new char [max_size] {};
        for (int j = 0; j < 16; j++) {
            if (j % 2 == 1) {
                string_array[i][j] = 'a';
            } else {
                string_array[i][j] = 'b';
            }
        }
        string_array[i][16] = '\0';
        ASSERT_EQ(false, check_is_palindrome(string_array[i], get_length_of_string(string_array[i])));
        ASSERT_EQ(0, count_spaces(string_array[i], get_length_of_string(string_array[i])));
    }

    for (int i = 0; i < strings_amount; i++) {
        if (string_array[i] != nullptr) {
            delete[] string_array[i];
        }
    }
    delete[] string_array;
}

TEST(Task3, test5) {
    const int strings_amount = 12;
    const int max_size = 128;
    char** string_array = new char* [strings_amount] {nullptr};
    
    for (int i = 0; i < strings_amount; i++) {
        string_array[i] = new char [max_size] {};
        for (int j = 0; j < 19; j++) {
            if (j == 3 || j == 10) {
                string_array[i][j] = 'x';
            } else if (j == 5 || j == 6) {
                string_array[i][j] = ' ';
            } else {
                string_array[i][j] = 'y';
            }
        }
        string_array[i][19] = '\0';
        ASSERT_EQ(false, check_is_palindrome(string_array[i], get_length_of_string(string_array[i])));
        ASSERT_EQ(2, count_spaces(string_array[i], get_length_of_string(string_array[i])));
    }

    for (int i = 0; i < strings_amount; i++) {
        if (string_array[i] != nullptr) {
            delete[] string_array[i];
        }
    }
    delete[] string_array;
}

TEST(Task3, test6) {
    const int strings_amount = 8;
    const int max_size = 128;
    char** string_array = new char* [strings_amount] {nullptr};
    
    for (int i = 0; i < strings_amount; i++) {
        string_array[i] = new char [max_size] {};
        for (int j = 0; j < 10; j++) {
            if (j == 0 || j == 6 || j == 9) {
                string_array[i][j] = ' ';
            } else {
                string_array[i][j] = 'p';
            }
        }
        string_array[i][10] = '\0';
        ASSERT_EQ(false, check_is_palindrome(string_array[i], get_length_of_string(string_array[i])));
        ASSERT_EQ(3, count_spaces(string_array[i], get_length_of_string(string_array[i])));
    }

    for (int i = 0; i < strings_amount; i++) {
        if (string_array[i] != nullptr) {
            delete[] string_array[i];
        }
    }
    delete[] string_array;
}

TEST(Task3, test7) {
    const int strings_amount = 13;
    const int max_size = 128;
    char** string_array = new char* [strings_amount] {nullptr};
    
    for (int i = 0; i < strings_amount; i++) {
        string_array[i] = new char [max_size] {};
        for (int j = 0; j < 15; j++) {
            if (j == 0 || j == 14) {
                string_array[i][j] = ' ';
            } else {
                string_array[i][j] = 'a';
            }
        }
        string_array[i][15] = '\0';
        ASSERT_EQ(true, check_is_palindrome(string_array[i], get_length_of_string(string_array[i])));
        ASSERT_EQ(2, count_spaces(string_array[i], get_length_of_string(string_array[i])));
    }

    for (int i = 0; i < strings_amount; i++) {
        if (string_array[i] != nullptr) {
            delete[] string_array[i];
        }
    }
    delete[] string_array;
}

TEST(Task3, test8) {
    const int strings_amount = 6;
    const int max_size = 128;
    char** string_array = new char* [strings_amount] {nullptr};
    
    for (int i = 0; i < strings_amount; i++) {
        string_array[i] = new char [max_size] {};
        for (int j = 0; j < 25; j++) {
            if (j + i == 5) {
                string_array[i][j] = ' ';
            } else {
                string_array[i][j] = 'h';
            }
        }
        string_array[i][20] = '\0';
        ASSERT_EQ(false, check_is_palindrome(string_array[i], get_length_of_string(string_array[i])));
        ASSERT_EQ(1, count_spaces(string_array[i], get_length_of_string(string_array[i])));
    }

    for (int i = 0; i < strings_amount; i++) {
        if (string_array[i] != nullptr) {
            delete[] string_array[i];
        }
    }
    delete[] string_array;
}

TEST(Task3, test9) {
    const int strings_amount = 10;
    const int max_size = 128;
    char** string_array = new char* [strings_amount] {nullptr};
    
    for (int i = 0; i < strings_amount; i++) {
        string_array[i] = new char [max_size] {};
        for (int j = 0; j < 22; j++) {
            if (j == 0 || j == 14 || j == 19) {
                string_array[i][j] = 'i';
            } else {
                string_array[i][j] = 'v';
            }
        }
        string_array[i][22] = '\0';
        ASSERT_EQ(false, check_is_palindrome(string_array[i], get_length_of_string(string_array[i])));
        ASSERT_EQ(0, count_spaces(string_array[i], get_length_of_string(string_array[i])));
    }

    for (int i = 0; i < strings_amount; i++) {
        if (string_array[i] != nullptr) {
            delete[] string_array[i];
        }
    }
    delete[] string_array;
}

TEST(Task3, test10) {
    const int strings_amount = 9;
    const int max_size = 128;
    char** string_array = new char* [strings_amount] {nullptr};
    
    for (int i = 0; i < strings_amount; i++) {
        string_array[i] = new char [max_size] {};
        for (int j = 0; j < 26; j++) {
            if (j == 6 || j == 18 || j == 20) {
                string_array[i][j] = 'u';
            } else {
                string_array[i][j] = 'm';
            }
        }
        string_array[i][26] = '\0';
        ASSERT_EQ(false, check_is_palindrome(string_array[i], get_length_of_string(string_array[i])));
        ASSERT_EQ(0, count_spaces(string_array[i], get_length_of_string(string_array[i])));
    }

    for (int i = 0; i < strings_amount; i++) {
        if (string_array[i] != nullptr) {
            delete[] string_array[i];
        }
    }
    delete[] string_array;
}