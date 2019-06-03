/**
    MergeSort.cpp
    Purpose: Merge sort in an array of 10,000 elements

    @author: Juan Castillo
    @version: 1.0 03/06/2019
*/

#include <iostream>
#include <random>
#include <chrono>

inline int random_number(std::mt19937 &rng, int lower, int higher) {
    std::uniform_int_distribution<int> dist(lower, higher);
    return dist(rng);
}

void merge_sort(int arr[], int low, int high);
void merge(int arr[], int low, int mid, int high);

int main() {
    const int size = 10000;
    int array[size];

    //std::random_device rd;
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);

    for (int i = 0; i < size; i++) {
        array[i] = random_number(rng, 1, 1000);
        std::cout << array[i] << ' ';
    }

    merge_sort(array, 0, size - 1);

    std::cout << "\n\n";
    std::cout << "The sorted array is:\n";
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << ' ';
    }
    std::cout << "\n\n";
    std::cin.get();

    return 0;
}

void merge_sort(int arr[], int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        merge_sort(arr, low, mid);
        merge_sort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

void merge(int arr[], int low, int mid, int high) {
    int p1 = low;
    int p2 = mid + 1;
    int index = 0;
    std::vector<int> aux_array(arr + low, arr + high + 1);

    while (p1 < mid + 1 || p2 < high + 1) {
        if (p1 > mid) {
            aux_array[index] = arr[p2];
            p2++;
        } else if (p2 > high) {
            aux_array[index] = arr[p1];
            p1++;
        } else if (arr[p1] < arr[p2]) {
            aux_array[index] = arr[p1];
            p1++;
        } else {
            aux_array[index] = arr[p2];
            p2++;
        }
        index++;
    }
    for (int i = 0; i < aux_array.size(); i++) {
        arr[i + low] = aux_array[i];
    }
}
