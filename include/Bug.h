/// 
 // Filename: Bug.h
 // Description: Header file for the Bug class
 // 
 // Version History:
 // 1.0 2024-07-02 - Initial version
 ///

#pragma once

#include <string>
#include <fstream>

class Bug {
public:
    //===============================================================================
    // Constructor
    // Default constructor initializes an empty Bug object
    Bug();

    //===============================================================================
    // Parameterized constructor initializes a Bug object with specific details
    // @param bugID - The ID of the bug
    // @param description - Description of the bug
    // @param severity - Severity of the bug
    // @param status - Status of the bug
    // @param productReleaseID - ID of the related product release
    Bug(int bugID, const std::string& description, const std::string& severity, 
        const std::string& status, int productID, int releaseID);

    //===============================================================================
    // Getters - all const as they do not change anything

    // Gets the bug ID
    // @return - returns the associated integer bug ID
    int getBugID() const;
    
    //===============================================================================
    // Gets the description of the bug
    // @return - returns the associated string description
    std::string getDescription() const;

    //===============================================================================
    // Gets the severity of the bug
    // @return - returns the associated string severity
    std::string getSeverity() const;

    //===============================================================================
    // Gets the status of the bug
    // @return - returns the associated string status
    std::string getStatus() const;

    //===============================================================================
    // Gets the product ID related to the bug
    // @return - returns the associated integer product ID
    int getProductID() const;

    //===============================================================================
    // Gets the release ID related to the Bug's Product
    // @return - returns the associated integer releaseID
    int getReleaseID() const;

    //===============================================================================
    // Setters - no const promise because they change attributes

    // Sets the bug ID
    // @param bugID - The bug ID to set
    // @return - returns true if successful, false otherwise
    bool setBugID(int bugID);

    //===============================================================================
    // Sets the product ID
    // @param product ID - The product ID to set
    // @return - returns true if successful, false otherwise
    bool setProductID(int productID);

    //===============================================================================
    // Sets the release ID
    // @param release ID - The product ID to set
    // @return - returns true if successful, false otherwise
    bool setReleaseID(int releaseID);

    //===============================================================================
    // Sets the description of the bug
    // @param description - The description to set
    // @return - returns true if successful, false otherwise
    bool setDescription(const std::string& description);

    //===============================================================================
    // Sets the severity of the bug
    // @param severity - The severity to set
    // @return - returns true if successful, false otherwise
    bool setSeverity(const std::string& severity);

    //===============================================================================
    // Sets the status of the bug
    // @param status - The status to set
    // @return - returns true if successful, false otherwise
    bool setStatus(const std::string& status);


    //===============================================================================
    // File operations

    // Opens the file for reading and writing
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
    // Writes a Bug object to the file
    // @param bugObject - The Bug object to write
    // @return - True if the write operation was successful, false otherwise
    static bool writeBug(Bug& bugObject);

    //===============================================================================
    // Moves the file cursor to the beginning of the file
    static void seekToBeginningOfFile();

    //===============================================================================
    // Reads the next Bug object from the file
    // @param bugObject - The Bug object to fill with data from the file
    // @param index - Starting at 0, it indicates which Bug item to retrieve
    // @return - True if a record was successfully read, false if the end of the file was reached
    static bool getNext(Bug& bugObject, int index);

    //===============================================================================
    // Deletes a specific Bug record from the file
    // @param bugID - The ID of the bug to delete
    // @return - True if the record was successfully deleted, false otherwise
    static bool deleteBugRecord(int bugID);

    //===============================================================================
    // Finds a specific Bug record in the file
    // @param bugID - The ID of the bug to find
    // @param bugObject - The Bug object to fill with data if found
    // @return - True if the record was found, false otherwise
    static Bug findBugRecord(int bugID);

    //===============================================================================
    // Finds specific Bugs record in the file by productID
    // @param productID - Product ID associated with the bug to find
    // @return - None (void) - prints all bugs to console
    static void printBugsByProduct(int productID);

    //===============================================================================
    // Finds specific Bugs record in the file by severity
    // @param severity - String representing the severity of the bug
    // @return - None (void) - prints all bugs to console
    static void printBugsBySeverity(std::string severity);

    //===============================================================================
    // Finds specific Bugs record in the file by status
    // @param status - String representing the status of the bug
    // @return - None (void) - prints all bugs to console
    static void Bug::printBugsByStatus(std::string status);

    //===============================================================================
    // Saves the last ID
    static void Bug::readLastID();

    //===============================================================================
    // Reads the last ID
    static void Bug::writeLastID();

    static int bugIDCount; // Keeps tracks of the bug ID 

private:
    int bugID;               // The bug ID
    char description[500]; // The description of the bug
    char severity[100];    // The severity of the bug
    char status[100];      // The status of the bug
    int productID;           // The product ID of the Product related to the Bug
    int releaseID;           // The ID of the related product release

    static std::string fileName;  // The name of the currently open file

    static std::ofstream fout;    // stream for writing to files
    static std::fstream fin;      // stream for reading to files

    static std::ofstream tempFout;    // Stream for writing to temporary file
    static std::fstream tempFin;     // Stream for reading from temporary file
};

