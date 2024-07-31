// Filename: performance_test.cpp
#include <iostream>
#include <chrono>
#include "Bug.h"

void performanceTest() {
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000; ++i) {
        Bug bug("Description", "High", "Open", 101, 1);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;
}

int main() {
    performanceTest();
    return 0;
}