/// 
// Filename: Release.cpp
// Description: Implementation file for the Release class
// 
// Version History:
// 1.0 2024-07-02 - Initial version
///

#include <iostream>
#include <cstring>
#include "Release.h"

// Define and initialize the static member variables
std::string Release::fileName = "release_default.data";  // You can set a default filename

std::ofstream Release::fout;
std::fstream Release::fin;

// Constructors
Release::Release() : releaseID(0), productID(0) {
    // referring to attributes - eg. this->version
    std::memset(version, 0, sizeof(version));
    std::memset(releaseDate, 0, sizeof(releaseDate));
}

Release::Release(int releaseID, int productID, const std::string& version, const std::string& releaseDate)
    : releaseID(releaseID), productID(productID) {
    std::strncpy(this->version, version.c_str(), sizeof(this->version) - 1);
    std::strncpy(this->releaseDate, releaseDate.c_str(), sizeof(this->releaseDate) - 1);
}

// Getters
int Release::getReleaseID() const {
    return releaseID;
}

int Release::getProductID() const {
    return productID;
}

std::string Release::getVersion() const {
    return version;
}

std::string Release::getReleaseDate() const {
    return releaseDate;
}

// Setters
void Release::setReleaseID(int releaseID) {
    this->releaseID = releaseID;
}

void Release::setProductID(int productID) {
    this->productID = productID;
}

bool Release::setVersion(const std::string& version) {
    // explicit attribute to avoid confusing with argument
    if (version.size() >= sizeof(this->version)) {
        return false; // Input string too long
    }
    std::strncpy(this->version, version.c_str(), sizeof(this->version) - 1);
    this->version[sizeof(this->version) - 1] = '\0'; // Ensure null-termination
    return true;
}

bool Release::setReleaseDate(const std::string& releaseDate) {
    if (releaseDate.size() >= sizeof(this->releaseDate)) {
        return false; // Input string too long
    }
    std::strncpy(this->releaseDate, releaseDate.c_str(), sizeof(this->releaseDate) - 1);
    this->releaseDate[sizeof(this->releaseDate) - 1] = '\0'; // Ensure null-termination
    return true;
}

// File operations
bool Release::openWriteFile(const std::string& fileName) {
    Release::fileName = fileName;
    Release::fout.clear();
    Release::fout.flush();
    Release::fout.open(Release::fileName, std::ios::out | std::ios::binary | std::ios::app);
    return Release::fout.is_open();
}

bool Release::openReadFile(const std::string& fileName)
{
    Release::fileName = fileName;
    Release::fin.clear();
    Release::fin.open(Release::fileName, std::ios::in | std::ios::binary);
    return Release::fin.is_open();
}

void Release::closeWriteFile() {
    if (Release::fout.is_open()) {
        Release::fout.close();
    }
}

void Release::closeReadFile()
{
    if (Release::fin.is_open()) {
        Release::fin.close();
    }
}

bool Release::writeRelease(Release& releaseObject) {
    if (!openWriteFile("E:/SFU/Cmpt276/Assignment4_VS/Bug_Report/src/release.dat")) {
        std::cout << "Could not open Write file" << std::endl;
        return false;
    }

    if (!Release::fout.good()) {
        std::cout << "There was a problem with Release write file stream" << std::endl;
    }
    else {
        Release::fout.write(reinterpret_cast<char*>(&releaseObject), sizeof(Release));
    }

    if (!Release::fout.good()) {
        std::cerr << "Error writing to file" << std::endl;
        closeWriteFile();
        return false;
    }

    closeWriteFile();
    std::cout << "Data written to Release file successfully." << std::endl;
    return true;
}

void Release::seekToBeginningOfFile() {
    if (Release::fin.is_open()) {
        Release::fin.seekg(0);
    }
}

bool Release::getNext(Release& releaseObject, int index) {
    if (!openReadFile("E:/SFU/Cmpt276/Assignment4_VS/Bug_Report/src/release.dat")) {
        std::cout << "Could not open Read file" << std::endl;
        return false;
    }

    if (!Release::fin.is_open()) {
        std::cout << "Error opening file for reading" << std::endl;
    }

    Release::fin.seekg(index * sizeof(Release), std::ios::beg);
    Release::fin.read(reinterpret_cast<char*>(&releaseObject), sizeof(Release));

    if (Release::fin.eof()) {
        std::cout << "End of file reached" << std::endl;
        closeReadFile();
        return false;
    }

    if (Release::fin.fail()) {
        std::cout << "Error reading data from file" << std::endl;
        closeReadFile();
        return false;
    }

    closeReadFile();
    return true;
}

bool Release::deleteReleaseRecord(int releaseID) {
    // Implement the logic to delete a specific release record
    // This would typically involve reading all records, skipping the one to delete, and rewriting the file
    return true;
}

Release Release::findReleaseRecord(int releaseID) {
    Release releaseObj;
    seekToBeginningOfFile();
    int num = 0;

    // Loop over every item from file, checking to see if there is a matching Release ID
    while (getNext(releaseObj, num)) {
        if (releaseObj.getReleaseID() == releaseID) {

            return releaseObj;
        }
        num++;
    }
    return Release(0, 0, "", "");       // Return Empty Release so we can check for Release ID to be zero to indiciate that no Release Object with given ID found
}
