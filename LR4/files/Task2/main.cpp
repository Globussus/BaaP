#include <iostream>
#include "../../modules/functions.h"
#include <cmath>
#include <string>

void Calculate() {
  int m = 4, index = 0;
  int array[m * m];

  srand(time(NULL));
  std::cout << "Матрица:" << std::endl;

  for (int i = 0; i < m ; i++) {
    for (int j = 0; j < m; j++) {
      array[index] = (rand() % 90) + 10;
      std::cout << array[index] << " ";
      index++;
    }
    std::cout << '\n';
  }

  int maximum = FindMaxElementOfMatrix(array, m);
  std::cout << "Максимальный элемент, лежащий выше побочной диагонали: " << maximum << std::endl;
}

int main() {
  std::string command;

  ShowInstructions(2);

  while (true) {
    std::cout << "Введите команду: ";
    std::cin >> command;

    if (command == "1") {
      Calculate();
    } else if (command == "0") {
      std::cout << "Завершение работы" << std::endl;
      break;
    } else if (command == "2") {
      ShowInstructions(2);
    } else {
      std::cout << "Программа не обрабатывает введённую команду." << std::endl;
    }
  }
  return 0;
}
