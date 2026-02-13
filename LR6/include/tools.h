#pragma once

#include <iostream>
#include <cstdio>
#include "tools.cpp"

void show_instructions(int task);

bool is_empty_string(char* string);

void select_task(int task);

void input(const int max_size, char* string);

void clean_input();

bool is_string_of_digits(char* string);

void divide_string(const int max_size, char* string, int* numbers);

int count_numbers(const int max_size, char* string);

void bubble_sort(int* numbers, int length);

bool is_in_string(char* string, char element, int size);

int count_vowels(char* string);

int count_consonants(char* string);

bool check_is_palindrome(char* string, int length);

void print_reversed_string(char* string, int length);

int get_length_of_string(char* string);

int count_spaces(char* string, int length);

char to_lower(char element);

void calculate(int task);

bool are_equivalent_arrays(int* numbers, int* another, int first_size, int second_size);