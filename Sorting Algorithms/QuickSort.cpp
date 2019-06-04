/**
    QuickSort.cpp
    Purpose: Quick sort in an array of 10,000 elements

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

void quick_sort(int arr[], int low, int high);
int partition(int arr[], int low, int high);

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

    quick_sort(array, 0, size - 1);

    std::cout << "\n\n";
    std::cout << "The sorted array is:\n";
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << ' ';
    }
    std::cout << "\n\n";
    std::cin.get();

    return 0;
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
		int mid = partition(arr, low, high);
        quick_sort(arr, low, mid - 1);
        quick_sort(arr, mid + 1, high);
	}
}

int partition(int arr[], int low, int high) {
    int i = low;
    int j = high - 1;
    int pivot = arr[high];
    int aux;
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            aux = arr[i];
            arr[i] = arr[j];
            arr[j] = aux;
            i++;
            j--;
        }
    }
    arr[high] = arr[i];
    arr[i] = pivot;
    return i;
}
