/// 
// Filename: Customer.cpp
// Description: Implementation file for the Customer class
// 
// Version History:
// 1.0 2024-07-02 - Initial version
///

#include <fstream>
#include <iostream>
#include "Customer.h"

// Initialize static members
std::string Customer::fileName = "bug_default.dat";  // You can set a default filename

std::ofstream Customer::fout;
std::fstream Customer::fin;

Customer::Customer() : isEmployee(false)
{
    // referring to attributes - eg. this->version
    std::memset(customerName, 0, sizeof(customerName));
    std::memset(phone, 0, sizeof(phone));
    std::memset(email, 0, sizeof(email));
    std::memset(department, 0, sizeof(department));
}

// Constructor - parameterized
Customer::Customer(const std::string &name, const std::string &phone, const std::string &email)
    : isEmployee(false) {
    // explicitly using this->description to avoid confusion with arguments
    std::strncpy(this->customerName, name.c_str(), sizeof(this->customerName) - 1);
    std::strncpy(this->phone, phone.c_str(), sizeof(this->phone) - 1);
    std::strncpy(this->email, email.c_str(), sizeof(this->email) - 1);
    std::memset(department, 0, sizeof(department));         // Initially empty; have to set up manually
}

// Getters
std::string Customer::getCustomerName() const {
    return customerName;
}

std::string Customer::getPhone() const {
    return phone;
}

std::string Customer::getEmail() const {
    return email;
}

bool Customer::getIsEmployee() const {
    return isEmployee;
}

std::string Customer::getDepartment() const {
    return isEmployee ? department : "";
}

// Setters
bool Customer::setCustomerName(const std::string& name) {
    if (name.size() >= sizeof(this->customerName)) {
        return false; // Input string too long
    }
    std::strncpy(this->customerName, name.c_str(), sizeof(this->customerName) - 1);
    this->customerName[sizeof(this->customerName) - 1] = '\0'; // Ensure null-termination
    return true;
}

bool Customer::setPhone(const std::string& phone) {
    if (phone.size() >= sizeof(this->phone)) {
        return false; // Input string too long
    }
    std::strncpy(this->phone, phone.c_str(), sizeof(this->phone) - 1);
    this->phone[sizeof(this->phone) - 1] = '\0'; // Ensure null-termination
    return true;
}

bool Customer::setEmail(const std::string& email) {
    if (email.size() >= sizeof(this->email)) {
        return false; // Input string too long
    }
    std::strncpy(this->email, email.c_str(), sizeof(this->email) - 1);
    this->email[sizeof(this->email) - 1] = '\0'; // Ensure null-termination
    return true;
}

bool Customer::setIsEmployee(bool isEmployee) {
    this->isEmployee = isEmployee;
    if (!isEmployee) {
        std::memset(this->department, 0, sizeof(this->department)); // Clear department if not an employee
    }
    return true;
}

bool Customer::setDepartment(const std::string& department) {
    if (isEmployee) {
        if (department.size() >= sizeof(this->department)) {
            return false; // Input string too long
        }
        std::strncpy(this->department, department.c_str(), sizeof(this->department) - 1);
        this->department[sizeof(this->department) - 1] = '\0'; // Ensure null-termination
        return true;
    }
    return false;
}

// File Operations

bool Customer::openWriteFile(const std::string& fileName) {
    Customer::fileName = fileName;
    Customer::fout.clear();
    Customer::fout.flush();
    Customer::fout.open(Customer::fileName, std::ios::out | std::ios::binary | std::ios::app);
    return Customer::fout.is_open();
}

bool Customer::openReadFile(const std::string& fileName)
{
    Customer::fileName = fileName;
    Customer::fin.clear();
    Customer::fin.open(Customer::fileName, std::ios::in | std::ios::binary);
    return Customer::fin.is_open();
}


void Customer::closeWriteFile() {
    if (Customer::fout.is_open()) {
        Customer::fout.close();
    }
}

void Customer::closeReadFile()
{
    if (Customer::fin.is_open()) {
        Customer::fin.close();
    }
}


// Expectations: opens the files and closes the file after writing
bool Customer::writeCustomer(Customer& customerObject) {
    if (!openWriteFile("E:/SFU/Cmpt276/Assignment4_VS/Bug_Report/src/customer.dat")) {       // TODO: Refractor path to static variable; path should also be relative
        std::cout << "Could not open Customer Write file" << std::endl;
        return false;
    }

    if (!Customer::fout.good()) {
        std::cout << "Problem with Customer File" << std::endl;
    }
    else {
        Customer::fout.write(reinterpret_cast<char*>(&customerObject), sizeof(Customer));
    }

    if (!Customer::fout.good()) {
        std::cerr << "Error writing to file: customer.dat" << std::endl;
        closeWriteFile();
        return false;
    }

    closeWriteFile();
    std::cout << "Data written to Customer file successfully." << std::endl;
    return true;
}

void Customer::seekToBeginningOfFile() {
    if (Customer::fin.is_open()) {
        Customer::fin.seekg(0, std::ios::beg);
    }
}


bool Customer::getNext(Customer& customerObject, int index) {
    if (!openReadFile("E:/SFU/Cmpt276/Assignment4_VS/Bug_Report/src/customer.dat")) {
        std::cout << "Could not open Customer Read file" << std::endl;
        return false;
    }

    if (!Customer::fin.is_open()) {
        std::cout << "Error opening file for Customer read" << std::endl;
    }

    Customer::fin.seekg(index * sizeof(Customer), std::ios::beg);
    if (fin.fail()) {
        std::cerr << "Error seeking to position" << std::endl;
        closeReadFile();
        return false;
    }

    Customer::fin.read(reinterpret_cast<char*>(&customerObject), sizeof(Customer));

    if (Customer::fin.eof()) {
        std::cout << "End of file reached (Customer)" << std::endl;
        closeReadFile();
        return false;
    }

    if (Customer::fin.fail()) {
        std::cout << "Error reading data from: customer.dat" << std::endl;
        closeReadFile();
        return false;
    }

    closeReadFile();
    return true;
}

bool Customer::deleteCustomerRecord(std::string customerName) {
    // This would be more complex in a real system, involving marking a record as deleted
    // or re-writing the file without the deleted record
    return false; // Placeholder implementation
}

Customer Customer::findCustomerRecord(std::string customerName) {
    Customer customerObj;
    int num = 0;
    seekToBeginningOfFile();
    while (getNext(customerObj, num)) {
        if (customerObj.getCustomerName() == customerName) {
            return customerObj;
        }
        ++num;
    }
    return Customer("", "", "");    // Ensure everything is empty - allows for not found check
}
