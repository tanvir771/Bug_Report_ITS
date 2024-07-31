/// 
 // Filename: Request.h
 // Description: Header file for the Request class
 // 
 // Version History:
 // 1.0 2024-07-02 - Initial version
 ///
#pragma once

#include <string>
#include <fstream>
#include "Bug.h"

class Request {
public:
    //===============================================================================
    // Constructor
    // Default constructor initializes an empty Request object
    Request();

    //===============================================================================
    // Parameterized constructor initializes a Request object with specific details
    // @param requestID - The ID of the request
    // @param description - Description of the request
    // @param priority - Priority of the request
    // @param status - Status of the request
    // @param dateOfRequest - Date the request was made
    // @param productID - ID of the related product
    // @param customerName - Name of the customer making the request
    // @param releaseID - ID of the Release associated with the product (nullable)
    Request(int changeRequestID, const std::string& description, const std::string& priority, 
            const std::string& status, const std::string& dateOfRequest, int productID, 
            const std::string& customerName, int releaseID);

    //===============================================================================
    // Getters - all const as they do not change anything

    // Gets the change request ID
    // @return - returns the associated integer request ID
    int getRequestID() const;

    //===============================================================================
    // Gets the description of the request
    // @return - returns the associated string description
    std::string getDescription() const;

    //===============================================================================
    // Gets the priority of the request
    // @return - returns the associated string priority
    std::string getPriority() const;

    //===============================================================================
    // Gets the status of the request
    // @return - returns the associated string status
    std::string getStatus() const;

    //===============================================================================
    // Gets the date of the request
    // @return - returns the associated string date of request
    std::string getDateOfRequest() const;

    //===============================================================================
    // Gets the product ID related to the request
    // @return - returns the associated integer product ID
    int getProductID() const;

    //===============================================================================
    // Gets the name of the customer making the request
    // @return - returns the associated string customer name
    std::string getCustomerName() const;

    //===============================================================================
    // Gets the release ID related to the request
    // @return - returns the associated integer release ID, or -1 if not set
    int getReleaseID() const;

    //===============================================================================
    // Setters - no const promise because they change attributes

    // Sets the change request ID
    // @param changeRequestID - The change request ID to set
    // @return - returns true if successful, false otherwise
    bool setRequestID(int requestID);

    //===============================================================================
    // Sets the description of the request
    // @param description - The description to set
    // @return - returns true if successful, false otherwise
    bool setDescription(const std::string& description);

    //===============================================================================
    // Sets the priority of the request
    // @param priority - The priority to set
    // @return - returns true if successful, false otherwise
    bool setPriority(const std::string& priority);

    //===============================================================================
    // Sets the status of the request
    // @param status - The status to set
    // @return - returns true if successful, false otherwise
    bool setStatus(const std::string& status);

    //===============================================================================
    // Sets the date of the request
    // @param dateOfRequest - The date of request to set
    // @return - returns true if successful, false otherwise
    bool setDateOfRequest(const std::string& dateOfRequest);

    //===============================================================================
    // Sets the product ID related to the request
    // @param productID - The product ID to set
    // @return - returns true if successful, false otherwise
    bool setProductID(int productID);

    //===============================================================================
    // Sets the name of the customer making the request
    // @param customerName - The customer name to set
    // @return - returns true if successful, false otherwise
    bool setCustomerName(const std::string& customerName);

    //===============================================================================
    // Sets the release ID related to the request
    // @param releaseID - The release ID to set
    // @return - returns true if successful, false otherwise
    bool setReleaseID(int releaseID);

    //===============================================================================
    // File operations

    // Opens the file for writing
    // @param fileName - The name of the file to open
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
    // Writes a Request object to the file
    // @param requestObject - The Request object to write
    // @return - True if the write operation was successful, false otherwise
    static bool writeRequest(Request& requestObject);

    //===============================================================================
    // Moves the file cursor to the beginning of the file
    static void seekToBeginningOfFile();

    //===============================================================================
    // Reads the next Request object from the file
    // @param requestObject - The Request object to fill with data from the file
    // @param index - The record number to read
    // @return - True if a record was successfully read, false if the end of the file was reached
    static bool getNext(Request& requestObject, int num);

    //===============================================================================
    // Deletes a specific Request record from the file
    // @param changeRequestID - The ID of the request to delete
    // @return - True if the record was successfully deleted, false otherwise
    static bool deleteRequestRecord(int changeRequestID);

    //===============================================================================
    // Finds a specific Request record in the file
    // @param changeRequestID - The ID of the request to find
    // @param requestObject - The Request object to fill with data if found
    // @return - True if the record was found, false otherwise
    static Request findRequestRecord(int changeRequestID);

    //===============================================================================
    // Writes last ID to file
    static void writeLastID();

    //===============================================================================
    // Reads last ID from file
    static void readLastID();

    //===============================================================================
    // Keeps track of Request ID
    static int requestIDCount;

private:
    int changeRequestID;  // The change request ID
    char description[500];  // The description of the request
    char priority[100];  // The priority of the request
    char status[100];  // The status of the request
    char dateOfRequest[100];  // The date the request was made
    int productID;  // The ID of the related product
    char customerName[150];  // The name of the customer making the request
    int releaseID;  // The ID of the related release, or -1 if not set

    static std::string fileName;  // The name of the currently open file

    static std::ofstream fout;    // stream for writing to files
    static std::fstream fin;      // stream for reading to files
};