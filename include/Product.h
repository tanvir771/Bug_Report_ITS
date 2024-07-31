/// 
 // Filename: Product.h
 // Description: Header file for the Product class
 // 
 // Version History:
 // 1.0 2024-07-02 - Initial version
 ///

#pragma once

#include <string>
#include "Release.h"

class Product {
public:
    // Constructor
    // Default - initializes empty Product instance
    Product();

    // Parameterized Constructor - initializes Product instance with given parameters
    // @param productID - Product ID number (of the Product to create)
    // @param name - Name of Product (taken by reference)
    // @param releaseDate - String of the release date to use (taken by reference)
    Product(int productID, Release& release, const std::string& name, const std::string& releaseDate);

    // Getters - all const as they do not change anything

    // Gets Product ID of a particular instance
    // @return - returns associated integer Product ID 
    int getProductID() const;

    // Gets Release ID of a particular instance of Product
    // @return - returns associated integer Release ID 
    int getReleaseID() const;
    
    // Gets Product name of a particular instance
    // @return - returns associated string of Product name 
    std::string getName() const;

    // Gets Product release date of a particular instance
    // @return - returns associated string of Product release date from Release instance
    std::string getReleaseDate() const;

    // Gets whether or not the Product has an anticipated release
    // @return - returns true if anticipated release, false otherwise
    bool getIsAnticipatedRelease() const;

    // Gets Product Release of a particular instance
    // @return - return a reference to the associated Release instance of the Product instance
    Release& getReleases() const;

    // Setters - no const promise because sets different attributes

    // Sets Product ID of a particular instance
    // @return - returns true if successful, false otherwise
    bool setProductID(int newProductID);

    // Sets Product name of a particular instance
    // @return - returns true if successful, false otherwise
    bool setName(const std::string& newName);

    // Sets Product associated Release with a new Release object
    // Note: Cannot change the date of the Release (of a Product), without changing the whole relase
    // @return - returns true if successful, false otherwise
    bool setRelease(Release& releaseToSet);

    // Sets Product anticipated release
    // @param isAnticipatedRelease - bool representing whether or not Product has an anticipated release
    // @return - returns true if successful, false otherwise
    bool setAnticipatedRelease(bool isAnticipatedRelease);

    // File operations

    // Opens the file for writing
    // @param filename - The name of the file to open
    // @return True if the file was successfully opened, false otherwise
    static bool openWriteFile(const std::string& filename);


    // Opens the file for reading
    // @param fileName - The name of the file to open
    // @return True if the file was successfully opened, false otherwise
    static bool openReadFile(const std::string& fileName);

    // Closes the currently open ostream file
    static void closeWriteFile();

    // Closes the currently open fstream file
    static void closeReadFile();

    // Writes a Product object to the file
    // @param - productObject - The Product object to write
    // @return - True if the write operation was successful, false otherwise
    static bool writeProduct(Product& productObject);

    // Moves the file cursor to the beginning of the file
    static void seekToBeginningOfFile();

    // Reads the next Product object from the file
    // @param productObject - The Product object to fill with data from the file
    // @param index - The record number to read
    // @return - True if a record was successfully read, false if the end of the file was reached
    static bool getNext(Product& productObject, int index);

    // Finds a specific Product record in the file
    // @param productID - The ID of the release to find
    // @param productObject - The Product object to fill with data if found
    // @return - True if the record was found, false otherwise
    static Product findProductRecord(int productID);

    static void printAllProducts();

private:
    int productID;
    char name[150];
    Release productRelease; // if a future Release, then this is the anticipatedRelease
    bool isAnticipatedRelease; // represents whether the Product Release is in the future or not

    static std::string fileName;  // The name of the currently open file

    static std::ofstream fout;    // stream for writing to files
    static std::fstream fin;      // stream for reading to files
};

