/// 
// Filename: Request.cpp
// Description: Implementation file for the Request class
// 
// Version History:
// 1.0 2024-07-02 - Initial version
///

#include <stdexcept>
#include <sstream>
#include <iostream>
#include <cstring>
#include "Request.h"

// Define and initialize the static member variables
std::string Request::fileName = "request_default.dat";  // set a default fileName

std::ofstream Request::fout;
std::fstream Request::fin;

int Request::requestIDCount = 0;

//===============================================================================
// Constructor
// Default constructor initializes an empty Request object
Request::Request() : changeRequestID(0), productID(0), releaseID(-1) {
    // each working with attributes - eg. description refers to this->description
    std::memset(description, 0, sizeof(description));
    std::memset(status, 0, sizeof(status));
    std::memset(priority, 0, sizeof(priority));
    std::memset(dateOfRequest, 0, sizeof(dateOfRequest));
    std::memset(customerName, 0, sizeof(customerName));
}

//===============================================================================
// Parameterized constructor initializes a Request object with specific details
// @param requestID - The ID of the request
// @param description - Description of the request
// @param priority - Priority of the request
// @param status - Status of the request
// @param dateOfRequest - Date the request was made
// @param productID - ID of the related product
// @param customerName - Name of the customer making the request
// @param releaseID - ID of the Release associated with the product (nullable)
Request::Request(int changeRequestID, const std::string& description, const std::string& priority, 
                 const std::string& status, const std::string& dateOfRequest, int productID, 
                 const std::string& customerName, int releaseID)
    : changeRequestID(++requestIDCount), productID(productID), releaseID(releaseID) {
    // explicitly using this->description to avoid confusion with arguments
    std::strncpy(this->description, description.c_str(), sizeof(this->description) - 1);
    std::strncpy(this->status, status.c_str(), sizeof(this->status) - 1);
    std::strncpy(this->priority, priority.c_str(), sizeof(this->priority) - 1);
    std::strncpy(this->dateOfRequest, dateOfRequest.c_str(), sizeof(this->dateOfRequest) - 1);
    std::strncpy(this->customerName, customerName.c_str(), sizeof(this->customerName) - 1);
}

//===============================================================================
// Getters - all const as they do not change anything

// Gets the change request ID
// @return - returns the associated integer request ID
int Request::getRequestID() const {
    return changeRequestID;
}

//===============================================================================
// Gets the description of the request
// @return - returns the associated string description
std::string Request::getDescription() const {
    return description;
}

//===============================================================================
// Gets the priority of the request
// @return - returns the associated string priority
std::string Request::getPriority() const {
    return priority;
}

//===============================================================================
// Gets the status of the request
// @return - returns the associated string status
std::string Request::getStatus() const {
    return status;
}

//===============================================================================
// Gets the date of the request
// @return - returns the associated string date of request
std::string Request::getDateOfRequest() const {
    return dateOfRequest;
}

//===============================================================================
// Gets the product ID related to the request
// @return - returns the associated integer product ID
int Request::getProductID() const {
    return productID;
}

//===============================================================================
// Gets the name of the customer making the request
// @return - returns the associated string customer name
std::string Request::getCustomerName() const {
    return customerName;
}

//===============================================================================
// Gets the release ID related to the request
// @return - returns the associated integer release ID, or -1 if not set
int Request::getReleaseID() const {
    return releaseID;
}

//===============================================================================
// Setters - no const promise because they change attributes

// Sets the change request ID
// @param changeRequestID - The change request ID to set
// @return - returns true if successful, false otherwise
bool Request::setRequestID(int requestID) {
    changeRequestID = requestID;
    return true;
}

//===============================================================================
// Sets the description of the request
// @param description - The description to set
// @return - returns true if successful, false otherwise
bool Request::setDescription(const std::string& description) {
    if (description.size() >= sizeof(this->description)) {
        return false; // Input string too long
    }
    std::strncpy(this->description, description.c_str(), sizeof(this->description) - 1);
    this->description[sizeof(this->description) - 1] = '\0'; // Ensure null-termination
    return true;
}

