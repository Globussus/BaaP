#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <string>
#include <cmath>
#include <format>

std::string decimalToBinary(double number);
std::string integerToBinary(int number);
std::string fractionToBinary(double number, int signAmount);

int ackermannsFunction(unsigned int m, unsigned int n, int iterationsAmount);
int reverse(int number, int iter);
void hanoi(int n, int i, int k);

#endif