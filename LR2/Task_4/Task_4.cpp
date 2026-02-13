#include <iostream>

int main() {
    int x, y;
    double a, b, c, k;

    
    if (x > y) {
        y = 0; 
    }
    else if (y > x) {
        x = 0;
    }
    else {
        x = 0;
        y = 0;
    }

    if (a >= b && a >= c) {
        a -= k; 
    }
    else if (b >= a && b >= c) {
        b -= k;
    }
    else if (c >= a && c >= b) {
        c -= k;
    }

    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;

    return 0;
}