//===============================================================================
// Sets the priority of the request
// @param priority - The priority to set
// @return - returns true if successful, false otherwise
bool Request::setPriority(const std::string& priority) {
    if (priority.size() >= sizeof(this->priority)) {
        return false; // Input string too long
    }
    std::strncpy(this->priority, priority.c_str(), sizeof(this->priority) - 1);
    this->priority[sizeof(this->priority) - 1] = '\0'; // Ensure null-termination
    return true;
}

//===============================================================================
// Sets the status of the request
// @param status - The status to set
// @return - returns true if successful, false otherwise
bool Request::setStatus(const std::string& status) {
    if (status.size() >= sizeof(this->status)) {
        return false; // Input string too long
    }
    std::strncpy(this->status, status.c_str(), sizeof(this->status) - 1);
    this->status[sizeof(this->status) - 1] = '\0'; // Ensure null-termination
    return true;
}

//===============================================================================
// Sets the date of the request
// @param dateOfRequest - The date of request to set
// @return - returns true if successful, false otherwise
bool Request::setDateOfRequest(const std::string& dateOfRequest) {
    if (dateOfRequest.size() >= sizeof(this->dateOfRequest)) {
        return false; // Input string too long
    }
    std::strncpy(this->dateOfRequest, dateOfRequest.c_str(), sizeof(this->dateOfRequest) - 1);
    this->dateOfRequest[sizeof(this->dateOfRequest) - 1] = '\0'; // Ensure null-termination
    return true;
}

//===============================================================================
// Sets the product ID related to the request
// @param productID - The product ID to set
// @return - returns true if successful, false otherwise
bool Request::setProductID(int productID) {
    this->productID = productID;
    return true;
}

//===============================================================================
// Sets the name of the customer making the request
// @param customerName - The customer name to set
// @return - returns true if successful, false otherwise
bool Request::setCustomerName(const std::string& customerName) {
    if (customerName.size() >= sizeof(this->customerName)) {
        return false; // Input string too long
    }
    std::strncpy(this->customerName, customerName.c_str(), sizeof(this->customerName) - 1);
    this->customerName[sizeof(this->customerName) - 1] = '\0'; // Ensure null-termination
    return true;
}

//===============================================================================
// Sets the release ID related to the request
// @param releaseID - The release ID to set
// @return - returns true if successful, false otherwise
bool Request::setReleaseID(int releaseID) {
    this->releaseID = releaseID;
    return true;
}

//===============================================================================
// File operations

// Opens the file for writing
// @param fileName - The name of the file to open
// @return True if the file was successfully opened, false otherwise
bool Request::openWriteFile(const std::string& fileName) {
    Request::fileName = fileName;
    Request::fout.clear();
    Request::fout.flush();
    Request::fout.open(Request::fileName, std::ios::out | std::ios::binary | std::ios::app);
    return Request::fout.is_open();
}

//===============================================================================
// Opens the file for reading
// @param fileName - The name of the file to open
// @return True if the file was successfully opened, false otherwise
bool Request::openReadFile(const std::string& fileName)
{
    Request::fileName = fileName;
    Request::fin.clear();
    Request::fin.open(Request::fileName, std::ios::in | std::ios::binary);
    return Request::fin.is_open();

}

//===============================================================================
// Closes the currently open file
void Request::closeWriteFile() {
    if (Request::fout.is_open()) {
        Request::fout.close();
    }
}

//===============================================================================
// Closes the currently open file
void Request::closeReadFile()
{
    if (Request::fin.is_open()) {
        Request::fin.close();
    }
}

//===============================================================================
// Writes a Request object to the file
// @param requestObject - The Request object to write
// @return - True if the write operation was successful, false otherwise
bool Request::writeRequest(Request& requestObject) {
    if (!openWriteFile("E:/SFU/Cmpt276/Assignment4_VS/Bug_Report/src/request.dat")) {
        std::cout << "Could not open Request Write file" << std::endl;
        return false;
    }

    if (!Request::fout.good()) {
        std::cout << "Problem" << std::endl;
    }
    else {
        Request::fout.write(reinterpret_cast<char*>(&requestObject), sizeof(Request));
    }

    if (!Request::fout.good()) {
        std::cerr << "Error writing to file: request.dat" << std::endl;
        closeWriteFile();
        return false;
    }

    closeWriteFile();
    std::cout << "Data written to Request file successfully." << std::endl;

    writeLastID();      // save the most recent ID

    return true;
}

