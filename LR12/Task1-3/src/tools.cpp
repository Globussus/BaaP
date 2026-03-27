#include "tools.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <cmath>

void cleanInput() {
    std::cin.clear();
    std::cin.ignore(32657, '\n');
}

void heapify(std::vector<int> &array, int n, int i) {
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

void heapSort(std::vector<int> &array, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(array, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        std::swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}

void merge(std::vector<int> &array, int start, int end, int mid) {
    std::vector<int> mergedList(end - start + 1);
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

void mergeSort(std::vector<int> &array, int start, int end) {
    int mid;
    if (start < end) {
        mid = (start + end) / 2;
        mergeSort(array, start, mid);
        mergeSort(array, mid + 1, end);
        merge(array, start, end, mid);
    }
}

int partition(std::vector<int> &array, int start, int end) {
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

void quickSort(std::vector<int> &array, int start, int end) {
    if (start < end) {
        int pivot = partition(array, start, end);
        quickSort(array, start, pivot - 1);
        quickSort(array, pivot + 1, end);
    }
}

int binarySearch(std::vector<int> &array, int element, int length) {
    int left = 0, right = length - 1, mid = 0;
    while (left <= right) {
        mid = (left + right) / 2;
        if (array[mid] == element) {
            return mid;
        } else if (array[mid] > element) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return -1;
}

std::string printArray(std::vector<int>& array, int length) {
    std::string output;
    for (int i = 0; i < length; i++) {
        output.append(std::to_string(array[i]) + " ");
    }
    output.append("\n");
    return output;
}

void interpolationSort(std::vector<int> &array, int length, std::string &message) {
    if (length <= 1) {
        return;
    }

    int minimumValue = array[0];
    int maximumValue = array[0];

    for (int i = 1; i < length; i++) {
        if (array[i] < minimumValue) {
            minimumValue = array[i];
        }
        if (array[i] > maximumValue) {
            maximumValue = array[i];
        }
    }

    if (minimumValue == maximumValue) {
        return;
    }
    message.append(printArray(array, length));
    std::vector<std::vector<int>> buckets(length);

    for (int i = 0; i < length; i++) {
        int bucketId = (int)(((double)(array[i] - minimumValue) / (maximumValue - minimumValue)) * (length - 1));
        buckets[bucketId].push_back(array[i]);
    }

    int index = 0;
    for (int i = 0; i < length; i++) {
        if (!buckets[i].empty()) {
            message.append(printArray(array, length));
            if (buckets[i].size() > 1) {
                interpolationSort(buckets[i], buckets[i].size(), message);
            }
            for (int val : buckets[i]) {
                array[index++] = val;
            }
        }
    }
}


int interpolationSearch(std::vector<int> &array, int length, int element) {
    int left = 0;
    int right = length - 1;

    while (left <= right && element >= array[left] && element <= array[right]) {
        if (array[left] == array[right]) {
            return (array[left] == element) ? left : -1;
        }
        int mid = left + ((double)(element - array[left]) * (right - left)) / (array[right] - array[left]);
        if (array[mid] < element) {
            left = mid + 1;
        } else if (array[mid] > element) {
            right = mid - 1;
        } else {
            return mid;
        }
    }
    return -1;
}

int binaryPow(int digit, int powder, int mod) {
    long long result = 1; 
    long long d = digit % mod;

    while (powder > 0) {
        if (powder & 1) {
            result = (result * d) % mod;
        }
        d = (d * d) % mod; 
        powder >>= 1;     
    }
    return (int)result;
}

std::vector<int> findMedians(std::vector<int> &array, int length) {
    std::vector<int> medians(std::ceil(length / 3.0));
    std::vector<int> group(3);
    int counter = 0, index = 0;
    for (int i = 0; i < length; i++) {
        group[index] = array[i];

        if (index == 2) {
            quickSort(group, 0, 2);
            medians[counter++] = group[1];
            index = 0;
        } else {
            index++;
        }
    }
    if (index != 0) {
        int sum = 0;
        for (int i = 0; i < index; i++) {
            sum += group[i];
        }
        medians[counter] = sum / index;
    }
    return medians;
}
