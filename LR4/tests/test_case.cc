#include <iostream>
#include <gtest/gtest.h>
#include "../modules/functions.h"

TEST(Task1, test1) {
  int numbers[6] = {1, -1, 2, -2, 3, -3}; 
  int neg_nums[3] = {-1, -2, -3}; 
  int non_neg_nums[3] = {1, 2, 3};
  int* negative = MakeArrayOfNegative(numbers, 6); 
  int* non_negative = MakeArrayOfNonNegative(numbers, 6);

  EXPECT_EQ(true, AreEquivalentArrays(negative, neg_nums, 3)); 
  EXPECT_EQ(true, AreEquivalentArrays(non_negative, non_neg_nums, 3));
  delete[] negative;
  delete[] non_negative;
} 

TEST(Task1, test2) {
  int numbers[10] = {10, 20, 30, 40, 50, -10, -30, -20, 100, 200}; 
  int neg_nums[3] = {-10, -30, -20}; 
  int non_neg_nums[7] = {10, 20, 30, 40, 50, 100, 200};
  int* negative = MakeArrayOfNegative(numbers, 10); 
  int* non_negative = MakeArrayOfNonNegative(numbers, 10);

  EXPECT_EQ(true, AreEquivalentArrays(negative, neg_nums, 3)); 
  EXPECT_EQ(true, AreEquivalentArrays(non_negative, non_neg_nums, 7));
  delete[] negative;
  delete[] non_negative;
} 

TEST(Task2, test1) {
  int array[9] = {1, 2, 3, 
                  4, 5, 6, 
                  7, 8, 9}; 
  EXPECT_EQ(4, FindMaxElementOfMatrix(array, 3));
}

TEST(Task2, test2) {
  int array[16] = {10, 20, 34, 14,
                  56, 19, 99, 43,
                  13, 8, 9, 13,
                  10, 56, 109, 4};
  EXPECT_EQ(56, FindMaxElementOfMatrix(array, 4));
}

TEST(Task3, test1) {
  int** matrix = new int*[3]{};

  for (int i = 0; i < 3; i++) {
    matrix[i] = new int[3]{i * 1, i * 2, i * 3};
  }

  EXPECT_EQ(false, IsMagicalSquare(matrix, 3));

  for (int i = 0; i < 3; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

TEST(Task3, test2) {
  int** matrix = new int*[3]{};

  for (int i = 0; i < 3; i++) {
    matrix[i] = new int[3]{1 + i, 2, 3 - i};
  }

  EXPECT_EQ(false, IsMagicalSquare(matrix, 3));

  for (int i = 0; i < 3; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
}

TEST(Task3, test3) {
  int** matrix = new int*[4]{};

  for (int i = 0; i < 4; i++) {
    matrix[i] = new int[4]{1, 1, 1, 1};
  }

  EXPECT_EQ(true, IsMagicalSquare(matrix, 4));

  for (int i = 0; i < 4; i++) {
    delete[] matrix[i];
  }
  delete[] matrix;
}