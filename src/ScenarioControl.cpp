#include "ScenarioControl.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "Product.h"
#include "Bug.h"
#include "Customer.h"
#include "Request.h"


// Helper Printing Functions
void printCustomerTableHeader() {
    std::cout << std::setw(20) << std::right << "Name"
        << std::setw(30) << std::right << "Email"
        << std::setw(20) << std::right << "Phone"
        << std::setw(15) << std::right << "Is Employee"
        << std::setw(25) << std::right << "Department" << std::endl;
    std::cout << std::string(110, '-') << std::endl;
}

void printCustomer(const Customer& customer) {
    std::cout << std::setw(20) << std::right << customer.getCustomerName()
        << std::setw(30) << std::right << customer.getEmail()
        << std::setw(20) << std::right << customer.getPhone()
        << std::setw(15) << std::right << (customer.getIsEmployee() ? "Yes" : "No")
        << std::setw(25) << std::right << (customer.getIsEmployee() ? customer.getDepartment() : "")
        << std::endl;
}

void printProductTableHeader() {
    std::cout << std::setw(15) << std::right << "Product ID"
        << std::setw(40) << std::right << "Name"
        << std::setw(40) << std::right << "Release Date"
        << std::setw(25) << std::right << "Is Anticipated Release" << std::endl;
    std::cout << std::string(120, '-') << std::endl;
}

void printProduct(const Product& product) {
    std::cout << std::setw(15) << std::right << product.getProductID()
        << std::setw(40) << std::right << product.getName()
        << std::setw(40) << std::right << product.getReleaseDate() // Assuming you have a method to get release as a string
        << std::setw(25) << std::right << (product.getIsAnticipatedRelease() ? "Yes" : "No") << std::endl;
}

// Constructor
ScenarioControl::ScenarioControl()
{
    // looks unncessary
    bug = Bug();
    product = Product();
    customer = Customer();
    request = Request();
}

// Product operations
Product ScenarioControl::createProduct()
{
    int productID;
    int releaseID;
    std::string name;
    std::string version;

    // TODO: should make the ID assignment automatic
    std::cout << "Enter Product ID: ";
    std::cin >> productID;
    std::cin.ignore(); // To ignore the newline character left by std::cin

    std::cout << "Enter Product Name: ";
    std::getline(std::cin, name);

    std::cout << "Enter Product Version: ";
    std::getline(std::cin, version);

    std::cout << "Enter Release ID: ";
    std::cin >> releaseID;

    Release tempRelease = Release::findReleaseRecord(releaseID);

    if (tempRelease.getReleaseID() == 0) {
        // then empty release returned - no such Release in file, create a Release object first
        // some temp variables to store release info
        
        int tempReleaseID;
        std::string tempVersion;
        std::string tempReleaseDate;

        std::cout << "No Release ID found - create a new Release" << std::endl; // TODO: ask if they want to try again or create new Release object
        std::cout << "Enter Release ID: ";
        std::cin >> tempReleaseID;
        std::cin.ignore(); // To ignore the newline character left by std::cin

        std::cout << "Enter Release Version: ";
        std::getline(std::cin, tempVersion);

        std::cout << "Enter Release Date: ";
        std::getline(std::cin, tempReleaseDate);

        tempRelease.setProductID(productID);        // productID already stored;
        tempRelease.setReleaseDate(tempReleaseDate);
        tempRelease.setReleaseID(tempReleaseID);
        tempRelease.setVersion(tempVersion);
    }

    Product newProduct = Product(productID, tempRelease, name, version);

    Product::writeProduct(newProduct);

    Product readProduct;

    Product::getNext(readProduct, 0);

    std::cout << readProduct.getName() << std::endl;
    std::cout << readProduct.getReleaseDate() << std::endl;

    return newProduct;
}

bool ScenarioControl::deleteProduct()
{
    int productID;

    std::cout << "Enter Product ID: ";
    std::cin >> productID;
    std::cin.ignore(); // To ignore the newline character left by std::cin

    product.deleteProductRecord(productID);

    return true;
}

