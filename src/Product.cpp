/// 
// Filename: Product.cpp
// Description: Implementation file for the Product class
// 
// Version History:
// 1.0 2024-07-02 - Initial version
///

#include "Product.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>


// Define and initialize the static member variables
std::string Product::fileName = "product_default.dat";  // set a default fileName

std::ofstream Product::fout;
std::fstream Product::fin;

// Default constructor
Product::Product() : productID(0), isAnticipatedRelease(false) {
    // name is the attribute - explicit: this->name
    std::memset(name, 0, sizeof(name));
}

// Parameterized constructor
Product::Product(int productID, Release& release, const std::string &name, const std::string &releaseDate)
    : productID(productID),  productRelease(release), isAnticipatedRelease(false) {
    std::strncpy(this->name, name.c_str(), sizeof(this->name) - 1);
}

// Getter for Product ID
int Product::getProductID() const {
    return productID;
}

// Gets Release ID of a particular instance of Product
// @return - returns associated integer Release ID 
int Product::getReleaseID() const
{
    return productRelease.getReleaseID();
}

// Getter for Product name
std::string Product::getName() const {
    return name;
}

// Getter for Product release date
std::string Product::getReleaseDate() const {
    return productRelease.getReleaseDate();
}


// Getter for anticipated release
bool Product::getIsAnticipatedRelease() const
{
    return isAnticipatedRelease;
}

// Getter for Product Release
Release& Product::getReleases() const {
    return const_cast<Release&>(productRelease);
}

// Setter for Product ID
bool Product::setProductID(int newProductID) {
    if (newProductID > 0) {
        productID = newProductID;
        return true;
    }
    return false;
}

// Setter for Product name
bool Product::setName(const std::string& newName) {
    if (newName.size() >= sizeof(this->name)) {
        return false; // Input string too long
    }
    std::strncpy(this->name, newName.c_str(), sizeof(this->name) - 1);
    this->name[sizeof(this->name) - 1] = '\0'; // Ensure null-termination
    return true;
}

// Setter for Product Release
bool Product::setRelease(Release& releaseToSet) {
    productRelease = releaseToSet;
    return true;
}

// Setter for anticipated release
bool Product::setAnticipatedRelease(bool isAnticipated) {
    isAnticipatedRelease = isAnticipated;
    return true;
}

// Opens the file for reading and writing
bool Product::openWriteFile(const std::string& filename) {
    Product::fileName = filename;
    Product::fout.clear();
    Product::fout.flush();
    Product::fout.open(Product::fileName, std::ios::out | std::ios::binary | std::ios::app);
    return Product::fout.is_open();
}

bool Product::openReadFile(const std::string& fileName)
{
    Product::fileName = fileName;
    Product::fin.clear();
    Product::fin.open(Product::fileName, std::ios::in | std::ios::binary);
    return Product::fin.is_open();
}


// Closes the currently open file
void Product::closeWriteFile() {
    if (Product::fout.is_open()) {
        Product::fout.close();
    }
}

void Product::closeReadFile()
{
    if (Product::fin.is_open()) {
        Product::fin.close();
    }
}


bool Product::writeProduct(Product& productObject) {
    if (!openWriteFile("E:/SFU/Cmpt276/Assignment4_VS/Bug_Report/src/product.dat")) {
        std::cout << "Could not open Write file" << std::endl;
        return false;
    }

    if (!Product::fout.good()) {
        std::cout << "Problem" << std::endl;
    }
    else {
        Product::fout.write(reinterpret_cast<char*>(&productObject), sizeof(Product));
    }

    if (!Product::fout.good()) {
        std::cerr << "Error writing to file: output.dat" << std::endl;
        closeWriteFile();
        return false;
    }

    closeWriteFile();
    std::cout << "Data written to product.dat successfully." << std::endl;
    return true;
}

// Moves the file cursor to the beginning of the file
void Product::seekToBeginningOfFile() {
    if (Product::fin.is_open()) {
        Product::fin.seekg(0, std::ios::beg);
    }
}

//
// Reads the next Product object from the file
bool Product::getNext(Product& productObject, int index) {
    if (!openReadFile("E:/SFU/Cmpt276/Assignment4_VS/Bug_Report/src/product.dat")) {
        std::cout << "Could not open Read file" << std::endl;
        return false;
    }

    if (!Product::fin.is_open()) {
        std::cout << "Error opening file for reading" << std::endl;
    }

    Product::fin.seekg(index * sizeof(Product), std::ios::beg);
    Product::fin.read(reinterpret_cast<char*>(&productObject), sizeof(Product));

    if (Product::fin.eof()) {
        std::cout << "End of file reached prematurely" << std::endl;
        closeReadFile();
        return false;
    }

    if (Product::fin.fail()) {
        std::cout << "Error reading data from file" << std::endl;
        closeReadFile();
        return false;
    }

    closeReadFile();
    return true;
}

// TODO: Delete probably does not work
// Deletes a specific Product record from the file
bool Product::deleteProductRecord(int productID) {
    int num = 1;
    if (Product::fin.is_open()) {
        std::fstream tempFile("temp.dat", std::ios::out | std::ios::binary);
        Product tempProduct;
        bool found = false;

        seekToBeginningOfFile();
        while (getNext(tempProduct, num)) {
            if (tempProduct.getProductID() != productID) {
                tempFile.write(reinterpret_cast<const char*>(&tempProduct), sizeof(Product));
            } else {
                found = true;
            }
            num++;
        }

        Product::fin.close();
        tempFile.close();

        remove(fileName.c_str());
        rename("temp.dat", fileName.c_str());

        openWriteFile(fileName);
        return found;
    }
    return false;
}

// Finds a specific Product record in the file
// Returns nullptr if no Product Found
Product Product::findProductRecord(int productID) {
    Product productObj;
    int num = 0;
    seekToBeginningOfFile();
    while (getNext(productObj, num)) {
        if (productObj.getProductID() == productID) {
            return productObj;
        }
        num++;
    }
    return Product();
}
