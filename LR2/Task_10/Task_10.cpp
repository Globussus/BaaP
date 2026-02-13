#include <iostream>

double sqrt(double number) {
    double result = 1;
    const double err = 1e-10;

    while (abs(result * result - number) > err) {
        result = (result + number / result) / 2;
    }

    return result;
}

double abs(double number) {
    if (number < 0) {
        number = number * (-1);
    }

    return number;
}

int main() {
    double x1, y1, x2, y2, r, R, d;
    
    std::cout << "Введите координаты x1, y1, x2, y2: ";
    std::cin >> x1 >> y1 >> x2 >> y2;
    std::cout << "Введите радиусы r и R: ";
    std::cin >> r >> R;

    d = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

    if (R - r > d) {
        std::cout << "Да";
    }
    else if (R - r == d && !d) {
        std::cout << "Да, но справедливо обратное для двух фигур";
    }
    else if (r + R >= d) {
        std::cout << "Фигуры пересекаются";
    }
    else {
        std::cout << "Ни одно условие не выполнено";
    }

    return 0;
}