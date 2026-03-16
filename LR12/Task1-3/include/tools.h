#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <memory>
#include <random>
#include <chrono>

void heapify(std::unique_ptr<int[]> &array, int n, int i);
void heapSort(std::unique_ptr<int[]> &array, int n);

void merge(std::unique_ptr<int[]> &array, int start, int end, int mid);
void mergeSort(std::unique_ptr<int[]> &array, int start, int end);

int partition(std::unique_ptr<int[]> &array, int start, int end);
void quickSort(std::unique_ptr<int[]> &array, int start, int end);

#endif