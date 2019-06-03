/**
    BinarySearch.cpp
    Purpose: Binary Search in array of 10,000 elements

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

void insertion_sort(int arr[], int size);
int binary_search(int arr[], int size, int key);

int main()
{
    const int size = 10000;
    int array[size];
    int value_to_search;
    int position;

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
    position = binary_search(array, size, value_to_search);

    if (position != -1) {
        std::cout << "The number searched is in position: " << position << '\n';
    } else {
        std::cout << "The number isn't in the array\n";
    }
    std::cin.get();
    std::cin.get();

    return 0;
}

void insertion_sort(int arr[], int size) {
	int current;
	int aux_pos;
	for (int i = 1; i < size; i++) {
		current = arr[i];
		aux_pos = i;
		while (current < arr[aux_pos - 1] && aux_pos > 0) {
			arr[aux_pos] = arr[aux_pos - 1];
			aux_pos--;
		}
		arr[aux_pos] = current;
	}
}

int binary_search(int arr[], int size, int key)
{
    int low = 0;
    int high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) {
            return mid;
        } else if (arr[mid] > key) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}
