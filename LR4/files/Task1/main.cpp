#include <iostream>
#include "../../modules/functions.h"
#include <cmath>
#include <string>

void Calculate() {
  const int length = 10;
  int array[length];

  std::cout << "Элементы исходного массива:" << std::endl;
  srand(time(NULL));

  for (int i = 0; i < length; i++) {
    array[i] =  pow(-1, rand() % 2) * (rand() % 100);
    std::cout << array[i] << " ";
  }

  const int amount_of_neg = CountNegativeNumbers(array, length);
  int *negative_numbers = MakeArrayOfNegative(array, length);
  int *non_negative_numbers = MakeArrayOfNonNegative(array, length);

  std::cout << "\nЭлементы массива с отрицательными числами:" << std::endl;
  for (int i = 0; i < amount_of_neg; i++) {
    std::cout << negative_numbers[i] << " ";
  }

  std::cout << "\nЭлементы массива с неотрицательными числами:" << std::endl;
  for (int i = 0; i < length - amount_of_neg; i++) {
    std::cout << non_negative_numbers[i] << " ";
  }
  std::cout << "\n\n";

  delete[] negative_numbers;
  delete[] non_negative_numbers;
}

int main() {
  std::string command;

  ShowInstructions(1);

  while (true) {
    std::cout << "Введите команду: ";
    std::cin >> command;

    if (command == "1") {
      Calculate();
    } else if (command == "0") {
      std::cout << "Завершение работы" << std::endl;
      break;
    } else if (command == "2") {
      ShowInstructions(1);
    } else {
      std::cout << "Программа не обрабатывает введённую команду." << std::endl;
    }
  }
  return 0;
}