#include <iostream>
#include <gtest/gtest.h>
#include <cmath>
#include "../include/tools.h"
#include "../src/Task1/matrix_functions.h"
#include "../src/Task2/array_functions.h"

TEST(Task1, test1) {
  int n = 1;
  int string_sum_of_first = 0, row_sum_of_first = 0, string_sum_of_second = 0, row_sum_of_second = 0;

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

  SumOfFirstMatrix(matrix, n, first_sum, second_sum);
  EXPECT_EQ(0, string_sum_of_first);
  EXPECT_EQ(0, row_sum_of_first);

  SumOfTransposedMatrix(transposed_matrix, n, third_sum, fourth_sum);
  EXPECT_EQ(0, string_sum_of_second);
  EXPECT_EQ(0, row_sum_of_second);

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

TEST(Task1, test2) {
  int n = 2;
  int string_sum_of_first = 0, row_sum_of_first = 0, string_sum_of_second = 0, row_sum_of_second = 0;

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

  SumOfFirstMatrix(matrix, n, first_sum, second_sum);
  EXPECT_EQ(0, string_sum_of_first);
  EXPECT_EQ(0, row_sum_of_first);

  SumOfTransposedMatrix(transposed_matrix, n, third_sum, fourth_sum);
  EXPECT_EQ(0, string_sum_of_second);
  EXPECT_EQ(0, row_sum_of_second);

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

TEST(Task1, test3) {
  int n = 5;
  int string_sum_of_first = 0, row_sum_of_first = 0, string_sum_of_second = 0, row_sum_of_second = 0;

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

  SumOfFirstMatrix(matrix, n, first_sum, second_sum);
  EXPECT_EQ(200, string_sum_of_first);
  EXPECT_EQ(204, row_sum_of_first);

  SumOfTransposedMatrix(transposed_matrix, n, third_sum, fourth_sum);
  EXPECT_EQ(340, string_sum_of_second);
  EXPECT_EQ(64, row_sum_of_second);

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

TEST(Task2, test1) {
  const int length = 1;
  double array[length] {};

  for (int i = 0; i < length; i++) {
    array[i] = 0.0;
  }

  EXPECT_DOUBLE_EQ(-1.0, RecursiveMultiplication(array, length, 0, 0));
}

TEST(Task2, test2) {
  const int length = 5;
  double array[length] {};

  for (int i = 0; i < length; i++) {
    array[i] = M_PI;
  }

  EXPECT_DOUBLE_EQ(1.0, RecursiveMultiplication(array, length, 0, 4));
}

TEST(Task2, test3) {
  const int length = 4;
  double array[length] {};

  for (int i = 0; i < length; i++) {
    array[i] = M_PI_4;
  }

  EXPECT_NEAR(0.0, RecursiveMultiplication(array, length, 0, 3), 1e-10);
}


TEST(Task3, test1) {
  const int n = 0;
  const int k = 0;

  int** matrix = new int* [n] {};
  
  for (int i = 0; i <= n; i++) {
    matrix[i] = new int [k] {};
  }

  int amount_of_even = CountEvenElementsOfMainDiagonal(matrix, n, k);
  int* array = new int[amount_of_even];

  int* example = nullptr;
  EXPECT_EQ(0, AreEquivalentArrays(array, example, amount_of_even, 1));
  EXPECT_EQ(0, MultiplicationOfMatrix(matrix, n, k));

  for (int i = 0; i < n; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
  delete[] array;
}

TEST(Task3, test2) {
  const int n = 1;
  const int k = 1;

  int** matrix = new int* [n] {};

  for (int i = 0; i < n; i++) {
    matrix[i] = new int[k] {};
  }

  for (int i = 0; i < n; i++) {
    matrix[i][i] = 1;
  }

  const int amount_of_even = CountEvenElementsOfMainDiagonal(matrix, n, k);
  EXPECT_EQ(0, amount_of_even);
  int* array = new int[amount_of_even];

  CreateArrayOfEven(matrix, array, n, k, amount_of_even);

  int example[1] = {1};
  EXPECT_EQ(false, AreEquivalentArrays(array, example, amount_of_even, 1));
  EXPECT_EQ(1, MultiplicationOfMatrix(matrix, n, k));

  for (int i = 0; i < n; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
  delete[] array;
}

TEST(Task3, test3) {
  const int n = 3;
  const int k = 3;

  int** matrix = new int* [n] {};

  for (int i = 0; i < n; i++) {
    matrix[i] = new int[k] {};
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      matrix[i][j] = (i + 1) * (j + 1);
    }
  }

  const int amount_of_even = CountEvenElementsOfMainDiagonal(matrix, n, k);
  EXPECT_EQ(1, amount_of_even);
  int* array = new int[amount_of_even];

  CreateArrayOfEven(matrix, array, n, k, amount_of_even);

  int example[1] = {4};
  EXPECT_EQ(true, AreEquivalentArrays(array, example, amount_of_even, 1));
  EXPECT_EQ(46656, MultiplicationOfMatrix(matrix, n, k));

  for (int i = 0; i < n; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
  delete[] array;
}

TEST(Task4, test1) {
  const int n = 1;
  const int k = 1;

  double** matrix = new double* [n] {};
  double** example = new double* [n] {};

  for (int i = 0; i < n; i++) {
    matrix[i] = new double[k] {};
    example[i] = new double[k] {};
  }
  matrix[0][0] = 0;
  example[0][0] = 0;

  const int amount_of_zeroes = CountZeroes(matrix, n, k);
  EXPECT_EQ(1, amount_of_zeroes);

  EXPECT_EQ(true, IsEquivalentMatrix(matrix, example, n, k, 1, 1));
  
  ReverseMatrix(matrix, n, k);
  ReverseMatrix(example, n, k);
  EXPECT_EQ(true, IsEquivalentMatrix(matrix, example, n, k, 1, 1));

  for (int i = 0; i < n; i++) {
    delete[] matrix[i];
    delete[] example[i];
  }
  delete[] matrix;
  delete[] example;
}

TEST(Task4, test2) {
  const int n = 3;
  const int k = 3;

  double** matrix = new double* [n] {};
  double** example = new double* [n] {};

  for (int i = 0; i < n; i++) {
    matrix[i] = new double[k] {};
    example[i] = new double[k] {};
  }
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      if (i <= j) {
        matrix[i][j] = 1;
        example[i][j] = 1;
      } else {
        matrix[i][j] = 0;
        example[i][j] = 0;
      }
    }
  }

  const int amount_of_zeroes = CountZeroes(matrix, n, k);
  EXPECT_EQ(3, amount_of_zeroes);

  EXPECT_EQ(true, IsEquivalentMatrix(matrix, example, n, k, 3, 3));
  
  ReverseMatrix(matrix, n, k);
  ReverseMatrix(example, n, k);
  EXPECT_EQ(true, IsEquivalentMatrix(matrix, example, n, k, 3, 3));

  for (int i = 0; i < n; i++) {
    delete[] matrix[i];
    delete[] example[i];
  }
  delete[] matrix;
  delete[] example;
}

TEST(Task4, test3) {
  const int n = 5;
  const int k = 5;

  double** matrix = new double* [n] {};
  double** example = new double* [n] {};

  for (int i = 0; i < n; i++) {
    matrix[i] = new double[k] {};
    example[i] = new double[k] {};
  }
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      if (i <= j) {
        matrix[i][j] = 1;
        example[i][j] = 1;
      } else {
        matrix[i][j] = 0;
        example[i][j] = 0;
      }
    }
  }

  const int amount_of_zeroes = CountZeroes(matrix, n, k);
  EXPECT_EQ(10, amount_of_zeroes);

  EXPECT_EQ(true, IsEquivalentMatrix(matrix, example, n, k, 5, 5));

  ReverseMatrix(matrix, n, k);
  EXPECT_EQ(false, IsEquivalentMatrix(matrix, example, n, k, 5, 5));

  for (int i = 0; i < n; i++) {
    delete[] matrix[i];
    delete[] example[i];
  }
  delete[] matrix;
  delete[] example;
}

TEST(Task5, test1) {
  const int n = 2;
  const int k = 2;

  int** matrix = new int*[n];
  for (int i = 0; i < n; i++) {
    matrix[i] = new int[k];
  }

  matrix[0][0] = 1;
  matrix[0][1] = 0;
  matrix[1][0] = 0;
  matrix[1][1] = 1;

  int amount_of_non_even = CountNonEvenElementsFromEvenColumns(matrix, n, k);
  EXPECT_EQ(1, amount_of_non_even);

  int* array = new int[amount_of_non_even];
  CreateArrayOfNonEven(matrix, array, n, k);

  int example[amount_of_non_even] = {1};
  EXPECT_EQ(true, AreEquivalentArrays(array, example, amount_of_non_even, 1));

  int arithmetic_mean = CountArithmeticMean(array, amount_of_non_even);
  EXPECT_EQ(1, arithmetic_mean);
}

TEST(Task5, test2) {
  const int n = 3;
  const int k = 3;

  int** matrix = new int*[n];
  for (int i = 0; i < n; i++) {
    matrix[i] = new int[k];
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      if (!(j % 2)) {
        matrix[i][j] = j + 1;
      } else {
        matrix[0][j] = 1;
      }
    }
  }

  int amount_of_non_even = CountNonEvenElementsFromEvenColumns(matrix, n, k);
  EXPECT_EQ(6, amount_of_non_even);

  int* array = new int[amount_of_non_even];
  CreateArrayOfNonEven(matrix, array, n, k);

  int example[amount_of_non_even] = {1, 3, 1, 3, 1, 3};
  EXPECT_EQ(true, AreEquivalentArrays(array, example, amount_of_non_even, 6));

  int arithmetic_mean = CountArithmeticMean(array, amount_of_non_even);
  EXPECT_EQ(2, arithmetic_mean);
}

TEST(Task5, test3) {
  const int n = 5;
  const int k = 5;

  int** matrix = new int*[n];
  for (int i = 0; i < n; i++) {
    matrix[i] = new int[k];
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      if (!(j % 2)) {
        matrix[i][j] = i * i;
      } else {
        matrix[0][j] = 0;
      }
    }
  }

  int amount_of_non_even = CountNonEvenElementsFromEvenColumns(matrix, n, k);
  EXPECT_EQ(6, amount_of_non_even);

  int* array = new int[amount_of_non_even];
  CreateArrayOfNonEven(matrix, array, n, k);

  int example[amount_of_non_even] = {1, 1, 1, 9, 9, 9};
  EXPECT_EQ(true, AreEquivalentArrays(array, example, amount_of_non_even, 6));

  int arithmetic_mean = CountArithmeticMean(array, amount_of_non_even);
  EXPECT_EQ(5, arithmetic_mean);
}