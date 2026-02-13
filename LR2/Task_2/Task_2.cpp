#include <iostream>

int main() {
    double a, b, c;

    std::cout << "Введите сторону a: ";
    std::cin >> a;
    std::cout << "Введите сторону b: ";
    std::cin >> b;
    std::cout << "Введите сторону c: ";
    std::cin >> c;

    if (a + b > c && a + c > b && b + c > a) {
        std::cout << "Такой треугольник существует" << std::endl;
    } 
    else {
        std::cout << "Треугольник с такими сторонами не существует";
    }

    return 0;
}