/**
    ShakerSort.cpp
    Purpose: Shaker sort in an array of 10,000 elements

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

void shaker_sort(int arr[], int size);

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

    shaker_sort(array, size);

    std::cout << "\n\n";
    std::cout << "The sorted array is:\n";
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << ' ';
    }
    std::cout << "\n\n";
    std::cin.get();

    return 0;
}

void shaker_sort(int arr[], int size) {
    int aux;
    int left = 0;
    int right = size - 1;
    int last_exchange;
    while (left < right) {
        for (int i = right; i > left; i--) {
            if (arr[i] < arr[i - 1]) {
                aux = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = aux;
                last_exchange = i;
            }
        }
        left = last_exchange;
        for (int i = left; i < right; i++) {
            if (arr[i] > arr[i + 1]) {
                aux = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = aux;
                last_exchange = i;
            }
        }
        right = last_exchange;
    }
}
