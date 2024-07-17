/// 
// Filename: BugReport.cpp
// Description: Implementation file for the BugReport class
// 
// Version History:
// 1.0 2024-07-02 - Initial version
///

#include "BugReport.h"

// Constructor
BugReport::BugReport(int changeRequestID, const std::string &description, int priority, const std::string &status, const std::string &dateOfRequest,
                     const Product &product, const Customer &customer)
    : changeRequestID(changeRequestID), description(description), priority(priority), status(status), dateOfRequest(dateOfRequest), 
      product(product), customer(customer) {}

// Getters
int BugReport::getChangeRequestID() const {
    return changeRequestID;
}

std::string BugReport::getDescription() const {
    return description;
}

int BugReport::getPriority() const {
    return priority;
}

std::string BugReport::getStatus() const {
    return status;
}

std::string BugReport::getDateOfRequest() const {
    return dateOfRequest;
}

Product BugReport::getProduct() const {
    return product;
}

Customer BugReport::getCustomer() const {
    return customer;
}
