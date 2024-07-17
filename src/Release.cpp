/// 
// Filename: Release.cpp
// Description: Implementation file for the Release class
// 
// Version History:
// 1.0 2024-07-02 - Initial version
///

#include <iostream>
#include "Release.h"

// Define and initialize the static member variables
std::string Release::fileName = "release_default.data";  // You can set a default filename

std::ofstream Release::fout;
std::fstream Release::fin;

// Constructors
Release::Release() : releaseID(0), productID(0), version(""), releaseDate("") {}

Release::Release(int releaseID, int productID, const std::string& version, const std::string& releaseDate)
    : releaseID(releaseID), productID(productID), version(version), releaseDate(releaseDate) 
{}

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

void Release::setVersion(const std::string& version) {
    this->version = version;
}

void Release::setReleaseDate(const std::string& releaseDate) {
    this->releaseDate = releaseDate;
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
        std::cout << "End of file reached prematurely" << std::endl;
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
    while (getNext(releaseObj, num)) {
        if (releaseObj.getReleaseID() == releaseID) {
            num++;
            return releaseObj;
        }
    }
    return releaseObj;
}
