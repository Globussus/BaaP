#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <chrono>
#include <vector>
#include <string>

void cleanInput();

void heapify(std::vector<int> &array, int n, int i);
void heapSort(std::vector<int> &array, int n);

void merge(std::vector<int> &array, int start, int end, int mid);
void mergeSort(std::vector<int> &array, int start, int end);

int partition(std::vector<int> &array, int start, int end);
void quickSort(std::vector<int> &array, int start, int end);

int binarySearch(std::vector<int> &array, int element, int length);

std::string printArray(std::vector<int> &array, int length);
void interpolationSort(std::vector<int> &array, int length, std::string &message);
int interpolationSearch(std::vector<int> &array, int length, int element);
int binaryPow(int digit, int power, int mod);

std::vector<int> findMedians(std::vector<int> &array, int length);

#endif