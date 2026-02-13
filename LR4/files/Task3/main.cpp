#include <iostream>
#include "../../modules/functions.h"
#include <cmath>
#include <string>

void Calculate() {
  int N;

  std::cout << "Введите N: ";
  std::cin >> N;

  if (std::cin.fail()) {
    std::cout << "N - должно быть числом!" << std::endl;
    CleanInput();
  } else if ((int) N != N || N < 1) {
    std::cout << "N - должно быть натуральным числом!" << std::endl;
  } else {
    int** matrix = new int*[N];

    srand(time(NULL));
    std::cout << "Матрица: " << std::endl;

    for (int i = 0; i < N; i++) {
      matrix[i] = new int[N]{};

      for (int j = 0; j < N; j++) {
        matrix[i][j] = (rand() % 90) + 10;
        std::cout << matrix[i][j] << ' ';
      }
      std::cout << '\n';
    }
    bool result =  IsMagicalSquare(matrix, N);

    if (result) {
      std::cout << "Введенная матрица является магическим квадратом." << std::endl;
    } else {
      std::cout << " Матрица не является магическим квадратом." << std::endl;
    }

    for (int i = 0; i < N; i++) {
      delete[] matrix[i];
    }
    delete[] matrix;
  }
}

int main() {
  std::string command;

  ShowInstructions(3);

  while (true) {
    std::cout << "Введите команду: ";
    std::cin >> command;

    if (command == "1") {
      Calculate();
    } else if (command == "0") {
      std::cout << "Завершение работы" << std::endl;
      break;
    } else if (command == "2") {
      ShowInstructions(3);
    } else {
      std::cout << "Программа не обрабатывает введённую команду." << std::endl;
    }
  }
  return 0;
}