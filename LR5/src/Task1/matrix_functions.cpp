#include "matrix_functions.h"
#include <iostream>

void SumOfFirstMatrix(int **matrix, int n, int * first_sum, int *second_sum) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if ((i + 1) % 2 == 0) {
        *first_sum += matrix[i][j];
      } else if ((j + 1) % 2 == 1) {
        *second_sum += matrix[i][j];
      }
    }
  }
}

void SumOfTransposedMatrix(int **matrix, int n, int *first_sum, int *second_sum) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if ((i + 1) % 2 == 1) {
        *first_sum += matrix[i][j];
      } else if ((j + 1) % 2 == 0) {
        *second_sum += matrix[i][j];
      }
    }
  }
}

void TranspositionOfMatrix(int **matrix, int **transposed_matrix, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i + 1 <= 5) {
        matrix[i][j] = 2 * i * j * j - 2 * j;
      } else {
        matrix[i][j] = 3 * i * j - 3;
      }
      transposed_matrix[j][i] = matrix[i][j];
    }
  }
}