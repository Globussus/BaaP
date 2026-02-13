#include <iostream>

int main() {
    int n = 9;
    double b1, q = 1.0 / (n + 1);

    std::cout << "Введите первый член геометрической прогресии: ";
    std::cin >> b1;
    std::cout << "Сумма членов бесконечно убывающей прогресии равна: " << b1 / (1 - q) << std::endl;

    return 0;
}