/// 
 // Filename: Employee.h
 // Description: Header file for the Employee class
 // 
 // Version History:
 // 1.0 2024-07-02 - Initial version
 ///

#pragma once

#include <string>

class Employee {
public:
    // Constructor
    Employee(const std::string &name, const std::string &phone, const std::string &role);

    // Getters
    std::string getName() const;
    std::string getPhone() const;
    std::string getEmail() const;
    std::string getRole() const;

private:
    std::string name;
    std::string phone;
    std::string email;
    std::string role;
};
