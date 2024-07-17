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
    // Constructor
    // Default constructor initializes an empty Bug object
    Bug();

    // Parameterized constructor initializes a Bug object with specific details
    // @param bugID - The ID of the bug
    // @param description - Description of the bug
    // @param severity - Severity of the bug
    // @param status - Status of the bug
    // @param productReleaseID - ID of the related product release
    Bug(int bugID, const std::string& description, const std::string& severity, 
        const std::string& status, int productReleaseID);

    // Getters - all const as they do not change anything

    // Gets the bug ID
    // @return - returns the associated integer bug ID
    int getBugID() const;
    
    // Gets the description of the bug
    // @return - returns the associated string description
    std::string getDescription() const;

    // Gets the severity of the bug
    // @return - returns the associated string severity
    std::string getSeverity() const;

    // Gets the status of the bug
    // @return - returns the associated string status
    std::string getStatus() const;

    // Gets the product release ID related to the bug
    // @return - returns the associated integer product release ID
    int getProductReleaseID() const;

    // Setters - no const promise because they change attributes

    // Sets the bug ID
    // @param bugID - The bug ID to set
    // @return - returns true if successful, false otherwise
    bool setBugID(int bugID);

    // Sets the description of the bug
    // @param description - The description to set
    // @return - returns true if successful, false otherwise
    bool setDescription(const std::string& description);

    // Sets the severity of the bug
    // @param severity - The severity to set
    // @return - returns true if successful, false otherwise
    bool setSeverity(const std::string& severity);

    // Sets the status of the bug
    // @param status - The status to set
    // @return - returns true if successful, false otherwise
    bool setStatus(const std::string& status);

    // Sets the product release ID related to the bug
    // @param productReleaseID - The product release ID to set
    // @return - returns true if successful, false otherwise
    bool setProductReleaseID(int productReleaseID);

    // File operations

    // Opens the file for reading and writing
    // @param filename - The name of the file to open
    // @return True if the file was successfully opened, false otherwise
    static bool openBugFile(const std::string& filename);

    // Closes the currently open file
    static void closeBugFile();

    // Writes a Bug object to the file
    // @param bugObject - The Bug object to write
    // @return - True if the write operation was successful, false otherwise
    static bool writeBug(const Bug& bugObject);

    // Moves the file cursor to the beginning of the file
    static void seekToBeginningOfFile();

    // Reads the next Bug object from the file
    // @param bugObject - The Bug object to fill with data from the file
    // @return - True if a record was successfully read, false if the end of the file was reached
    static bool getNext(Bug& bugObject);

    // Deletes a specific Bug record from the file
    // @param bugID - The ID of the bug to delete
    // @return - True if the record was successfully deleted, false otherwise
    static bool deleteBugRecord(int bugID);

    // Finds a specific Bug record in the file
    // @param bugID - The ID of the bug to find
    // @param bugObject - The Bug object to fill with data if found
    // @return - True if the record was found, false otherwise
    static Bug findBugRecord(int bugID);

private:
    int bugID;  // The bug ID
    std::string description;  // The description of the bug
    std::string severity;  // The severity of the bug
    std::string status;  // The status of the bug
    int productReleaseID;  // The ID of the related product release

    static std::fstream file;  // The file stream used for file operations
    static std::string filename;  // The name of the currently open file
};

