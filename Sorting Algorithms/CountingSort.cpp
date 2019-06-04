/**
    CountingSort.cpp
    Purpose: Counting sort in an array of 10,000 elements

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

int min(int arr[], int size);
int max(int arr[], int size);
void counting_sort(int arr[], int size);

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

    counting_sort(array, size);

    std::cout << "\n\n";
    std::cout << "The sorted array is:\n";
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << ' ';
    }
    std::cout << "\n\n";
    std::cin.get();

    return 0;
}

int min(int arr[], int size) {
    int minimum = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < minimum) {
            minimum = arr[i];
        }
    }
    return minimum;
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

void counting_sort(int arr[], int size) {
    int minimum = min(arr, size);
    int maximum = max(arr, size);
    std::vector<int> counting(maximum - minimum + 1);
    for (int i = 0; i < size; i++) {
        counting[ arr[i] + minimum * -1 ]++;
    }
    int x = 0;
    for (int i = 0; i < counting.size(); i++) {
        for (int j = 1; j <= counting[i]; j++) {
            arr[x] = minimum + i;
            x++;
        }
    }
}
