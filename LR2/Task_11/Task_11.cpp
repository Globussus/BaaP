#include <iostream>

int main() {
    int h1, m1, h2, m2, timedelta;

    std::cout << "Введите h1, m1, h2, m2: ";
    std::cin >> h1 >> m1 >> h2 >> m2;
    
    if (h2 < h1) {
        h2 += 24;
    }

    timedelta = (h2 - h1) * 60 + (m2 - m1);
    std::cout << "Время выполнения дз равно: " << timedelta / 60 << " часов " << timedelta % 60 << " минут.";

    return 0;
}