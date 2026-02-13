#include <iostream>
#include <algorithm>

int CountNegativeNumbers(int array[], int length) {
  int counter = 0;
    
  for (int i = 0; i < length; i++) {
    if (array[i] < 0) {
      counter++;
    }
  }
  return counter;
}

void CleanInput() {
  std::cin.clear();
  std::cin.ignore(32767, '\n');
}

//Задание 1. Разделение исходного массива на массив с отр. числами и массив с неотр. числами
int* MakeArrayOfNegative(int array[], int length) {
  const int amount_of_neg = CountNegativeNumbers(array, length);
  int* negative_numbers = new int[amount_of_neg];
  int index = 0;

  for (int i = 0; i < length; i++) {
    if (array[i] < 0) {
      negative_numbers[index] = array[i];
      index++;
    }
  }
  return negative_numbers;
}

int* MakeArrayOfNonNegative(int array[], int length) {
  const int amount_of_non_negative = length - CountNegativeNumbers(array, length);
  int* non_negative_numbers = new int[amount_of_non_negative];
  int index = 0;

  for (int i = 0; i < length; i++) {
    if (array[i] >= 0) {
      non_negative_numbers[index] = array[i];
      index++;
    }
  }
  return non_negative_numbers;
}

bool AreEquivalentArrays(int first_array[], int second_array[], int length) {
  bool flag = true;

  for (int i = 0; i < length; i++) {
    if (first_array[i] != second_array[i]) {
      flag = false;
      break;
    }
  }
  return flag;
}

//Задание 2. Поиск максимального элемента, лежащаго выше побочной диагонали. 
int FindMaxElementOfMatrix(int array[], int m) {
  int index = 0;
  int matrix[m][m];

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      matrix[i][j] = array[index];
      index++;
    }
  }

  int right_index = m - 1, maximum = matrix[0][0]; 

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < right_index; j++) {
      if (matrix[i][j] > maximum) {
        maximum = matrix[i][j];
      }
    }
    right_index--;
  }
  return maximum;
}

//Задание 3. Проверка матрицы на то, является ли она магическим квадратом
bool IsMagicalSquare(int** matrix, int N) {
  int result = 0, sum = 0;

  for (int i = 0; i < N; i++) {
    result += matrix[i][0];
  }

  //Проверка рядов
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      sum += matrix[i][j];
    }

    if (sum != result) {
      return false;
    }
    sum = 0;
  }

  //Проверка столбцов
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      sum += matrix[j][i];
    }

    if (sum != result) {
      return false;
    }
    sum = 0;
  }

  //Проверка побочной диагонали
  int i = N - 1;
  while (i >= 0) {
    sum += matrix[i][i];
    i--;
  }

  if (sum != result) {
    return false;
  }
  sum = 0;

  //Проверка главной диагонали
  i = N - 1;
  while (i >= 0) {
    sum += matrix[N - i - 1][i];
    i--;
  }

  if (sum != result) {
    return false;
  }
  sum = 0;

  return true;
}

void ShowInstructions(int number_of_task) {
  switch (number_of_task) {
    case 1:
      std::cout << "Задание 1. Разделение массива на массив. Вариант 9. Выполнил: Глобаж Станислав" << std::endl;
      std::cout << "  Программа запрашивает у пользователя целое число k и генерирует массив из k случайных чисел" << std::endl;
      std::cout << "  Программа разделяет этот массив на два новых массива: " << std::endl;
      std::cout << "    Массив из отрицательных чисел. Массив из неотрицательных чисел" << std::endl;
      break;
    case 2:
      std::cout << "Задание 2. Вычисление максимального элемента матрицы, лежащего выше побочной диагонали. Вариант 9. Выполнил: Глобаж Станислав" << std::endl;
      std::cout << "  Программа запрашивает у пользователя число m и генерирует матрицу размера m x m" << std::endl;
      std::cout << "  Программа находит максимальный элемент матрицы, лежащий выше побочной диагонали" << std::endl;
      std::cout << "(побочная диагональ - диагональ идущая из правого верхнего в нижний левый угол)" << std::endl;
      break;
    case 3:
      std::cout << "Задание 3. Проверка матрицы на то, является ли она магическим квадратом. Вариант 9. Выполнил: Глобаж Станислав" << std::endl;
      std::cout << "  Программа запрашивает у пользователя число N - количество столбцов и рядов в матрице." << std::endl;
      std::cout << "  Программа проверяет столбцы, ряды и две диагонали матрицы:" << std::endl;
      std::cout << "    Если суммы чисел на них равны - матрица является магическим квадратом, иначе - матрица не маг. квадрат." << std::endl;
      break;
  }
  std::cout << "Пользователю доступны следующие команды:" << std::endl;
  std::cout << "  0 — выход" << std::endl;
  std::cout << "  1 — запуск" << std::endl;
  std::cout << "  2 — выводит инструкцию по использованию программы\n" << std::endl;
}