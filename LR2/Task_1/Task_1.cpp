#include <iostream>

int main() {
    double x, var_1, var_2, var_3;

    std::cout << "Введите число: ";
    std::cin >> x;

    var_1 = x * x;
    var_2 = 69 * var_1 + 8;
    var_3 = x * (23 * var_1 + 32);

    std::cout << "Результат первой операции: " << var_2 + var_3 << std::endl;
    std::cout << "Результат второй операции: " << var_2 - var_3 << std::endl;

    return 0;
}