#include "ScenarioControl.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <limits>

#include "Product.h"
#include "Bug.h"
#include "Customer.h"
#include "Request.h"

//===============================================================================
// Helper Printing Functions
void printCustomerTableHeader() {
    std::cout << std::setw(20) << std::right << "Name"
        << std::setw(30) << std::right << "Email"
        << std::setw(20) << std::right << "Phone"
        << std::setw(15) << std::right << "Is Employee"
        << std::setw(25) << std::right << "Department" << std::endl;
    std::cout << std::string(110, '-') << std::endl;
}

//===============================================================================
void printCustomer(const Customer& customer) {
    std::cout << std::setw(20) << std::right << customer.getCustomerName()
        << std::setw(30) << std::right << customer.getEmail()
        << std::setw(20) << std::right << customer.getPhone()
        << std::setw(15) << std::right << (customer.getIsEmployee() ? "Yes" : "No")
        << std::setw(25) << std::right << (customer.getIsEmployee() ? customer.getDepartment() : "")
        << std::endl;
}

//===============================================================================
void printProductTableHeader() {
    std::cout << std::setw(15) << std::right << "Product ID"
        << std::setw(40) << std::right << "Name"
        << std::setw(40) << std::right << "Release Date"
        << std::setw(25) << std::right << "Is Anticipated Release" << std::endl;
    std::cout << std::string(120, '-') << std::endl;
}

//===============================================================================
void printProduct(const Product& product) {
    std::cout << std::setw(15) << std::right << product.getProductID()
        << std::setw(40) << std::right << product.getName()
        << std::setw(40) << std::right << product.getReleaseDate() // Assuming you have a method to get release as a string
        << std::setw(25) << std::right << (product.getIsAnticipatedRelease() ? "Yes" : "No") << std::endl;
}

//===============================================================================
void printReleaseTableHeader() {
    std::cout << std::setw(15) << std::right << "Release ID"
        << std::setw(15) << std::right << "Product ID"
        << std::setw(30) << std::right << "Version"
        << std::setw(30) << std::right << "Release Date" << std::endl;
    std::cout << std::string(90, '-') << std::endl;
}

//===============================================================================
void printRelease(const Release& release) {
    std::cout << std::setw(15) << std::right << release.getReleaseID()
        << std::setw(15) << std::right << release.getProductID()
        << std::setw(30) << std::right << release.getVersion()
        << std::setw(30) << std::right << release.getReleaseDate() << std::endl;
}

//===============================================================================
// Constructor
ScenarioControl::ScenarioControl()
{
    bug = Bug();
    product = Product();
    customer = Customer();
    request = Request();
}

//===============================================================================
// Product operations
// @brief Creates a new Product object and adds it to the product list.
// @param productID The ID of the product.
// @param name The name of the product.
// @param version The version of the product.
// @return Product The created Product object.
Product ScenarioControl::createProduct()
{
    int releaseID;
    std::string name;
    std::string version;
    std::string anticipated;


    std::cin.ignore();
    std::cout << "Enter Product Name: ";
    std::getline(std::cin, name);

    std::cout << "Enter Product Version: ";
    std::getline(std::cin, version);

    while (true) {
        std::cout << "Enter Release ID: ";
        std::cin >> releaseID;

        // Check if the input is valid
        if (std::cin.fail()) {
            // Clear the error flag
            std::cin.clear();
            // Ignore the invalid input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid integer." << std::endl;
        }
        else {
            // If input is valid, break out of the loop
            break;
        }
    }

    Release tempRelease = Release::findReleaseRecord(releaseID);

    if (tempRelease.getReleaseID() == 0) {
        // then empty release returned - no such Release in file, create a Release object first
        // some temp variables to store release info

        int tempReleaseID;
        std::string tempVersion;
        std::string tempReleaseDate;

        std::cout << "No Release ID found - create a new Release" << std::endl;
        std::cout << "Enter Release ID: ";
        std::cin >> tempReleaseID;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Enter Release Version: ";
        std::getline(std::cin, tempVersion);

        std::cout << "Enter Release Date: ";
        std::getline(std::cin, tempReleaseDate);

        tempRelease.setProductID(Product::productIDCount);        // productID already stored;
        tempRelease.setReleaseDate(tempReleaseDate);
        tempRelease.setReleaseID(tempReleaseID);
        tempRelease.setVersion(tempVersion);

        Release::writeRelease(tempRelease);
    }
    else {
        std::cout << "Found Release with ID!" << std::endl;
        printReleaseTableHeader();
        printRelease(tempRelease);
        std::cin.ignore();
    }

    Product newProduct = Product(Product::productIDCount, tempRelease, name, version);

    while (true) {
        std::cout << "Enter if Release is Anticipated Release (Release date in the future)? (y/n): ";
        std::getline(std::cin, anticipated);

        if (anticipated == "y") {
            newProduct.setAnticipatedRelease(true);
            std::cout << "Product created successfully!" << std::endl;
            break;
        }
        else if (anticipated == "n") {
            newProduct.setAnticipatedRelease(false);
            std::cout << "Product created successfully!" << std::endl;
            break;
        }
        else {
            std::cout << "Invalid Input" << std::endl;
        }
    }

    Product::writeProduct(newProduct);

    return newProduct;
}

