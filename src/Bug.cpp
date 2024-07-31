/// 
// Filename: Bug.cpp
// Description: Implementation file for the Bug class
// 
// Version History:
// 1.0 2024-07-02 - Initial version
///

#include <iostream>
#include <cstring>
#include <iomanip>
#include "Bug.h"

// Define and initialize the static member variables
std::string Bug::fileName = "bug_default.dat";  // You can set a default filename

std::ofstream Bug::fout;
std::fstream Bug::fin;

std::ofstream Bug::tempFout;
std::fstream Bug::tempFin;

int Bug::bugIDCount = 0;

// Helper Printing Functions for Report Functions in Bug Class
void printBugTableHeader() {
    std::cout << std::setw(10) << std::right << "Bug ID"
        << std::setw(60) << std::right << "Description"
        << std::setw(20) << std::right << "Severity"
        << std::setw(20) << std::right << "Status"
        << std::setw(15) << std::right << "Product ID"
        << std::setw(15) << std::right << "Release ID" << std::endl;
    std::cout << std::string(140, '-') << std::endl;
}

void printBug(const Bug& bug) {
    std::cout << std::setw(10) << std::right << bug.getBugID()
        << std::setw(60) << std::right << bug.getDescription()
        << std::setw(20) << std::right << bug.getSeverity()
        << std::setw(20) << std::right << bug.getStatus()
        << std::setw(15) << std::right << bug.getProductID()
        << std::setw(15) << std::right << bug.getReleaseID() << std::endl;
}

// Constructor - default
// bugID set to zero - represents an empty object
Bug::Bug() : bugID(0), productID(0), releaseID(0) {
    std::memset(description, 0, sizeof(description));
    std::memset(severity, 0, sizeof(severity));
    std::memset(status, 0, sizeof(status));
}

// Parameterized constructor
Bug::Bug(int bugID, const std::string& desc, const std::string& sev, const std::string& stat, int productID, int releaseID)
    : bugID(++bugIDCount), productID(productID), releaseID(releaseID) 
{
    std::strncpy(description, desc.c_str(), sizeof(description) - 1);
    std::strncpy(severity, sev.c_str(), sizeof(severity) - 1);
    std::strncpy(status, stat.c_str(), sizeof(status) - 1);
    bugIDCount++;
}

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

int Bug::getProductID() const {
    return productID;
}

int Bug::getReleaseID() const
{
    return releaseID;
}

// Setters
bool Bug::setBugID(int bugID) {
    this->bugIDCount = bugID;
    return true;
}

bool Bug::setProductID(int productID)
{
    this->productID = productID;
    return true;
}

bool Bug::setReleaseID(int releaseID)
{
    this->releaseID = releaseID;
    return true;
}

bool Bug::setDescription(const std::string& description) {
    if (description.size() >= sizeof(this->description)) {
        return false;
    }
    std::strncpy(this->description, description.c_str(), sizeof(this->description) - 1);
    this->description[sizeof(this->description) - 1] = '\0';
    return true;
}

bool Bug::setSeverity(const std::string& severity) {
    if (severity.size() >= sizeof(this->severity)) {
        return false; // Input string too long
    }
    std::strncpy(this->severity, severity.c_str(), sizeof(this->severity) - 1);
    this->severity[sizeof(this->severity) - 1] = '\0'; // Ensure null-termination
    return true;
}

bool Bug::setStatus(const std::string& status) {
    if (status.size() >= sizeof(this->status)) {
        return false; // Input string too long
    }
    std::strncpy(this->status, status.c_str(), sizeof(this->status) - 1);
    this->status[sizeof(this->status) - 1] = '\0'; // Ensure null-termination
    return true;
}


// File operations
bool Bug::openWriteFile(const std::string& fileName) {
    Bug::fileName = fileName;
    Bug::fout.clear();
    Bug::fout.flush();
    Bug::fout.open(Bug::fileName, std::ios::out | std::ios::binary | std::ios::app);
    return Bug::fout.is_open();
}

bool Bug::openReadFile(const std::string& fileName)
{
    Bug::fileName = fileName;
    Bug::fin.clear();
    Bug::fin.open(Bug::fileName, std::ios::in | std::ios::binary);
    return Bug::fin.is_open();
}


void Bug::closeWriteFile() {
    if (Bug::fout.is_open()) {
        Bug::fout.close();
    }
}

void Bug::closeReadFile()
{
    if (Bug::fin.is_open()) {
        Bug::fin.close();
    }
}


// Expectations: opens the files and closes the file after writing
bool Bug::writeBug(Bug& bugObject) {
    if (!openWriteFile("E:/SFU/Cmpt276/Assignment4_VS/Bug_Report/src/bug.dat")) {       // TODO: Refractor path to static variable; path should also be relative
        std::cout << "Could not open Bug Write file" << std::endl;
        return false;
    }

    if (!Bug::fout.good()) {
        std::cout << "Problem" << std::endl;
    }
    else {
        Bug::fout.write(reinterpret_cast<char*>(&bugObject), sizeof(Bug));
    }

    if (!Bug::fout.good()) {
        std::cerr << "Error writing to file: bug.dat" << std::endl;
        closeWriteFile();
        return false;
    }

    closeWriteFile();
    std::cout << "Data written to Bug file successfully." << std::endl;

    writeLastID();      // Save last ID to separate file for later use

    return true;
}

