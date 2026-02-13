#ifndef TOOLS
#define TOOLS

#include <iostream>

void CleanInput() {
	std::cin.clear();
	std::cin.ignore(32767, '\n');
}

void ShowInstructions(int number_of_task) {
	switch (number_of_task) {
	case 1:
		std::cout << "Задание 1. Вариант 9. Выполнил: Глобаж Станислав" << std::endl;
		std::cout << "Программа формирует матрицу размера n x n и транспонирует ее (меняет местами строки и столбцы)" << std::endl;
		std::cout << "После этого программа выводит матрицы, вычисляет суммы элементов в определенных строках и столбцах двух матриц" << std::endl;
		std::cout << "Пользователю нужно ввести n — число строк и столбцов матрицы" << std::endl;
		break;
	case 2: 
		std::cout << "Задание 2. Вариант 9. Выполнил: Глобаж Станислав" << std::endl;
		std::cout << "Пользователю нужно ввести N - размер массива" << std::endl;
		std::cout << "Программа, используя рекурсию, вычисляет произведение N множителей вида: (sin C_i - cos C_i)" << std::endl;
		std::cout << "	где C_i - это i-й элемент массива" << std::endl;
		break;
	case 3:
		std::cout << "Задание 3. Выполнил: Глобаж Станислав" << std::endl;
		std::cout << "Пользователю нужно ввести натуральные числа n и k - кол-во строк и столбцов матрицы соответственно" << std::endl;
		std::cout << "Программа строит матрицу из случайных целых чисел." << std::endl;
		std::cout << "Программа находит четные числа на главной диагонали, а также вычисляет произведение элементов матрицы" << std::endl;
		break;
	case 4:
		std::cout << "Задание 4. Выполнил: Глобаж Станислав" << std::endl;
		std::cout << "Пользователю нужно ввести натуральные числа n и k - кол-во строк и столбцов матрицы соответственно" << std::endl;
		std::cout << "Программа строит матрицу из случайных вещественных чисел:" << std::endl;
		std::cout << "	Если в матрице есть нули, программа считает их кол-во и выводит их позиции" << std::endl;
		std::cout << "	После этого матрица выводится в обратном порядке" << std::endl;
		break;
	case 5:
		std::cout << "Задание 5. Выполнил Глобаж Станислав" << std::endl;
		std::cout << "Пользователю нужно ввести натуральные числа n и k - кол-во строк и столбцов матрицы соответственно" << std::endl;
		std::cout << "Программа строит матрицу из случайных целых чисел:" << std::endl;
		std::cout << "	Из нечетных элементов четных столбцов(индексация начинается с нуля) строится новый массив" << std::endl;
		std::cout << "	Программа вычисляет среднее арифметическое элементов нового массива" << std::endl;
		break;
	}
	std::cout << "Пользователю доступны следующие команды:" << std::endl;
	std::cout << "  0 — выход" << std::endl;
	std::cout << "  1 — запуск" << std::endl;
	std::cout << "  2 — выводит инструкцию по использованию программы\n" << std::endl;
}

//Задание 3
int CountEvenElementsOfMainDiagonal(int** matrix, int n, int k) {
	int index = 0, counter = 0;

	while (index < n && index < k) {
		if (matrix[index][index] % 2 == 0) {
			counter++;
		}
		index++;
	}

	return counter;
} 

void CreateArrayOfEven(int** matrix, int* array, int n, int k, int size) {
	int index = 0;
	int position = 0;

	std::cout << "Четные элементы главной диагонали: " << std::endl;
	while (index < n && index < k) {
		if (matrix[index][index] % 2 == 0) {
			array[position] = matrix[index][index];
			std::cout << array[position] << ' ';
			position++;
		}
		index++;
	}
	std::cout << std::endl;
}

long long MultiplicationOfMatrix(int** matrix, int n, int k) {
	if (n == 0 || k == 0) {
		return 0;
	}

	long long multiplication = 1;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			multiplication *= matrix[i][j];
		}
	}

	return multiplication;
}

bool AreEquivalentArrays(int* array, int* other_array, int first_size, int second_size) {
	if (!first_size) {
		return 0;
	} 
	bool flag = true;

	if (first_size != second_size) {
		flag = false;
	} else {
		for (int i = 0; i < first_size; i++) {
			if (array[i] != other_array[i]) {
				flag = false;
				break;
			}
		}
	}
	return flag;
}

//Задание 4
int CountZeroes(double** matrix, int n, int k) {
	int counter = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			if (matrix[i][j] == 0){
				counter++;
			}
		}
	}
	return counter;
}

void ReverseMatrix(double** matrix, int n, int k) {
	double temp[n * k] {};
	double element = 0;
  int index = 0, total_elements = n * k;	

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      temp[index] = matrix[i][j];
			index++;
    }
  }
	
  for (int i = 0; i < total_elements / 2; i++) {
    element = temp[i];
    temp[i] = temp[total_elements - 1 - i];
    temp[total_elements - 1 - i] = element;
  }
  index = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      matrix[i][j] = temp[index];
			index++;
    }
  }
}

bool IsEquivalentMatrix(double** matrix, double** other_matrix, int n1, int k1, int n2, int k2) {
	bool flag = true;

	if (n1 != n2 || k1 != k2) {
		flag = false;
	} else {
		for (int i = 0; i < n1; i++) {
			for (int j = 0; j < k1; j++) {
				if (matrix[i][j] != other_matrix[i][j]) {
					flag = false;
					break;
				}
			}
		}
	}
	return flag;
}

//Задание 5
int CountNonEvenElementsFromEvenColumns(int** matrix, int n, int k) {
	int counter = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			if (!(j % 2) && matrix[i][j] % 2 == 1) {
				counter++;
			}
		}
	}

	return counter;
}

void CreateArrayOfNonEven(int** matrix, int* array, int n, int k) {
	int index = 0;

	std::cout << "Нечетные элементы четных столбцов матрицы: " << std::endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			if (!(j % 2) && matrix[i][j] % 2 == 1) {
				array[index] = matrix[i][j];
				std::cout << array[index] << ' ';
				index++;
			}
		}
	}
	std::cout << std::endl;
}

double CountArithmeticMean(int* array, int length) {
	if (length == 0) {
		return 0;
	}

	double result = 0;

	for (int i = 0; i < length; i++) {
		result += array[i];
	}
	result /= length;

	return result;
}

#endif