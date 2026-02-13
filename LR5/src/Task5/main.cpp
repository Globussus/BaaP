#include <iostream>
#include "../../include/tools.h"

void Calculate() {
  int n, k;
  
  std::cout << "Введите n и k: ";
  std::cin >> n >> k;

  if (std::cin.fail()) {
    std::cout << "Ошибка ввода! Повторите попытку." << std::endl;
		CleanInput();
  } else if (static_cast<int>(n) != n || n < 1 || static_cast<int>(k) != k || k < 1) {
    std::cout << "Числа n и k должны быть натуральными!\nПовторите попытку." << std::endl;
  } else {
    int** matrix = new int*[n];

    for (int i = 0; i < n; i++) {
      matrix[i] = new int[k];
    }
    srand(time(NULL));

    std::cout << "Элементы матрицы: " <<  std::endl;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < k; j++) {
        matrix[i][j] = rand() % 50 + 10;
        std::cout << matrix[i][j] << ' ';
      }
      std::cout << std::endl;
    }

    const int amount_of_non_even = CountNonEvenElementsFromEvenColumns(matrix, n, k);
    int* array = new int[amount_of_non_even];
    CreateArrayOfNonEven(matrix, array, n, k);

    double arithmetic_mean = CountArithmeticMean(array, amount_of_non_even);
    std::cout << "Среднее арифметическое нечетных элементов чётных столбцов матрицы = " << arithmetic_mean << std::endl;

    for (int i = 0; i < n; i++) {
      delete[] matrix[i];
    }
    delete[] matrix;
  }
}

int main() {
	std::string command;

	ShowInstructions(5);

	while(true) {
		std::cout << "Введите команду: ";
		std::cin >> command;

		if (command == "1") {
			Calculate();
		} else if (command == "0") {
			std::cout << "Завершение работы" << std::endl;
			break;
		} else if (command == "2") {
			ShowInstructions(5);
		} else {
			std::cout << "Программа не обрабатывает введенную команду" << std::endl;
		}
	}
}