//===============================================================================
// Moves the file cursor to the beginning of the file
void Request::seekToBeginningOfFile() {
    if (Request::fin.is_open()) {
        Request::fin.seekg(0, std::ios::beg);
    }
}

//===============================================================================
// Reads the next Request object from the file
// @param requestObject - The Request object to fill with data from the file
// @param index - The record number to read
// @return - True if a record was successfully read, false if the end of the file was reached
bool Request::getNext(Request& requestObject, int index) {
    if (!openReadFile("E:/SFU/Cmpt276/Assignment4_VS/Bug_Report/src/request.dat")) {
        std::cout << "Could not open Request Read file" << std::endl;
        return false;
    }

    if (!Request::fin.is_open()) {
        std::cout << "Error opening file for Request read" << std::endl;
    }

    Request::fin.seekg(index * sizeof(Request), std::ios::beg);
    Request::fin.read(reinterpret_cast<char*>(&requestObject), sizeof(Request));

    if (Request::fin.eof()) {
        std::cout << "End of file reached prematurely (Request)" << std::endl;
        closeReadFile();
        return false;
    }

    if (Request::fin.fail()) {
        std::cout << "Error reading data from: request.dat" << std::endl;
        closeReadFile();
        return false;
    }

    closeReadFile();
    return true;
}

//===============================================================================
// Deletes a specific Request record from the file
// @param changeRequestID - The ID of the request to delete
// @return - True if the record was successfully deleted, false otherwise
bool Request::deleteRequestRecord(int changeRequestID) {
    int num = 1;
    if (Request::fin.is_open()) {
        std::fstream tempFile("temp.dat", std::ios::out | std::ios::binary);
        Request tempRequest;
        bool found = false;

        seekToBeginningOfFile();
        while (getNext(tempRequest, num)) {
            if (tempRequest.getProductID() != changeRequestID) {
                tempFile.write(reinterpret_cast<const char*>(&tempRequest), sizeof(Request));
            }
            else {
                found = true;
            }
            num++;
        }

        Request::fin.close();
        tempFile.close();

        remove(fileName.c_str());
        rename("temp.dat", fileName.c_str());

        openWriteFile(fileName);
        return found;
    }
    return false;
}

//===============================================================================
// Finds a specific Request record in the file
// @param changeRequestID - The ID of the request to find
// @param requestObject - The Request object to fill with data if found
// @return - True if the record was found, false otherwise
Request Request::findRequestRecord(int changeRequestID) {
    Request requestObj;
    seekToBeginningOfFile();
    int num = 0;
    while (getNext(requestObj, num)) {
        if (requestObj.getRequestID() == changeRequestID) {
            return requestObj;
        }
        ++num;
    }
    return requestObj;
}

//===============================================================================
// Static method to read the last ID from a file
void Request::readLastID() {
    std::ifstream fin("E:/SFU/Cmpt276/Assignment4_VS/Bug_Report/src/id.dat", std::ios::in | std::ios::binary);
    if (fin.is_open()) {
        fin.seekg(sizeof(requestIDCount), std::ios::beg);
        fin.read(reinterpret_cast<char*>(&requestIDCount), sizeof(requestIDCount));
        fin.close();
    }
}

//===============================================================================
// Static method to write the current ID to a file
void Request::writeLastID() {
    std::ofstream fout("E:/SFU/Cmpt276/Assignment4_VS/Bug_Report/src/id.dat", std::ios::out | std::ios::binary);
    if (fout.is_open()) {
        fout.seekp(sizeof(requestIDCount), std::ios::beg);
        fout.write(reinterpret_cast<const char*>(&requestIDCount), sizeof(requestIDCount));
        fout.close();
    }
}
