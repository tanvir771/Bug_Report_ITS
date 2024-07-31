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

//===============================================================================
// Define and initialize the static member variables
std::string Release::fileName = "release_default.data";  // You can set a default filename

std::ofstream Release::fout;
std::fstream Release::fin;

//===============================================================================
// Constructors
// Default constructor initializes an empty release object
Release::Release() : releaseID(0), productID(0) {
    // referring to attributes - eg. this->version
    std::memset(version, 0, sizeof(version));
    std::memset(releaseDate, 0, sizeof(releaseDate));
}

//===============================================================================
// Parameterized constructor initializes a release object with specific details
// @param releaseID - The ID of the release
// @param version - The version of the release
// @param releaseDate - The release date
Release::Release(int releaseID, int productID, const std::string& version, const std::string& releaseDate)
    : releaseID(releaseID), productID(productID) {
    std::strncpy(this->version, version.c_str(), sizeof(this->version) - 1);
    std::strncpy(this->releaseDate, releaseDate.c_str(), sizeof(this->releaseDate) - 1);
}

//===============================================================================
// Getters

// Gets the release ID
// @return The release ID
int Release::getReleaseID() const {
    return releaseID;
}

//===============================================================================
// Gets the version of the release
// @return The version string
int Release::getProductID() const {
    return productID;
}

//===============================================================================
// Gets the release date
// @return - The release date string
std::string Release::getVersion() const {
    return version;
}

//===============================================================================
// Gets the product ID
// @return - returns int Product ID
std::string Release::getReleaseDate() const {
    return releaseDate;
}

//===============================================================================
// Setters

// Sets the release ID
// @param releaseID - The release ID
void Release::setReleaseID(int releaseID) {
    this->releaseID = releaseID;
}

//===============================================================================
// Sets the product ID
// @param productID - The product ID
void Release::setProductID(int productID) {
    this->productID = productID;
}

//===============================================================================
// Sets the version of the release
// @param version - The version string
bool Release::setVersion(const std::string& version) {
    // explicit attribute to avoid confusing with argument
    if (version.size() >= sizeof(this->version)) {
        return false; // Input string too long
    }
    std::strncpy(this->version, version.c_str(), sizeof(this->version) - 1);
    this->version[sizeof(this->version) - 1] = '\0'; // Ensure null-termination
    return true;
}

//===============================================================================
// Sets the release date
// @param releaseDate - The release date string
bool Release::setReleaseDate(const std::string& releaseDate) {
    if (releaseDate.size() >= sizeof(this->releaseDate)) {
        return false; // Input string too long
    }
    std::strncpy(this->releaseDate, releaseDate.c_str(), sizeof(this->releaseDate) - 1);
    this->releaseDate[sizeof(this->releaseDate) - 1] = '\0'; // Ensure null-termination
    return true;
}

//===============================================================================
// File operations

// Opens the file for reading
// @param fileName - The name of the file to open
// @return True if the file was successfully opened, false otherwise
bool Release::openWriteFile(const std::string& fileName) {
    Release::fileName = fileName;
    Release::fout.clear();
    Release::fout.flush();
    Release::fout.open(Release::fileName, std::ios::out | std::ios::binary | std::ios::app);
    return Release::fout.is_open();
}

//===============================================================================
// Opens the file for reading
// @param fileName - The name of the file to open
// @return True if the file was successfully opened, false otherwise
bool Release::openReadFile(const std::string& fileName)
{
    Release::fileName = fileName;
    Release::fin.clear();
    Release::fin.open(Release::fileName, std::ios::in | std::ios::binary);
    return Release::fin.is_open();
}

//===============================================================================
// Closes the currently open ostream file
void Release::closeWriteFile() {
    if (Release::fout.is_open()) {
        Release::fout.close();
    }
}

//===============================================================================
// Closes the currently open fstream file
void Release::closeReadFile()
{
    if (Release::fin.is_open()) {
        Release::fin.close();
    }
}

//===============================================================================
// Writes a Release object to the file
// @param - releaseObject The Release object to write
// @return - True if the write operation was successful, false otherwise
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

// Moves the file cursor to the beginning of the file
void Release::seekToBeginningOfFile() {
    if (Release::fin.is_open()) {
        Release::fin.seekg(0);
    }
}

//===============================================================================
// Reads the next Release object from the file
// @param releaseObject - The Release object to fill with data from the file
// @param index - The record number to read
// @return - True if a record was successfully read, false if the end of the file was reached
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

//===============================================================================
// Finds a specific Release record in the file
// @param releaseID - The ID of the release to find
// @return - The Release object with data if found; otherwise empty Release object
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
    // Return Empty Release so we can check for Release ID to be zero to indiciate that no Release Object with given ID found
    return Release(0, 0, "", "");
}
