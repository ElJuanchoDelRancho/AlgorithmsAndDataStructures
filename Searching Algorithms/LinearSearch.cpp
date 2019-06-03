/**
    LinearSearch.cpp
    Purpose: Linear Search in array of 10,000 elements

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

int linear_search(int arr[], int size, int key);

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
        std::cout << array[i] << ' ';
    }

    std::cout << "\nEnter a number between 1 and 1000 to search in the array\n";
    std::cin >> value_to_search;
    index = linear_search(array, size, value_to_search);

    if (index != -1) {
        std::cout << "The number searched is in position: " << index << '\n';
    } else {
        std::cout << "The number isn't in the array\n";
    }
    std::cin.get();
    std::cin.get();

    return 0;
}

int linear_search(int arr[], int size, int key) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}
