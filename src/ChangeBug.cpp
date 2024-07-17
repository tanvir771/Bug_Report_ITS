/// 
// Filename: ChangeBug.cpp
// Description: Implementation file for the ChangeBug class
// 
// Version History:
// 1.0 2024-07-02 - Initial version
///

#include "ChangeBug.h"

// Constructor
ChangeBug::ChangeBug(int bugID, const std::string &description, const std::string &severity, const std::string &status, const ProductRelease &productRelease)
    : bugID(bugID), description(description), severity(severity), status(status), productRelease(productRelease) {}

// Getters
int ChangeBug::getBugID() const {
    return bugID;
}

std::string ChangeBug::getDescription() const {
    return description;
}

std::string ChangeBug::getSeverity() const {
    return severity;
}

std::string ChangeBug::getStatus() const {
    return status;
}

ProductRelease ChangeBug::getProductRelease() const {
    return productRelease;
}