//===============================================================================
// Bug operations
// @brief Creates a new Bug object and adds it to the Bug file
// @param bugID The ID of the bug.
// @param description The description of the bug.
// @param severity The severity of the bug.
// @param status The status of the bug.
// @return Bug The created Bug object.
Bug ScenarioControl::createBug()
{
    std::string description;
    std::string severity;
    std::string status;
    int productID;

    std::cout << "Enter Bug Description: ";
    std::getline(std::cin, description);

    std::cout << "Enter Bug Severity: ";
    std::getline(std::cin, severity);

    std::cout << "Enter Bug Status: ";
    std::getline(std::cin, status);

    while (true) {
        std::cout << "Enter Product ID: ";
        std::cin >> productID;

        // Check if the input is valid
        if (std::cin.fail()) {
            // Clear the error flag
            std::cin.clear();
            // Ignore the invalid input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid integer." << std::endl;
        }
        else {
            // If input is valid, break out of the loop
            break;
        }
    }

    Product tempProduct = Product::findProductRecord(productID);

    if (tempProduct.getProductID() == 0) {
        // no such product fonud
        std::cout << "No Product matches that ID! Please create one" << std::endl;
        createProduct();
    }
    else {
        std::cout << "Found Product! ";
        printProductTableHeader();
        printProduct(tempProduct);

    }

    Bug newBug = Bug(Bug::bugIDCount, description, severity, status, productID, tempProduct.getReleaseID());

    Bug::writeBug(newBug);

    return newBug;
}

//===============================================================================
// @brief Creates a new Bug object from a Request object and writes it to Bug file
// @param reqObj - Request Object containing all information for a Bug
// @return Bug The created Bug object.
Bug ScenarioControl::createBugFromRequest(Request& reqObj)
{
    Bug newBug = Bug(Bug::bugIDCount, reqObj.getDescription(), reqObj.getPriority(), reqObj.getStatus(), reqObj.getProductID(), reqObj.getReleaseID());
    Bug::writeBug(newBug);
    return newBug;
}

//===============================================================================
// @brief Deletes a Bug object from the bug list by ID.
// @param bugID The ID of the bug to delete.
// @return bool True if the bug was found and deleted, false otherwise.
bool ScenarioControl::deleteBug()
{
    int bugID;
    std::cout << "Enter Bug ID: ";
    std::cin >> bugID;
    std::cin.ignore(); // To ignore the newline character left by std::cin

    bug.deleteBugRecord(bugID);
    std::cout << "Bug " << bugID << " deleted!" << std::endl;
    return true;
}