// Bug operations
Bug ScenarioControl::createBug()
{
    int bugID;
    std::string description;
    std::string severity;
    std::string status;
    int productID;
    int releaseID;

    std::cout << "Enter Bug ID: ";
    std::cin >> bugID;  // TODO: ID needs to be static - we also might need to check if other bugs exist in file, and then start counting from there
    std::cin.ignore(); // To ignore the newline character left by std::cin

    std::cout << "Enter Bug Description: ";
    std::getline(std::cin, description);

    std::cout << "Enter Bug Severity: ";
    std::getline(std::cin, severity);

    std::cout << "Enter Bug Status: ";
    std::getline(std::cin, status);

    std::cout << "Enter product ID: ";
    std::cin >> productID;

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

    std::cout << "Enter release ID: ";          // TODO: remove this, since a product already has an associated release
    std::cin >> releaseID;

    Bug newBug = Bug(bugID, description, severity, status, productID, releaseID);

    Bug::writeBug(newBug);

    Bug readBug;

    Bug::getNext(readBug, 0);

    std::cout << readBug.getDescription() << std::endl;

    return newBug;
}

Bug ScenarioControl::createBugFromRequest(Request& reqObj)
{
    // TODO: check to make sure that if removing getReleaseID then we remove it here too
    Bug newBug = Bug(Bug::bugIDCount, reqObj.getDescription(), reqObj.getPriority(), reqObj.getStatus(), reqObj.getProductID(), reqObj.getReleaseID());
    Bug::writeBug(newBug);
    return newBug;
}

bool ScenarioControl::deleteBug()
{
    int bugID;
    std::cout << "Enter Bug ID: ";
    std::cin >> bugID;
    std::cin.ignore(); // To ignore the newline character left by std::cin

    bug.deleteBugRecord(bugID);

    return true;
}

// Customer operations
Customer ScenarioControl::createCustomer()
{
    std::string name;
    std::string phone;
    std::string email;

    std::cout << "Enter Customer Name: ";
    std::getline(std::cin, name);

    std::cout << "Enter Customer Phone: ";
    std::getline(std::cin, phone);

    std::cout << "Enter Customer Email: ";
    std::getline(std::cin, email);

    Customer newCustomer = Customer(name, phone, email);
    std::cout << "Customer created successfully!" << std::endl;

    Customer::writeCustomer(newCustomer);
    return Customer();
}

bool ScenarioControl::deleteCustomer()
{
    std::string name;

    std::cout << "Enter Customer Name: ";
    std::getline(std::cin, name);
    customer.deleteCustomerRecord(name);

    return false;
}

// Request operations
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

    std::cout << "Enter Product ID: ";
    std::cin >> productID;
    std::cin.ignore();

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

    std::cout << "Enter Customer Name: ";
    std::getline(std::cin, customerName); 

    Customer tempCustomer = Customer::findCustomerRecord(customerName);

    if (tempCustomer.getCustomerName() == "") {
        // no customer with that name found
        createCustomer();
    }
    else {
        std::cout << "Found it: " << tempCustomer.getPhone() << std::endl;
    }

    Request newRequest = Request(Request::requestIDCount, description, priority, status, dateOfRequest, productID, customerName, tempProduct.getReleaseID());

    Request::writeRequest(newRequest);
    std::cout << "Request created successfully!" << std::endl;


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

bool ScenarioControl::deleteRequest()
{
    int requestID;

    std::cout << "Enter Request ID: ";
    std::cin >> requestID;
    std::cin.ignore();

    request.deleteRequestRecord(requestID);

    return true;
}

// TODO: modify request and modify bug
bool ScenarioControl::modifyRequest()
{
    int requestID;

    std::cout << "Enter Request ID: ";
    std::cin >> requestID;
    std::cin.ignore();

    request.deleteRequestRecord(requestID);

    return true;
}

// Private helper functions to find objects by ID
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

Bug ScenarioControl::modifyBug()
{
    int bugID;

    std::cout << "Enter Bug ID: ";
    std::cin >> bugID;
    std::cin.ignore();
    // Function body not implemented
    return Bug::findBugRecord(bugID);
}

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


Request ScenarioControl::findRequest()
{
    int requestID;

    std::cout << "Enter request ID: ";
    std::cin >> requestID;
    std::cin.ignore();
    return request.findRequestRecord(requestID);
}

void ScenarioControl::report1()
{
    // TODO: fix - reaches file end prematurely 
    int productID;

    std::cout << "Enter Product ID: ";
    std::cin >> productID;
    std::cin.ignore();
    // Function body not implemented
    Bug::printBugsByProduct(productID);
}

void ScenarioControl::report2()
{
    // TODO: fix - reaches file end prematurely 
    std::string severity;

    std::cout << "Enter Severity: ";
    std::cin >> severity;
    std::cin.ignore();
    // Function body not implemented
    Bug::printBugsBySeverity(severity);
}
