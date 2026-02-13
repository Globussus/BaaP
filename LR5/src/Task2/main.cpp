#include <iostream>
#include "../../include/tools.h"

int Calculate() {
  int N; 

  std::cout << "Введите N: ";
  std::cin >> N;

  if (std::cin.fail()) {
    std::cout << "Ошибка ввода! Повторите попытку." << std::endl;
		CleanInput();
	} else if (static_cast<int>(N) != N || N < 1) {
		std::cout << "Число n должно быть натуральным!\nПовторите попытку." << std::endl;
	} else {
    double* array = new double[N];

    std::cout << "Произведение элементов вида (sin C_i - cos C_i) = ";
  }
}