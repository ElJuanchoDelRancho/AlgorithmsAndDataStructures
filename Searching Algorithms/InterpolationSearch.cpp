/**
    InterpolationSearch.cpp
    Purpose: Interpolation Search in array of 10,000 elements

    @author: Juan Castillo
    @version: 1.0 23/06/2019
*/

#include <iostream>
#include <random>
#include <chrono>

inline int random_number(std::mt19937 &rng, int lower, int higher) {
    std::uniform_int_distribution<int> dist(lower, higher);
    return dist(rng);
}

void insertion_sort(int arr[], int size);
int interpolation_search(int arr[], int size, int key);

int main() {
    const int size = 10000;
    int array[size];
    int value_to_search;
    int index;

    //std::random_device rd;
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);

    for (int i = 0; i < size; i++) {
        array[i] = random_number(rng, 1, 1000);
    }

    insertion_sort(array, size);
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << ' ';
    }

    std::cout << "\nEnter a number between 1 and 1000 to search in the array\n";
    std::cin >> value_to_search;
    index = interpolation_search(array, size, value_to_search);

    if (index != -1) {
        std::cout << "The number searched is in index: " << index << '\n';
    } else {
        std::cout << "The number isn't in the array\n";
    }
    std::cin.get();
    std::cin.get();

    return 0;
}

void insertion_sort(int arr[], int size) {
    int current;
    int aux_index;
    for (int i = 1; i < size; i++) {
        current = arr[i];
        aux_index = i;
        while (current < arr[aux_index - 1] && aux_index > 0) {
            arr[aux_index] = arr[aux_index - 1];
            aux_index--;
        }
        arr[aux_index] = current;
    }
}

int interpolation_search(int arr[], int size, int key) {
    int low = 0;
    int high = size - 1;
    while (low <= high && key >= arr[low] && key <= arr[high]) {
        // Probing position with uniform distribution
        int pos = low + (((double)(high - low) / (arr[high] - arr[low])) * (key - arr[low])); 
        if (arr[pos] == key) {
            return pos;
        } else if (arr[pos] > key) {
            high = pos - 1;
        } else {
            low = pos + 1;
        }
    }
    return -1;
}
