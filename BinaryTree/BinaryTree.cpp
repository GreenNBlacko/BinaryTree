#include <iostream>
#include <string>
#include <chrono>
#include "GrayStl.h"

using namespace std;
using namespace std::chrono;

void generateRandomArray(Vector<int>& list, int size) {
    list.clear();

    srand(time(NULL));
    for (int i = 0; i < size; ++i) {
        list.push_back(rand() % 1000); // Generate random numbers between 0 and 999
    }
}

template<typename T>
long long measureSortingTime(T& obj, void (T::* sortingFunction)()) {
    auto start = high_resolution_clock::now();
    (obj.*sortingFunction)(); // Call member function using the object
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

int main() {
    Vector<int> counts = { 5000, 10000, 50000, 100000};
    int testsCount = 5;

    for (int i = 0; i < counts.size(); i++) {
        Vector<long long> times = Vector<long long>(6, 0);

        for (int o = 0; o < testsCount; o++) {    
            Vector<int> items = Vector<int>();

            generateRandomArray(items, counts[i]);

            Vector<int> items2 = Vector<int>();

            for (int i : items) {
                items2.push_back(i);
            }

            times[0] += measureSortingTime<Vector<int>>(items, &Vector<int>::mergeSort); // Random

            times[1] += measureSortingTime<Vector<int>>(items, &Vector<int>::mergeSort); // Sorted

            items.reverse();

            times[2] += measureSortingTime<Vector<int>>(items, &Vector<int>::mergeSort); // Reversed

            // VS

            times[3] += measureSortingTime<Vector<int>>(items2, &Vector<int>::shellSort); // Random

            times[4] += measureSortingTime<Vector<int>>(items2, &Vector<int>::shellSort); // Sorted

            items2.reverse();

            times[5] += measureSortingTime<Vector<int>>(items2, &Vector<int>::shellSort); // Reversed
        }

        printf("\nTimes(MergeSort, %d elements):\nRandom -> %d \xE6s\nSorted -> %d \xE6s\nReversed -> %d \xE6s\n", counts[i], times[0] / testsCount, times[1] / testsCount, times[2] / testsCount);
        printf("\nTimes(ShellSort, %d elements):\nRandom -> %d \xE6s\nSorted -> %d \xE6s\nReversed -> %d \xE6s\n", counts[i], times[3] / testsCount, times[4] / testsCount, times[5] / testsCount);
    }
}
