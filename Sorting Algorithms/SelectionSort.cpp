/**
    SelectionSort.cpp
    Purpose: Selection sort in an array of 10,000 elements

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

void selection_sort(int arr[], int size);

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

    selection_sort(array, size);

    std::cout << "\n\n";
    std::cout << "The sorted array is:\n";
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << ' ';
    }
    std::cout << "\n\n";
    std::cin.get();

    return 0;
}

void selection_sort(int arr[], int size) {
    int aux;
	int index_of_min;
	for (int i = 0; i < size - 1; i++) {
		index_of_min = i;
		for (int j = i + 1; j < size; j++) {
			if (arr[j] < arr[index_of_min]) {
				index_of_min = j;
			}
		}
		aux = arr[i];
		arr[i] = arr[index_of_min];
		arr[index_of_min] = aux;
	}
}
