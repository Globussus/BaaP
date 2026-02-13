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
    double** matrix = new double* [n] {};
  
    for (int i = 0; i < n; i++) {
      matrix[i] = new double[k] {};
    }
    srand(time(NULL));
    
    std::cout << "Элементы матрицы: " << std::endl;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < k; j++) {
        matrix[i][j] = static_cast<double>((rand() + 10) % 100) / 10;
        std::cout << matrix[i][j] << ' ';
      }
      std::cout << std::endl;
    }

    const int amount_of_zeroes = CountZeroes(matrix, n, k);
    if (!amount_of_zeroes) {
      std::cout << "В матрице нет нулей" << std::endl;
    } else {
      std::cout << "Кол-во нулей в матрице = " << amount_of_zeroes << "\nПозиции нулей в матрице: " << std::endl; 
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
          if (matrix[i][j] == 0) {
            std::cout << "(" << i << ", " << j << ") ";
          }
        }
      }
      std::cout << std::endl;
    }
    int i = 0;

    std::cout << "Матрица в обратном порядке: " << std::endl;
    ReverseMatrix(matrix, n, k);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < k; j++) {
        std::cout << matrix[i][j] << ' ';
      }
      std::cout << std::endl;
    }

    for (int i = 0; i < n; i++) {
      delete[] matrix[i];
    }
    delete[] matrix;
  }
}

int main() {
	std::string command;

	ShowInstructions(4);

	while(true) {
		std::cout << "Введите команду: ";
		std::cin >> command;

		if (command == "1") {
			Calculate();
		} else if (command == "0") {
			std::cout << "Завершение работы" << std::endl;
			break;
		} else if (command == "2") {
			ShowInstructions(4);
		} else {
			std::cout << "Программа не обрабатывает введенную команду" << std::endl;
		}
	}
}