#include "tools.h"

std::string decimalToBinary(double number) {
    int integerPart = (int)number;
    double fractionPart = number - integerPart;
    std::string integerBinary = integerToBinary(integerPart);
    std::string fractionBinary = fractionToBinary(fractionPart, 10);
    std::string result = (number < 0 ? "-" : "") + 
        (integerBinary.empty() && !fractionBinary.empty() ? "0" : integerBinary) +
        (fractionBinary.empty() ? "" : "." + fractionBinary);
    return result;
}

std::string integerToBinary(int number) {
    if (number == 0) {
        return "";
    } else {
        return integerToBinary(number / 2) + std::to_string(number % 2);
    }
}

std::string fractionToBinary(double number, int signAmount) {
    if (number - (int)number == 0 || signAmount == 0) {
        return std::to_string((int)(number * 2));
    } else {
        return std::to_string((int)(number * 2)) + fractionToBinary((number * 2) - (int)(number * 2), signAmount - 1);
    }
}

int ackermannsFunction(unsigned int m, unsigned int n, int iterationsAmount) {
    if (m == 0 || iterationsAmount == 0) {
        return n + 1;
    } else if (m > 0 && n == 0) {
        return ackermannsFunction(m - 1, 1, iterationsAmount - 1);
    } else if (m > 0 && n > 0) {
        return ackermannsFunction(m - 1, ackermannsFunction(m, n - 1, iterationsAmount - 1), iterationsAmount - 1);
    }
    return 0;
}

int reverse(int number, int iter) {
    if (number == 0) {
        return iter;
    } else {
        return reverse(number / 10, iter * 10 + number % 10);
    }
}

void hanoi(int n, int i, int k) {
    if (n == 1) {
        std::cout << "Перекладываем диск 1 с " << i << "-го стержня на " << k << "-й" << std::endl; 
    } else {
        int tmp = 6 - i - k;
        hanoi(n - 1, i, tmp);
        std::cout << "Перекладываем диск " << n << " с " << i << "-го стержня на " << k << "-й" << std::endl; 
        hanoi(n - 1, tmp, k);
    }
}