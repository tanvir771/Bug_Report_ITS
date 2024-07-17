/// 
// Filename: Employee.cpp
// Description: Implementation file for the Employee class
// 
// Version History:
// 1.0 2024-07-02 - Initial version
///

#include "Employee.h"

// Constructor
Employee::Employee(const std::string &name, const std::string &phone, const std::string &role)
    : name(name), phone(phone), role(role) {
    // Assuming email can be generated based on the name and a domain
    email = name + "@company.com"; // Simple email generation logic
}

// Getters
std::string Employee::getName() const {
    return name;
}

std::string Employee::getPhone() const {
    return phone;
}

std::string Employee::getEmail() const {
    return email;
}

std::string Employee::getRole() const {
    return role;
}
