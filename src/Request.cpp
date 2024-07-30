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

// Constructors
Request::Request() : changeRequestID(0), productID(0), releaseID(-1) {
    // each working with attributes - eg. description refers to this->description
    std::memset(description, 0, sizeof(description));
    std::memset(status, 0, sizeof(status));
    std::memset(priority, 0, sizeof(priority));
    std::memset(dateOfRequest, 0, sizeof(dateOfRequest));
    std::memset(customerName, 0, sizeof(customerName));
}

Request::Request(int changeRequestID, const std::string& description, const std::string& priority, 
                 const std::string& status, const std::string& dateOfRequest, int productID, 
                 const std::string& customerName, int releaseID)
    : changeRequestID(changeRequestID), productID(productID), releaseID(releaseID) {
    // explicitly using this->description to avoid confusion with arguments
    std::strncpy(this->description, description.c_str(), sizeof(this->description) - 1);
    std::strncpy(this->status, status.c_str(), sizeof(this->status) - 1);
    std::strncpy(this->priority, priority.c_str(), sizeof(this->priority) - 1);
    std::strncpy(this->dateOfRequest, dateOfRequest.c_str(), sizeof(this->dateOfRequest) - 1);
    std::strncpy(this->customerName, customerName.c_str(), sizeof(this->customerName) - 1);
}

// Getters
int Request::getRequestID() const {
    return changeRequestID;
}

std::string Request::getDescription() const {
    return description;
}

std::string Request::getPriority() const {
    return priority;
}

std::string Request::getStatus() const {
    return status;
}

std::string Request::getDateOfRequest() const {
    return dateOfRequest;
}

int Request::getProductID() const {
    return productID;
}

std::string Request::getCustomerName() const {
    return customerName;
}

int Request::getReleaseID() const {
    return releaseID;
}

// Setters
bool Request::setRequestID(int requestID) {
    changeRequestID = requestID;
    return true;
}

bool Request::setDescription(const std::string& description) {
    if (description.size() >= sizeof(this->description)) {
        return false; // Input string too long
    }
    std::strncpy(this->description, description.c_str(), sizeof(this->description) - 1);
    this->description[sizeof(this->description) - 1] = '\0'; // Ensure null-termination
    return true;
}

bool Request::setPriority(const std::string& priority) {
    if (priority.size() >= sizeof(this->priority)) {
        return false; // Input string too long
    }
    std::strncpy(this->priority, priority.c_str(), sizeof(this->priority) - 1);
    this->priority[sizeof(this->priority) - 1] = '\0'; // Ensure null-termination
    return true;
}

bool Request::setStatus(const std::string& status) {
    if (status.size() >= sizeof(this->status)) {
        return false; // Input string too long
    }
    std::strncpy(this->status, status.c_str(), sizeof(this->status) - 1);
    this->status[sizeof(this->status) - 1] = '\0'; // Ensure null-termination
    return true;
}

bool Request::setDateOfRequest(const std::string& dateOfRequest) {
    if (dateOfRequest.size() >= sizeof(this->dateOfRequest)) {
        return false; // Input string too long
    }
    std::strncpy(this->dateOfRequest, dateOfRequest.c_str(), sizeof(this->dateOfRequest) - 1);
    this->dateOfRequest[sizeof(this->dateOfRequest) - 1] = '\0'; // Ensure null-termination
    return true;
}

bool Request::setProductID(int productID) {
    this->productID = productID;
    return true;
}

bool Request::setCustomerName(const std::string& customerName) {
    if (customerName.size() >= sizeof(this->customerName)) {
        return false; // Input string too long
    }
    std::strncpy(this->customerName, customerName.c_str(), sizeof(this->customerName) - 1);
    this->customerName[sizeof(this->customerName) - 1] = '\0'; // Ensure null-termination
    return true;
}

bool Request::setReleaseID(int releaseID) {
    this->releaseID = releaseID;
    return true;
}

// File operations
bool Request::openWriteFile(const std::string& fileName) {
    Request::fileName = fileName;
    Request::fout.clear();
    Request::fout.flush();
    Request::fout.open(Request::fileName, std::ios::out | std::ios::binary | std::ios::app);
    return Request::fout.is_open();
}

bool Request::openReadFile(const std::string& fileName)
{
    Request::fileName = fileName;
    Request::fin.clear();
    Request::fin.open(Request::fileName, std::ios::in | std::ios::binary);
    return Request::fin.is_open();
}


void Request::closeWriteFile() {
    if (Request::fout.is_open()) {
        Request::fout.close();
    }
}

void Request::closeReadFile()
{
    if (Request::fin.is_open()) {
        Request::fin.close();
    }
}

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
    return true;
}

void Request::seekToBeginningOfFile() {
    if (Request::fin.is_open()) {
        Request::fin.seekg(0, std::ios::beg);
    }
}

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

Request Request::findRequestRecord(int changeRequestID) {
    Request requestObj;
    seekToBeginningOfFile();
    int num = 0;
    while (getNext(requestObj, num)) {
        if (requestObj.getRequestID() == changeRequestID) {
            num++;
            return requestObj;
        }
    }
    return requestObj;
}

//Bug Request::convertToBug() const {
//    if (description.empty() || priority.empty() || status.empty() || productID == 0 || releaseID == -1) {
//        throw std::invalid_argument("Insufficient information to convert Request to Bug");
//    }
//    return Bug(changeRequestID, description, priority, status, productID, releaseID);
//}
