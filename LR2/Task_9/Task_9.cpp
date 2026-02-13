#include <iostream>
#include <cmath>

int main() {
    int flag = 1;
    double a, b, z, x, f, y;

    std::cout << "Введите a, b, z: ";
    std::cin >> a >> b >> z;

    if (z <= 0) {
        x = pow(z, 2) / 2;
    }
    else {
        x = log(pow(z, 2) - z);
    }

    std::cout << "Введите значение flag:\n\tПри flag = 1: f(x) = 2x\n\tПри flag = 2: f(x) = x ^ 3\n\tПри flag = 3: f(x) = x / 3\n";
    std::cout << "flag = ";
    std::cin >> flag;

    switch(flag) {
        case 1: {
            f = 2 * x;
            break;
        }
        case 2: {
            f = pow(x, 3);
            break;
        }
        case 3: {
            f = x / 3;
            break;
        }
    }

    y = b * f / cos(x) + a * log(fabs(tan(x / 2)));
    std::cout << "y = " << y;

    return 0;
}