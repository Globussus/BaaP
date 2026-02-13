#include <iostream>
#include "matrix_functions.h"
#include "../../include/tools.h"

void Calculate() {
	int n, string_sum_of_first = 0, row_sum_of_first = 0, string_sum_of_second = 0, row_sum_of_second = 0;

	std::cout << "Введите n: ";
	std::cin >> n;

	if (std::cin.fail()) {
		std::cout << "Ошибка ввода! Повторите попытку." << std::endl;
		CleanInput();
	} else if (static_cast<int>(n) != n || n < 1) {
		std::cout << "Число n должно быть натуральным!\nПовторите попытку." << std::endl;
	} else {
		int** matrix = new int* [n] {};
		int** transposed_matrix = new int* [n] {};

		for (int i = 0; i < n; i++) {
			matrix[i] = new int[n] {};
			transposed_matrix[i] = new int[n] {};
		}

		TranspositionOfMatrix(matrix, transposed_matrix, n);
		
		int* first_sum = &string_sum_of_first;
		int* second_sum = &row_sum_of_first;
		int* third_sum = &string_sum_of_second;
		int* fourth_sum = &row_sum_of_second;

		std::cout << "Элементы исходной матрицы: " << std::endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				std::cout << matrix[i][j] << ' ';
			}
			std::cout << std::endl;
		}

		std::cout << "Элементы транспонированной матрицы: " << std::endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				std::cout << transposed_matrix[i][j] << ' ';
			}
			std::cout << std::endl;
		}

    SumOfFirstMatrix(matrix, n, first_sum, second_sum);
    std::cout << "Сумма элементов четных строк исходной матрицы: " << *first_sum << std::endl ;
    std::cout << "Сумма элементов нечетных столбцов исходной матрицы: " << *second_sum << std::endl;

    SumOfTransposedMatrix(transposed_matrix, n, third_sum, fourth_sum);
    std::cout << "Сумма элементов нечетных строк транспонированной матрицы: " << *third_sum << std::endl;
    std::cout << "Сумма элементов четных столбцов транспонированной матрицы: " << *fourth_sum << std::endl;

    for (int i = 0; i < n; i++) {
      delete[] matrix[i];
      delete[] transposed_matrix[i];
    }
    delete[] matrix;
    delete[] transposed_matrix;
		
    first_sum = nullptr;
    second_sum = nullptr;
    third_sum = nullptr;
    fourth_sum = nullptr;
	}
}

int main() {
	std::string command;

	ShowInstructions(1);

	while(true) {
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
			std::cout << "Программа не обрабатывает введенную команду" << std::endl;
		}
	}
}