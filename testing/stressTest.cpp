// Filename: stress_test.cpp
#include <iostream>
#include <thread>
#include <vector>
#include "Bug.h"

void stressTest(int numIterations) {
    for (int i = 0; i < numIterations; ++i) {
        Bug bug("Description", "High", "Open", 101, 1);
    }
}

int main() {
    const int numThreads = 10;
    const int numIterations = 10000;

    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; ++i) {
        threads.push_back(std::thread(stressTest, numIterations));
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Stress test completed." << std::endl;
    return 0;
}