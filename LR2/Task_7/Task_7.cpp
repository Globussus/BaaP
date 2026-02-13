#include <iostream>

int main() {
    int n;
    double a, b, c, y;

    std::cout << "Введите n: ";
    std::cin >> n;
    std::cout << "Введите a, b, c: ";
    std::cin >> a >> b >> c;

    switch (n) {
        case 2: 
        {
            y = b * c - a * a * a;
            std::cout << "Y = " << y;
            break; 
        }
        case 56:
        {
            y = b * c;
            std::cout << "Y = " << y;
            break;
        }
        case 7:
        {
            y = a * a + c;
            std::cout << "Y = " << y;
            break;
        }
        case 3:
        {
            y = a - b * c;
            std::cout << "Y = " << y;
            break;
        }
        default:
        {
            y = (a + b) * (a + b) * (a + b);
            std::cout << "Y = " << y;
            break;
        }            
    }
}