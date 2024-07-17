/// 
 // Filename: ChangeBug.h
 // Description: Header file for the ChangeBug class
 // 
 // Version History:
 // 1.0 2024-07-02 - Initial version
 ///

#pragma once

#include <string>
#include "ProductRelease.h"

class ChangeBug {
public:
    // Constructor
    ChangeBug(int bugID, const std::string &description, const std::string &severity, const std::string &status);

    // Getters
    int getBugID() const;
    std::string getDescription() const;
    std::string getSeverity() const;
    std::string getStatus() const;

private:
    int bugID;
    std::string description;
    std::string severity;
    std::string status;
    ProductRelease// productRelease;
};
