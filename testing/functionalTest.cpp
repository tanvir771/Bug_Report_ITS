// Filename: functional_test.cpp
#include <iostream>
#include "Bug.h"
#include "Request.h"

void testBugCreation() {
    Bug bug1("Description 1", "High", "Open", 101, 1);
    Bug bug2("Description 2", "Medium", "Closed", 102, 2);

    if (bug1.getBugID() != 1 || bug2.getBugID() != 2) {
        std::cerr << "Bug creation test failed!" << std::endl;
    } else {
        std::cout << "Bug creation test passed." << std::endl;
    }
}

void testRequestCreation() {
    Request request1("Request Description 1", 201);
    Request request2("Request Description 2", 202);

    if (request1.getRequestID() != 1 || request2.getRequestID() != 2) {
        std::cerr << "Request creation test failed!" << std::endl;
    } else {
        std::cout << "Request creation test passed." << std::endl;
    }
}

void testFileOperations() {
    std::string idFile = "test_ids.dat";

    Bug::writeLastID(idFile);
    Request::writeLastID(idFile);

    Bug::bugIDCount = 0;
    Request::requestIDCount = 0;

    Bug::readLastID(idFile);
    Request::readLastID(idFile);

    if (Bug::bugIDCount != 2 || Request::requestIDCount != 2) {
        std::cerr << "File operations test failed!" << std::endl;
    } else {
        std::cout << "File operations test passed." << std::endl;
    }
}

int main() {
    testBugCreation();
    testRequestCreation();
    testFileOperations();
    return 0;
}