//===============================================================================
// Customer operations
// @brief Creates a new Customer object and adds it to the customer list.
// @param customerID The ID of the customer.
// @param name The name of the customer.
// @param contactInfo The contact information of the customer.
// @return Customer The created Customer object.
Customer ScenarioControl::createCustomer()
{
    std::string name;
    std::string phone;
    std::string email;
    std::string isEmployee;

    std::cin.ignore();

    std::cout << "Enter Customer Name: ";
    std::getline(std::cin, name);

    std::cout << "Enter Customer Phone: ";
    std::getline(std::cin, phone);

    std::cout << "Enter Customer Email: ";
    std::getline(std::cin, email);

    std::cout << "Is this customer an employee? (y/n): ";
    std::getline(std::cin, isEmployee);

    Customer newCustomer = Customer(name, phone, email);
    std::cout << "Customer created successfully!" << std::endl;

    while (true) {
        if (isEmployee == "y") {
            newCustomer.setIsEmployee(true);
            std::string department;
            std::cout << "Department: ";
            std::getline(std::cin, department);
            newCustomer.setDepartment(department);
            break;
        }
        else if (isEmployee == "n") {
            std::cout << "Department not required!" << std::endl;
            break;
        }
        else {
            std::cout << "Invalid Input!" << std::endl;
        }
    }

    Customer::writeCustomer(newCustomer);
    return Customer();
}

//===============================================================================
// @brief Deletes a Customer object from the customer list by ID.
// @param customerID The ID of the customer to delete.
// @return bool True if the customer was found and deleted, false otherwise.
bool ScenarioControl::deleteCustomer()
{
    std::string name;

    std::cout << "Enter Customer Name: ";
    std::getline(std::cin, name);
    customer.deleteCustomerRecord(name);

    return false;
}

//===============================================================================
// Request operations
// @brief Creates a new Request object and adds it to the request list.
// @return Request The created Request object.
Request ScenarioControl::createRequest()
{
    std::string description;
    std::string priority;
    std::string status;
    std::string dateOfRequest;
    int productID;
    std::string customerName;

    std::cin.ignore();

    std::cout << "Enter Request Description: ";
    std::getline(std::cin, description);

    std::cout << "Enter Request Priority: ";
    std::getline(std::cin, priority);

    std::cout << "Enter Request Status: ";
    std::getline(std::cin, status);

    std::cout << "Enter Date of Request: ";
    std::getline(std::cin, dateOfRequest);

    while (true) {
        std::cout << "Enter Product ID: ";
        std::cin >> productID;

        // Check if the input is valid
        if (std::cin.fail()) {
            // Clear the error flag
            std::cin.clear();
            // Ignore the invalid input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid integer." << std::endl;
        }
        else {
            // If input is valid, break out of the loop
            break;
        }
    }

    Product tempProduct = Product::findProductRecord(productID);

    if (tempProduct.getProductID() == 0) {
        // no such product fonud
        std::cout << "No Product matches that ID! Please create one" << std::endl;
        createProduct();
    }
    else {
        std::cout << "Found Product! " << std::endl;
        printProductTableHeader();
        printProduct(tempProduct);

    }

    std::cin.ignore();
    std::cout << "Enter Customer Name: ";
    std::getline(std::cin, customerName); 

    Customer tempCustomer = Customer::findCustomerRecord(customerName);

    if (tempCustomer.getCustomerName() == "") {
        // no customer with that name found
        createCustomer();
    }
    else {
        std::cout << "Found Customer: " << std::endl;
        printCustomerTableHeader();
        printCustomer(tempCustomer);
    }

    Request newRequest = Request(Request::requestIDCount, description, priority, status, dateOfRequest, productID, customerName, tempProduct.getReleaseID());

    Request::writeRequest(newRequest);
    std::cout << "Request created successfully! ID: " << Request::requestIDCount << std::endl;

    while (true) {
        std::string val;
        std::cout << "Do you want to convert the current Request into a Bug (y/n): ";
        std::getline(std::cin, val);

        if (val == "y") {
            createBugFromRequest(newRequest);
            std::cout << "Bug created successfully!" << std::endl;
            break;
        }
        else if (val == "n") {
            std::cout << "Request ID: " << newRequest.getRequestID() << " saved, but no Bug created!" << std::endl;
            break;
        }
        else {
            std::cout << "Invalid Input" << std::endl;
        }
    }

    return newRequest;
}

//===============================================================================
// @brief Deletes a Request object from the request list by ID.
// @return bool True if the request was found and deleted, false otherwise.
bool ScenarioControl::deleteRequest()
{
    int requestID;

    std::cout << "Enter Request ID: ";
    std::cin >> requestID;
    std::cin.ignore();

    return request.deleteRequestRecord(requestID);;
}

