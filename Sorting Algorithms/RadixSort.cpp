/**
    RadixSort.cpp
    Purpose: Radix sort in an array of 10,000 elements

    @author: Juan Castillo
    @version: 1.0 03/06/2019
*/

#include <iostream>
#include <random>
#include <chrono>
#include <vector>

inline int random_number(std::mt19937 &rng, int lower, int higher) {
    std::uniform_int_distribution<int> dist(lower, higher);
    return dist(rng);
}

int max(int arr[], int size);
void radix_sort(int arr[], int size);
void counting_sort(int arr[], int size, int exp);

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

    radix_sort(array, size);

    std::cout << "\n\n";
    std::cout << "The sorted array is:\n";
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << ' ';
    }
    std::cout << "\n\n";
    std::cin.get();

    return 0;
}

int max(int arr[], int size) {
    int maximum = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > maximum) {
            maximum = arr[i];
        }
    }
    return maximum;
}

void radix_sort(int arr[], int size) {
    int maximum = max(arr, size);
    for (int exp = 1; maximum / exp > 0; exp *= 10) {
        counting_sort(arr, size, exp);
    }
}

void countingSort(int arr[], int size, int exp) {
    int counting[10] = { 0 };
    std::vector<int> output(size);
    // The matches of the digits are saved in counting array
    for (int i = 0; i < size; i++) {
        counting[ (arr[i] / exp) % 10 ]++;
    }
    // Now counting array has the last index + 1 of the digits
    for (int i = 1; i < size; i++) {
        counting[i] += counting[i - 1];
    }
    // An auxiliary output array is prepared
    for (int i = size - 1; i >= 0; i--) {
        output[ counting[ (arr[i] / exp) % 10 ] - 1 ] = arr[i];
        counting[ (arr[i] / exp) % 10 ]--;
    }
    for (int i = 0; i < size; i++) {
        arr[i] = output[i];
    }
}
