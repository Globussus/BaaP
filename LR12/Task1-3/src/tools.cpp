#include "./../include/tools.h"
#include <algorithm>
#include <memory>

void heapify(std::unique_ptr<int[]> &array, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && array[l] > array[largest]) {
        largest = l;
    }

    if (r < n && array[r] > array[largest]) {
        largest = r;
    }

    if (largest != i) {
        std::swap(array[i], array[largest]);
        heapify(array, n, largest);
    }
}

void heapSort(std::unique_ptr<int[]> &array, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(array, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        std::swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}

void merge(std::unique_ptr<int[]> &array, int start, int end, int mid) {
    std::unique_ptr<int[]> mergedList = std::make_unique<int[]>(end - start + 1);
    int i, j, k;
    i = start, k = 0, j = mid + 1;

    while (i <= mid && j <= end) {
        if (array[i] < array[j]) {
            mergedList[k] = array[i];
            k++;
            i++;
        } else {
            mergedList[k] = array[j];
            k++;
            j++;
        }
    }

    while (i <= mid) {
        mergedList[k] = array[i];
        k++;
        i++;
    }

    while (j <= end) {
        mergedList[k] = array[j];
        k++;
        j++;
    }

    for (i = 0; i < k; i++) {
        array[start + i] = mergedList[i];
    }
}

void mergeSort(std::unique_ptr<int[]> &array, int start, int end) {
    int mid;
    if (start < end) {
        mid = (start + end) / 2;
        mergeSort(array, start, mid);
        mergeSort(array, mid + 1, end);
        merge(array, start, end, mid);
    }
}

int partition(std::unique_ptr<int[]> &array, int start, int end) {
    int pivot = array[end];
    int i = start - 1; 
    for (int j = start; j < end; j++) {
        if (array[j] <= pivot) {
            i++;
            std::swap(array[i], array[j]);
        }
    }
    std::swap(array[i + 1], array[end]);
    return i + 1;
}

void quickSort(std::unique_ptr<int[]> &array, int start, int end) {
    if (start < end) {
        int pivot = partition(array, start, end);
        quickSort(array, start, pivot - 1);
        quickSort(array, pivot + 1, end);
    }
}