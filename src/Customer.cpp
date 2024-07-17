/// 
// Filename: Customer.cpp
// Description: Implementation file for the Customer class
// 
// Version History:
// 1.0 2024-07-02 - Initial version
///

#include "Customer.h"
#include <fstream>

// Initialize static members
std::fstream Customer::file;
std::string Customer::filename = "customer_default.dat";

Customer::Customer() : customerName(""), phone(""), email(""), isEmployee(false), department("")
{
}

// Constructor - parameterized
Customer::Customer(const std::string &name, const std::string &phone, const std::string &email)
    : customerName(name), phone(phone), email(email), isEmployee(false), department("") {}

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
bool Customer::setCustomerName(const std::string &name) {
    customerName = name;
    return true;
}

bool Customer::setPhone(const std::string &phone) {
    this->phone = phone;
    return true;
}

bool Customer::setEmail(const std::string &email) {
    this->email = email;
    return true;
}

bool Customer::setIsEmployee(bool isEmployee) {
    this->isEmployee = isEmployee;
    if (!isEmployee) {
        department = "";
    }
    return true;
}

bool Customer::setDepartment(const std::string &department) {
    if (isEmployee) {
        this->department = department;
        return true;
    }
    return false;
}

// File operations
bool Customer::openReleaseFile(const std::string& filename) {
    Customer::filename = filename;
    file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    return file.is_open();
}

void Customer::closeCustomerFile() {
    if (file.is_open()) {
        file.close();
    }
}

bool Customer::writeCustomer(const Customer& customerObject) {
    if (!file.is_open()) return false;
    file.write(reinterpret_cast<const char*>(&customerObject), sizeof(Customer));
    return file.good();
}

void Customer::seekToBeginningOfFile() {
    if (file.is_open()) {
        file.seekg(0, std::ios::beg);
    }
}

bool Customer::getNext(Customer& customerObject) {
    if (!file.is_open()) return false;
    file.read(reinterpret_cast<char*>(&customerObject), sizeof(Customer));
    return file.gcount() == sizeof(Customer);
}

bool Customer::deleteCustomerRecord(std::string customerName) {
    // This would be more complex in a real system, involving marking a record as deleted
    // or re-writing the file without the deleted record
    return false; // Placeholder implementation
}

Customer Customer::findCustomerRecord(std::string customerName) {
    Customer customerObj;
    seekToBeginningOfFile();
    while (getNext(customerObj)) {
        if (customerObj.getCustomerName() == customerName) {
            return customerObj;
        }
    }
    return customerObj;
}