//===============================================================================
// @brief Modifies a Request Object from file
// @return bool True if the request was modified, false otherwise.
bool ScenarioControl::modifyRequest()
{
    int requestID;

    while (true) {
        std::cout << "Enter Request ID: ";
        std::cin >> requestID;

        // Check if the input is valid
        if (std::cin.fail()) {
            // Clear the error flag
            std::cin.clear();
            // Ignore the invalid input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid integer." << std::endl;
        }
        else {
            // If input is valid, break out of the loop
            break;
        }
    }

    Request tempRequest = Request::findRequestRecord(requestID);            // Make a copy
    Request::deleteRequestRecord(requestID);                        // Delete the current one from Record 

    // Modify the current Bug (without ID)

    std::string description;
    std::string severity;
    std::string status;
    int productID;

    bool done = false;
    while (!done) {

        std::cout << "1. Description" << std::endl;
        std::cout << "2. Severity" << std::endl;
        std::cout << "3. Status" << std::endl;
        std::cout << "4. Product ID" << std::endl;
        std::cout << "5. Convert to Bug" << std::endl;
        std::cout << "6. Done" << std::endl;


        int choice;
        std::cout << "Select the attribute you want to change: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the newline character from the input buffer

        switch (choice) {
            case 1: {
                std::cout << "Enter new Description: ";
                std::getline(std::cin, description);
                tempRequest.setDescription(description);
                break;
            }
            case 2: {
                std::cout << "Enter new Severity: ";
                std::getline(std::cin, severity);
                tempRequest.setPriority(severity);
                break;
            }
            case 3: {
                std::cout << "Enter new Status: ";
                std::getline(std::cin, status);
                tempRequest.setStatus(status);
                break;
            }
            case 4: {
                int productID;
                while (true) {
                    std::cout << "Enter new Product ID: ";
                    std::cin >> productID;

                    // Check if the input is valid
                    if (std::cin.fail()) {
                        // Clear the error flag
                        std::cin.clear();
                        // Ignore the invalid input
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input. Please enter a valid integer." << std::endl;
                    }
                    else {
                        // If input is valid, break out of the loop
                        tempRequest.setProductID(productID);
                        break;
                    }
                }
                break;
            }
            case 5: {
                while (true) {
                    std::string val;
                    std::cout << "Do you want to convert the current Request into a Bug (y/n): ";
                    std::getline(std::cin, val);

                    if (val == "y") {
                        createBugFromRequest(tempRequest);
                        std::cout << "Bug created successfully!" << std::endl;
                        break;
                    }
                    else if (val == "n") {
                        std::cout << "Request ID: " << tempRequest.getRequestID() << " saved, but no Bug created!" << std::endl;
                        break;
                    }
                    else {
                        std::cout << "Invalid Input" << std::endl;
                    }
                }
            }
            case 6: {
                done = true; // Exit the loop
                std::cout << "Changes confirmed." << std::endl;
                break;
            }
            default: {
                std::cout << "Invalid choice. Please select again." << std::endl;;
                break;
            }
        }
    }

    Request::writeRequest(tempRequest);
    return true;
}

//===============================================================================
// Private helper function to find objects by ID
// @brief Finds a Product object by ID.
// @return Product// Pointer to the found Product object, or nullptr if not found.
Product ScenarioControl::findProduct()
{
    int productID;

    std::cout << "Enter Product ID: ";
    std::cin >> productID;
    std::cin.ignore();

    Product tempProduct = product.findProductRecord(productID);
    if (tempProduct.getProductID() == 0) {
        std::cout << "No Product found that matches that ID!" << std::endl;
    } 
    else {
        printProductTableHeader();
        printProduct(tempProduct);
    }
    return tempProduct;
}

