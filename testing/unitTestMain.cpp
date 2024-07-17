/// 
 // Filename: unitTestCustomer.cpp
 // Description: Unit test for the Customer class
 // 
 // Version History:
 // 1.0 2024-07-03 - Initial version
 ///

#include <iostream>
#include "Customer.h"

int main() {
    // Create a Customer object
    Customer customer("John Doe", "123-456-7890", "johndoe@example.com");

    // Test getCustomerName() function
    std::string expectedName = "John Doe";
    std::string returnedName = customer.getCustomerName();
    if (expectedName == returnedName) {
        std::cout << "Unit test of getCustomerName(): Passed" << std::endl;
    } else {
        std::cout << "Unit test of getCustomerName(): Failed" << std::endl;
    }

    // Test getPhone() function
    std::string expectedPhone = "123-456-7890";
    std::string returnedPhone = customer.getPhone();
    if (expectedPhone == returnedPhone) {
        std::cout << "Unit test of getPhone(): Passed" << std::endl;
    } else {
        std::cout << "Unit test of getPhone(): Failed" << std::endl;
    }

    // Test getEmail() function
    std::string expectedEmail = "johndoe@example.com";
    std::string returnedEmail = customer.getEmail();
    if (expectedEmail == returnedEmail) {
        std::cout << "Unit test of getEmail(): Passed" << std::endl;
    } else {
        std::cout << "Unit test of getEmail(): Failed" << std::endl;
    }

    // Test setCustomerName() function
    std::string newName = "Jane Doe";
    customer.setCustomerName(newName);
    returnedName = customer.getCustomerName();
    if (newName == returnedName) {
        std::cout << "Unit test of setCustomerName(): Passed" << std::endl;
    } else {
        std::cout << "Unit test of setCustomerName(): Failed" << std::endl;
    }

    // Test setPhone() function
    std::string newPhone = "098-765-4321";
    customer.setPhone(newPhone);
    returnedPhone = customer.getPhone();
    if (newPhone == returnedPhone) {
        std::cout << "Unit test of setPhone(): Passed" << std::endl;
    } else {
        std::cout << "Unit test of setPhone(): Failed" << std::endl;
    }

    // Test setEmail() function
    std::string newEmail = "janedoe@example.com";
    customer.setEmail(newEmail);
    returnedEmail = customer.getEmail();
    if (newEmail == returnedEmail) {
        std::cout << "Unit test of setEmail(): Passed" << std::endl;
    } else {
        std::cout << "Unit test of setEmail(): Failed" << std::endl;
    }

    // Test setIsEmployee() and getIsEmployee() functions
    bool expectedIsEmployee = true;
    customer.setIsEmployee(expectedIsEmployee);
    bool returnedIsEmployee = customer.getIsEmployee();
    if (expectedIsEmployee == returnedIsEmployee) {
        std::cout << "Unit test of setIsEmployee() and getIsEmployee(): Passed" << std::endl;
    } else {
        std::cout << "Unit test of setIsEmployee() and getIsEmployee(): Failed" << std::endl;
    }

    // Test setDepartment() and getDepartment() functions
    std::string expectedDepartment = "Engineering";
    customer.setDepartment(expectedDepartment);
    std::string returnedDepartment = customer.getDepartment();
    if (expectedDepartment == returnedDepartment) {
        std::cout << "Unit test of setDepartment() and getDepartment(): Passed" << std::endl;
    } else {
        std::cout << "Unit test of setDepartment() and getDepartment(): Failed" << std::endl;
    }

    return 0;
}
