///
// Filename: testFilesOps.cpp
// Description: Unit test for the Bug class - low level module test
//
// Version History:
// 1.0 2024-07-18 - Initial Version
///

#include <iostream>
#include <cassert>

#include "Bug.h"

int main() {
    Bug b = Bug(1, "Test Description", "high", "open", 3, 5);

    std::cout << "Writing to file...\n";
    std::cout << "Bug Details: ID = " << b.getBugID()
              << ", Description = " << b.getDescription()
              << ", Severity = " << b.getSeverity()
              << ", Status = " << b.getStatus()
              << ", ProductID = " << b.getProductID() << std::endl;

    assert(Bug::writeBug(b));
    std::cout << "Write operation passed!\n\n";

    Bug b2;
    std::cout << "Reading from file...\n";
    assert(Bug::getNext(b2, 0));

    std::cout << "Bug Details: ID = " << b2.getBugID()
              << ", Description = " << b2.getDescription()
              << ", Severity = " << b2.getSeverity()
              << ", Status = " << b2.getStatus()
              << ", ProductID = " << b2.getProductID() << std::endl;
    std::cout << "Read operation passed!\n\n";

    std::cout << "Verifying data integrity...\n";

    std::cout << "Comparing IDs: " << b.getBugID() << " vs " << b2.getBugID() << std::endl;
    assert(b.getBugID() == b2.getBugID());
    std::cout << "ID check passed!\n";

    std::cout << "Comparing Descriptions: " << b.getDescription() << " vs " << b2.getDescription() << std::endl;
    assert(b.getDescription() == b2.getDescription());
    std::cout << "Description check passed!\n";

    std::cout << "Comparing Severities: " << b.getSeverity() << " vs " << b2.getSeverity() << std::endl;
    assert(b.getSeverity() == b2.getSeverity());
    std::cout << "Severity check passed!\n";

    std::cout << "Comparing Statuses: " << b.getStatus() << " vs " << b2.getStatus() << std::endl;
    assert(b.getStatus() == b2.getStatus());
    std::cout << "Status check passed!\n";

    std::cout << "Comparing ProductIDs: " << b.getProductID() << " vs " << b2.getProductID() << std::endl;
    assert(b.getProductID() == b2.getProductID());
    std::cout << "ProductID matches!\n";

    std::cout << "All tests passed!\n";
}