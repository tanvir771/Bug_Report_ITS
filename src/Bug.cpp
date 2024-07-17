/// 
// Filename: Bug.cpp
// Description: Implementation file for the Bug class
// 
// Version History:
// 1.0 2024-07-02 - Initial version
///

#include "Bug.h"

// Define and initialize the static member variables
std::fstream Bug::file;  // Default initialization
std::string Bug::filename = "bug_default.dat";  // You can set a default filename

// Constructor - default
Bug::Bug() : bugID(0), description(""), severity(""), status(""), productReleaseID(0) {}

// Parameterized constructor
Bug::Bug(int bugID, const std::string& description, const std::string& severity, 
         const std::string& status, int productReleaseID)
    : bugID(bugID), description(description), severity(severity), status(status), productReleaseID(productReleaseID) {}

// Getters
int Bug::getBugID() const {
    return bugID;
}

std::string Bug::getDescription() const {
    return description;
}

std::string Bug::getSeverity() const {
    return severity;
}

std::string Bug::getStatus() const {
    return status;
}

int Bug::getProductReleaseID() const {
    return productReleaseID;
}

// Setters
bool Bug::setBugID(int bugID) {
    this->bugID = bugID;
    return true;
}

bool Bug::setDescription(const std::string& description) {
    this->description = description;
    return true;
}

bool Bug::setSeverity(const std::string& severity) {
    this->severity = severity;
    return true;
}

bool Bug::setStatus(const std::string& status) {
    this->status = status;
    return true;
}

bool Bug::setProductReleaseID(int productReleaseID) {
    this->productReleaseID = productReleaseID;
    return true;
}

// File operations
bool Bug::openBugFile(const std::string& filename) {
    Bug::filename = filename;
    file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    return file.is_open();
}

void Bug::closeBugFile() {
    if (file.is_open()) {
        file.close();
    }
}

bool Bug::writeBug(const Bug& bugObject) {
    if (!file.is_open()) return false;
    file.write(reinterpret_cast<const char*>(&bugObject), sizeof(Bug));
    return file.good();
}

void Bug::seekToBeginningOfFile() {
    if (file.is_open()) {
        file.seekg(0, std::ios::beg);
    }
}

bool Bug::getNext(Bug& bugObject) {
    if (!file.is_open()) return false;
    file.read(reinterpret_cast<char*>(&bugObject), sizeof(Bug));
    return file.gcount() == sizeof(Bug);
}

bool Bug::deleteBugRecord(int bugID) {
    // This would be more complex in a real system, involving marking a record as deleted
    // or re-writing the file without the deleted record
    return false; // Placeholder implementation
}

Bug Bug::findBugRecord(int bugID) {
    Bug bugObj;
    seekToBeginningOfFile();
    while (getNext(bugObj)) {
        if (bugObj.getBugID() == bugID) {
            return bugObj;
        }
    }
    return bugObj;
}