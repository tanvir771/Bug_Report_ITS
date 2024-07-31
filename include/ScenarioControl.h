// 
 // Filename: ScenarioControl.h
 // Description: Header file for the ScenarioControl class to manage Products, Bugs, Customers, and Requests.
 // 
 // Version History:
 // 1.0 2024-07-04 - Initial version
 //
#pragma once

#include <fstream>
#include "Product.h"
#include "Bug.h"
#include "Customer.h"
#include "Request.h"

class ScenarioControl {
public:
    // Constructor
    ScenarioControl();

    // Product operations
    // @brief Creates a new Product object and adds it to the product list.
    // @param productID The ID of the product.
    // @param name The name of the product.
    // @param version The version of the product.
    // @return Product The created Product object.
    Product createProduct();

    // Bug operations
    // @brief Creates a new Bug object and adds it to the Bug file
    // @param bugID The ID of the bug.
    // @param description The description of the bug.
    // @param severity The severity of the bug.
    // @param status The status of the bug.
    // @return Bug The created Bug object.
    ///
    Bug createBug();

    // @brief Creates a new Bug object from a Request object and writes it to Bug file
    // @param reqObj - Request Object containing all information for a Bug
    // @return Bug The created Bug object.
    Bug createBugFromRequest(Request& reqObj);

    /////
     // @brief Deletes a Bug object from the bug list by ID.
     // @param bugID The ID of the bug to delete.
     // @return bool True if the bug was found and deleted, false otherwise.
     ///
    bool deleteBug();

    // Customer operations
    /////
     // @brief Creates a new Customer object and adds it to the customer list.
     // @param customerID The ID of the customer.
     // @param name The name of the customer.
     // @param contactInfo The contact information of the customer.
     // @return Customer The created Customer object.
     ///
    Customer createCustomer();

    /////
     // @brief Deletes a Customer object from the customer list by ID.
     // @param customerID The ID of the customer to delete.
     // @return bool True if the customer was found and deleted, false otherwise.
     ///
    bool deleteCustomer();

    // Request operations
    /////
     // @brief Creates a new Request object and adds it to the request list.
     // @param requestID The ID of the request.
     // @param description The description of the request.
     // @param priority The priority of the request.
     // @param status The status of the request.
     // @param dateOfRequest The date the request was made.
     // @param productID The ID of the related product.
     // @param customerName The name of the customer making the request.
     // @param releaseID The ID of the related release.
     // @return Request The created Request object.
     ///
    Request createRequest();

    /////
     // @brief Deletes a Request object from the request list by ID.
     // @param requestID The ID of the request to delete.
     // @return bool True if the request was found and deleted, false otherwise.
     ///
    bool deleteRequest();

    bool modifyRequest();

    // Private helper functions to find objects by ID
    /////
     // @brief Finds a Product object by ID.
     // @param productID The ID of the product to find.
     // @return Product// Pointer to the found Product object, or nullptr if not found.
     ///
    Product findProduct();

    /////
     // @brief Finds a Bug object by ID.
     // @param bugID The ID of the bug to find.
     // @return Bug// Pointer to the found Bug object, or nullptr if not found.
     ///
    Bug modifyBug();

    /////
     // @brief Finds a Customer object by ID.
     // @param customerID The ID of the customer to find.
     // @return Customer// Pointer to the found Customer object, or nullptr if not found.
     ///
    Customer findCustomer();

    /////
     // @brief Finds a Request object by ID.
     // @param requestID The ID of the request to find.
     // @return Request// Pointer to the found Request object, or nullptr if not found.
     ///
    Request findRequest();

    // Reports bugs by Product ID
    // Prints all Bugs associated to console
    void report1();

    // Reports bugs by severity
    // Prints all Bugs associated to console
    void report2();

    // Reports bugs by severity
    // Prints all Bugs associated to console
    void report3();

    // Prints all Products
    void printProducts();

private:
    // Placeholder variable
    Product product;
    Customer customer;
    Request request;
    Bug bug;
};