void Bug::seekToBeginningOfFile() {
    if (Bug::fin.is_open()) {
        Bug::fin.seekg(0, std::ios::beg);
    }
}


// Reads the next Bug object from the file
// @param bugObject - The Bug object to fill with data from the file
// @param index - Starting at 0, it indicates which Bug item to retrieve
// @return - True if a record was successfully read, false if the end of the file was reached
bool Bug::getNext(Bug& bugObject, int index) {
    if (!openReadFile("E:/SFU/Cmpt276/Assignment4_VS/Bug_Report/src/bug.dat")) {
        std::cout << "Could not open Bug Read file" << std::endl;
        return false;
    }

    if (!Bug::fin.is_open()) {
        std::cout << "Error opening file for Bug read" << std::endl;
    }

    Bug::fin.seekg(index * sizeof(Bug), std::ios::beg);
    if (fin.fail()) {
        std::cerr << "Error seeking to position" << std::endl;
        closeReadFile();
        return false;
    }

    Bug::fin.read(reinterpret_cast<char*>(&bugObject), sizeof(Bug));

    if (Bug::fin.eof()) {
        std::cout << "End of file reached (Bug)" << std::endl;
        closeReadFile();
        return false;
    }

    if (Bug::fin.fail()) {
        std::cout << "Error reading data from: bug.dat" << std::endl;
        closeReadFile();
        return false;
    }

    closeReadFile();
    return true;
}

bool Bug::deleteBugRecord(int bugID) {
    // Open the main file for reading
    std::string tempFilename = "E:/SFU/Cmpt276/Assignment4_VS/Bug_Report/src/temp.dat";
    Bug::tempFout.clear();
    Bug::tempFout.flush();
    Bug::tempFout.open(tempFilename, std::ios::out | std::ios::binary | std::ios::app);

    if (!tempFout.is_open()) {
        std::cout << "Problem loading file" << std::endl;
        closeReadFile();
        return false;
    }

    Bug tempBug;
    int index = 0;
    bool found = true;

    seekToBeginningOfFile();
    while (getNext(tempBug, index)) {
        if (tempBug.getBugID() != bugID) {
            tempFout.write(reinterpret_cast<char*>(&tempBug), sizeof(Bug));
        }
        else {
            found = true;
        }
        index++;
    }

    closeReadFile();
    tempFout.close();

    // Replace the original file with the temporary file if a record was found
    if (found) {
        if (remove("E:/SFU/Cmpt276/Assignment4_VS/Bug_Report/src/bug.dat") != 0) {
            std::cerr << "Error deleting original file" << std::endl;
            return false;
        }
        if (rename("E:/SFU/Cmpt276/Assignment4_VS/Bug_Report/src/temp.dat", "E:/SFU/Cmpt276/Assignment4_VS/Bug_Report/src/bug.dat") != 0) {
            std::cerr << "Error renaming temporary file" << std::endl;
            return false;
        }
    }
    else {
        std::cout << "Bug ID not found, no record deleted" << std::endl;
        remove("E:/SFU/Cmpt276/Assignment4_VS/Bug_Report/src/temp.dat");
    }
    std::cout << "Bug " << bugID << " deleted!" << std::endl;
    return true;
}

Bug Bug::findBugRecord(int bugID) {
    Bug bugObj;
    int num = 0;
    seekToBeginningOfFile();
    while (getNext(bugObj, num)) {
        if (bugObj.getBugID() == bugID) {
            return bugObj;
        }
        num++;
    }
    return Bug(0,"","","", 0, 0);
}

void Bug::printBugsByProduct(int productID)
{
    Bug bugObj;
    seekToBeginningOfFile();
    int num = 0;
    printBugTableHeader();
    while (getNext(bugObj, num)) {
        if (bugObj.getProductID() == productID) {
            printBug(bugObj);
        }
        num++;
    }
}

void Bug::printBugsBySeverity(std::string severity)
{
    Bug bugObj;
    seekToBeginningOfFile();
    int num = 0;
    printBugTableHeader();
    while (getNext(bugObj, num)) {
        if (bugObj.getSeverity() == severity) {
            printBug(bugObj);
        }
        num++;
    }
}

void Bug::printBugsByStatus(std::string status)
{
    Bug bugObj;
    seekToBeginningOfFile();
    int num = 0;
    printBugTableHeader();
    while (getNext(bugObj, num)) {
        if (bugObj.getStatus() == status) {
            printBug(bugObj);
        }
        num++;
    }
}

// Static method to read the last ID from a file
void Bug::readLastID() {
    std::ifstream fin("E:/SFU/Cmpt276/Assignment4_VS/Bug_Report/src/id.dat", std::ios::in | std::ios::binary);
    if (fin.is_open()) {
        fin.read(reinterpret_cast<char*>(&bugIDCount), sizeof(bugIDCount));
        fin.close();
    }
}

// Static method to write the current ID to a file
void Bug::writeLastID() {
    std::ofstream fout("E:/SFU/Cmpt276/Assignment4_VS/Bug_Report/src/id.dat", std::ios::out | std::ios::binary);
    if (fout.is_open()) {
        fout.write(reinterpret_cast<const char*>(&bugIDCount), sizeof(bugIDCount));
        fout.close();
    }
}
