#pragma once

#include <iostream>
#include "tools.cpp"

void show_instructions(int task);

int select_task();

bool is_correct_number(std::string str);

long long get_length_of_binary(long long number);

void decimal_to_binary(long long* array, long long number, const long long length);

void binary_to_twos(unsigned short* array, long long number, const long long length);

void twos_add(unsigned short* first_array, unsigned short* second_array, unsigned short* result, const long long length);

void twos_to_binary(unsigned short* array, const long long length);

long long get_length_of_number(long long number, unsigned short base);

long long char_to_long_long(char c);

char long_long_to_char(long long digit);

std::string decimal_to_base(long long number, const long long length, unsigned int base);

long long base_to_decimal(std::string number, const long long length, unsigned int base);

std::string base_addition(std::string first_string, std::string second_string, unsigned int base);

bool chech_is_divisor(long long number, long long divisor);

bool check_is_alive(unsigned short* array, long long barrel);

void calculate(int task);