//===============================================================================
// @brief Modifies Bug by ID
// @return Return Bug of the modified Bug.
Bug ScenarioControl::modifyBug()
{
    int bugID;

    while (true) {
        std::cout << "Enter Bug ID: ";
        std::cin >> bugID;

        // Check if the input is valid
        if (std::cin.fail()) {
            // Clear the error flag
            std::cin.clear();
            // Ignore the invalid input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid integer." << std::endl;
        }
        else {
            // If input is valid, break out of the loop
            break;
        }
    }
    
    Bug tempBug = Bug::findBugRecord(bugID);            // Make a copy
    Bug::deleteBugRecord(bugID);                        // Delete the current one from Record 

    // Modify the current Bug (without ID)

    std::string description;
    std::string severity;
    std::string status;
    int productID;

    bool done = false;
    while (!done) {
        
        std::cout << "1. Description" << std::endl;
        std::cout << "2. Severity" << std::endl;
        std::cout << "3. Status" << std::endl;
        std::cout << "4. Product ID" << std::endl;
        std::cout << "5. Done" << std::endl;


        int choice;
        std::cout << "Select the attribute you want to change: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the newline character from the input buffer

        switch (choice) {
            case 1: {
                std::cout << "Enter new Description: ";
                std::getline(std::cin, description);
                tempBug.setDescription(description);
                break;
            }
            case 2: {
                std::cout << "Enter new Severity: ";
                std::getline(std::cin, severity);
                tempBug.setSeverity(severity);
                break;
            }
            case 3: {
                std::cout << "Enter new Status: ";
                std::getline(std::cin, status);
                tempBug.setStatus(status);
                break;
            }
            case 4: {
                int productID;
                while (true) {
                    std::cout << "Enter new Product ID: ";
                    std::cin >> productID;

                    // Check if the input is valid
                    if (std::cin.fail()) {
                        // Clear the error flag
                        std::cin.clear();
                        // Ignore the invalid input
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input. Please enter a valid integer." << std::endl;
                    }
                    else {
                        // If input is valid, break out of the loop
                        tempBug.setProductID(productID);
                        break;
                    }
                }
                break;
            }
            case 5: {
                done = true; // Exit the loop
                std::cout << "Changes confirmed." << std::endl;
                break;
            }
            default: {
                std::cout << "Invalid choice. Please select again." << std::endl;;
                break;
            }
        }
    }

    Bug::writeBug(tempBug);
    return bug;
}

//===============================================================================
// @brief Finds a Customer object.
// @return Request Object found.
Customer ScenarioControl::findCustomer()
{
    std::cin.ignore();
    std::string customerName;

    std::cout << "Enter Customer Name: ";
    std::getline(std::cin, customerName);

    Customer tempCustomer = customer.findCustomerRecord(customerName);

    if (tempCustomer.getCustomerName() == "") {
        // no such customer found
        std::cout << "No Coustomer with that name found! " << std::endl;
    }
    else {
        // Print header
        printCustomerTableHeader();

        // Print customer details
        printCustomer(tempCustomer);
    }

    return tempCustomer;
}

//===============================================================================
// @brief Finds a Request object.
// @return Request Object found.
Request ScenarioControl::findRequest()
{
    int requestID;

    std::cout << "Enter request ID: ";
    std::cin >> requestID;
    std::cin.ignore();
    return request.findRequestRecord(requestID);
}

//===============================================================================
// Reports bugs by Product ID
// Prints all Bugs associated to console
void ScenarioControl::report1()
{
    int productID;

    std::cout << "Enter Product ID: ";
    std::cin >> productID;
    std::cin.ignore();

    Bug::printBugsByProduct(productID);
}

//===============================================================================
// Reports bugs by severity
// Prints all Bugs associated to console
void ScenarioControl::report2()
{
    std::string severity;

    std::cin.ignore();
    std::cout << "Enter Severity: ";
    std::getline(std::cin, severity);
    // Function body not implemented
    Bug::printBugsBySeverity(severity);
}

//===============================================================================
// Reports bugs by severity
// Prints all Bugs associated to console
void ScenarioControl::report3()
{
    std::string status;

    std::cin.ignore();
    std::cout << "Enter Severity: ";
    std::getline(std::cin, status);

    Bug::printBugsByStatus(status);
}

//===============================================================================
// Prints all Products
void ScenarioControl::printProducts()
{
    Product::printAllProducts();
}

