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
    //===============================================================================
    // Constructor
    ScenarioControl();

    //===============================================================================
    // Product operations
    // @brief Creates a new Product object and adds it to the product list.
    // @return Product The created Product object.
    Product createProduct();

    //===============================================================================
    // Bug operations
    // @brief Creates a new Bug object and adds it to the Bug file
    // @return Bug The created Bug object.
    Bug createBug();

    //===============================================================================
    // @brief Creates a new Bug object from a Request object and writes it to Bug file
    // @return Bug The created Bug object.
    Bug createBugFromRequest(Request& reqObj);

    //===============================================================================
    // @brief Deletes a Bug object from the bug list by ID.
    // @return bool True if the bug was found and deleted, false otherwise.
    bool deleteBug();

    //===============================================================================
    // Customer operations
    // @brief Creates a new Customer object and adds it to the customer list.
    // @return Customer The created Customer object.
    Customer createCustomer();

    //===============================================================================
    // @brief Deletes a Customer object from the customer list by ID.
    // @return bool True if the customer was found and deleted, false otherwise.
    bool deleteCustomer();

    //===============================================================================
    // Request operations
    // @brief Creates a new Request object and adds it to the request list.
    // @return Request The created Request object.
    Request createRequest();

    //===============================================================================
    // @brief Deletes a Request object from the request list by ID.
    // @param requestID The ID of the request to delete.
    // @return bool True if the request was found and deleted, false otherwise.
    bool deleteRequest();

    //===============================================================================
    // @brief Modifies a Request Object from file
    // @return bool True if the request was modified, false otherwise.
    bool modifyRequest();

    //===============================================================================
    // Private helper functions to find objects by ID
 
    // @brief Finds a Product object by ID.
    // @param productID The ID of the product to find.
    // @return Product// Pointer to the found Product object, or nullptr if not found.
    Product findProduct();

    //===============================================================================
    // @brief Modifies a Bug object by ID.
    // @param bugID The ID of the bug to find.
    // @return Bug// Pointer to the found Bug object, or nullptr if not found.
    Bug modifyBug();

    //===============================================================================
    // @brief Finds a Customer object.
    // @return Request Object found.
    Customer findCustomer();

    //===============================================================================
    // @brief Finds a Request object.
    // @return Request Object found.
    Request findRequest();

    //===============================================================================
    // Reports bugs by Product ID
    // Prints all Bugs associated to console
    void report1();

    //===============================================================================
    // Reports bugs by severity
    // Prints all Bugs associated to console
    void report2();

    //===============================================================================
    // Reports bugs by severity
    // Prints all Bugs associated to console
    void report3();

    //===============================================================================
    // Prints all Products
    void printProducts();

private:
    // Placeholder variable
    Product product;
    Customer customer;
    Request request;
    Bug bug;
};