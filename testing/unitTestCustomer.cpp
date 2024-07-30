/// 
 // Filename: unitTestCustomer.cpp
 // Description: Unit test for the Customer class
 // 
 // Version History:
 // 2.0 2024-07-18 - Second Version
 ///

#include <iostream>
#include "Customer.h"

int main() {
    // Create a Customer object
    Customer customer("John Doe", "123-456-7890", "johndoe@example.com");

    // Test getCustomerName() function
    std::string expectedName = "John Doe";
    std::string returnedName = customer.getCustomerName();
    std::cout << "Testing getCustomerName(): " << expectedName << " vs " << returnedName << std::endl;
    assert(expectedName == returnedName);
    std::cout << "Unit test of getCustomerName(): Passed" << std::endl;

    // Test getPhone() function
    std::string expectedPhone = "123-456-7890";
    std::string returnedPhone = customer.getPhone();
    std::cout << "Testing getPhone(): " << expectedPhone << " vs " << returnedPhone << std::endl;
    assert(expectedPhone == returnedPhone);
    std::cout << "Unit test of getPhone(): Passed" << std::endl;

    // Test getEmail() function
    std::string expectedEmail = "johndoe@example.com";
    std::string returnedEmail = customer.getEmail();
    std::cout << "Testing getEmail(): " << expectedEmail << " vs " << returnedEmail << std::endl;
    assert(expectedEmail == returnedEmail);
    std::cout << "Unit test of getEmail(): Passed" << std::endl;

    // Test setCustomerName() function
    std::string newName = "Jane Doe";
    customer.setCustomerName(newName);
    returnedName = customer.getCustomerName();
    std::cout << "Testing setCustomerName(): " << newName << " vs " << returnedName << std::endl;
    assert(newName == returnedName);
    std::cout << "Unit test of setCustomerName(): Passed" << std::endl;

    // Test setPhone() function
    std::string newPhone = "098-765-4321";
    customer.setPhone(newPhone);
    returnedPhone = customer.getPhone();
    std::cout << "Testing setPhone(): " << newPhone << " vs " << returnedPhone << std::endl;
    assert(newPhone == returnedPhone);
    std::cout << "Unit test of setPhone(): Passed" << std::endl;

    // Test setEmail() function
    std::string newEmail = "janedoe@example.com";
    customer.setEmail(newEmail);
    returnedEmail = customer.getEmail();
    std::cout << "Testing setEmail(): " << newEmail << " vs " << returnedEmail << std::endl;
    assert(newEmail == returnedEmail);
    std::cout << "Unit test of setEmail(): Passed" << std::endl;

    // Test setIsEmployee() and getIsEmployee() functions
    bool expectedIsEmployee = true;
    customer.setIsEmployee(expectedIsEmployee);
    bool returnedIsEmployee = customer.getIsEmployee();
    std::cout << "Testing setIsEmployee() and getIsEmployee(): " << expectedIsEmployee << " vs " << returnedIsEmployee << std::endl;
    assert(expectedIsEmployee == returnedIsEmployee);
    std::cout << "Unit test of setIsEmployee() and getIsEmployee(): Passed" << std::endl;

    // Test setDepartment() and getDepartment() functions
    std::string expectedDepartment = "Engineering";
    customer.setDepartment(expectedDepartment);
    std::string returnedDepartment = customer.getDepartment();
    std::cout << "Testing setDepartment() and getDepartment(): " << expectedDepartment << " vs " << returnedDepartment << std::endl;
    assert(expectedDepartment == returnedDepartment);
    std::cout << "Unit test of setDepartment() and getDepartment(): Passed" << std::endl;

    std::cout << "All tests passed!" << std::endl;
}
