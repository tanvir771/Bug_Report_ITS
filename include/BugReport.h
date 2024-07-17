/// 
 // Filename: BugReport.h
 // Description: Header file for the BugReport class
 // 
 // Version History:
 // 1.0 2024-07-02- Initial version
 ///

#pragma once

#include <string>
#include <vector>
#include "Customer.h"
#include "Product.h"
#include "ChangeBug.h"

class BugReport {
public:
    // Constructor
    BugReport(int changeRequestID, const std::string &description, int priority, const std::string &status, const std::string &dateOfRequest
            Product product, Customer customer);

    // Getters
    int getChangeRequestID() const;
    std::string getDescription() const;
    int getPriority() const;
    std::string getStatus() const;
    std::string getDateOfRequest() const;
    Product// getProduct() const;
    Customer// getCustomer() const;

private:
    int changeRequestID;
    std::string description;
    int priority;
    std::string status;
    std::string dateOfRequest;
    Product// product;
    Customer// customer;
    std::vector<ChangeBug//> changes;
};

