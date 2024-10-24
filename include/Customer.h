/// 
 // Filename: Customer.h
 // Description: Header file for the Customer class
 // 
 // Version History:
 // 1.0 2024-07-02 - Initial version
 ///

#pragma once

#include <string>
#include "Customer.h"

class Customer {
public:
    //===============================================================================
    // Constructor
    // Default Constructor
    Customer();
    
    //===============================================================================
    // Parameterized Constructor - initializes Customer instance with given parameters
    // @param name - Name of Customer (taken by reference)
    // @param phone - Phone number of Customer (taken by reference)
    // @param email - Email address of Customer (taken by reference)
    Customer(const std::string &name, const std::string &phone, const std::string &email);

    //===============================================================================
    // Getters - all const as they do not change anything

    // Gets Customer name of a particular instance
    // @return - returns associated string of Customer name 
    std::string getCustomerName() const;
    
    //===============================================================================
    // Gets Customer phone number of a particular instance
    // @return - returns associated string of Customer phone number 
    std::string getPhone() const;

    //===============================================================================
    // Gets Customer email address of a particular instance
    // @return - returns associated string of Customer email address 
    std::string getEmail() const;
    
    //===============================================================================
    // Gets whether the Customer is an employee
    // @return - returns true if the Customer is an employee, false otherwise
    bool getIsEmployee() const;

    //===============================================================================
    // Gets the department of the Customer if they are an employee
    // @return - returns associated string of Customer department, empty if not an employee
    std::string getDepartment() const;

    //===============================================================================
    // Setters - no const promise because they change attributes

    // Sets Customer name of a particular instance
    // @param name - Name of Customer (taken by reference)
    // @return - returns true if successful, false otherwise
    bool setCustomerName(const std::string &name);

    //===============================================================================
    // Sets Customer phone number of a particular instance
    // @param phone - Phone number of Customer (taken by reference)
    // @return - returns true if successful, false otherwise
    bool setPhone(const std::string &phone);

    //===============================================================================
    // Sets Customer email address of a particular instance
    // @param email - Email address of Customer (taken by reference)
    // @return - returns true if successful, false otherwise
    bool setEmail(const std::string &email);

    //===============================================================================
    // Sets whether the Customer is an employee
    // @param isEmployee - Boolean indicating if the Customer is an employee
    // @return - returns true if successful, false otherwise
    bool setIsEmployee(bool isEmployee);

    //===============================================================================
    // Sets the department of the Customer if they are an employee
    // Preconditions: Customer has to be an employee!
    // @param department - Department of Customer (taken by reference)
    // @return - returns true if successful, false otherwise
    bool setDepartment(const std::string &department);

    //===============================================================================
    // File operations

    // Opens the file for writing
    // @param filename - The name of the file to open
    // @return True if the file was successfully opened, false otherwise
    static bool openWriteFile(const std::string& fileName);

    //===============================================================================
    // Opens the file for reading
    // @param fileName - The name of the file to open
    // @return True if the file was successfully opened, false otherwise
    static bool openReadFile(const std::string& fileName);

    //===============================================================================
    // Closes the currently open file
    static void closeWriteFile();

    //===============================================================================
    // Closes the currently open file
    static void closeReadFile();

    //===============================================================================
    // Writes a Customer object to the file
    // @param - customerObject - The Customer object to write
    // @return - True if the write operation was successful, false otherwise
    static bool Customer::writeCustomer(Customer& customerObject);

    //===============================================================================
    // Moves the file cursor to the beginning of the file
    static void seekToBeginningOfFile();

    //===============================================================================
    // Reads the next Customer object from the file
    // @param customerObject - The Customer object to fill with data from the file
    // @return - True if a record was successfully read, false if the end of the file was reached
    static bool getNext(Customer& customerObject, int index);

    //===============================================================================
    // Deletes a specific Customer record from the file
    // @param customerName - The name of the Customer to delete
    // @return - True if the record was successfully deleted, false otherwise
    static bool deleteCustomerRecord(std::string customerName);

    //===============================================================================
    // Finds a specific Customer record in the file
    // @param customerName - The Name of the release to find
    // @return customerObject - The object with data if found; otherwise empty Object (customerName = "")
    static Customer findCustomerRecord(std::string customerName);

private:
    char customerName[150];  // The name of the customer
    char phone[100];  // The phone number of the customer
    char email[150];  // The email address of the customer
    bool isEmployee;  // Indicates if the customer is an employee
    char department[100];  // The department of the customer, empty string if not an employee

    static std::string fileName;  // The name of the currently open file

    static std::ofstream fout;    // stream for writing to files
    static std::fstream fin;      // stream for reading to files
};

