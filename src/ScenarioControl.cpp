#include "ScenarioControl.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Product.h"
#include "Bug.h"
#include "Customer.h"
#include "Request.h"


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
    std::string name;
    std::string version;

    std::cout << "Enter Product ID: ";
    std::cin >> productID;
    std::cin.ignore(); // To ignore the newline character left by std::cin

    std::cout << "Enter Product Name: ";
    std::getline(std::cin, name);

    std::cout << "Enter Product Version: ";
    std::getline(std::cin, version);

    // TODO: simple release; change later
    Release r = Release();

    Product newProduct = Product(productID, r, name, version);

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
    std::cin >> bugID;                      // TODO: ID needs to be static - we also might need to check if other bugs exist in file, and then start counting from there
    std::cin.ignore(); // To ignore the newline character left by std::cin

    std::cout << "Enter Bug Description: ";
    std::getline(std::cin, description);

    std::cout << "Enter Bug Severity: ";
    std::getline(std::cin, severity);

    std::cout << "Enter Bug Status: ";
    std::getline(std::cin, status);

    std::cout << "Enter product ID: ";
    std::cin >> productID;

    std::cout << "Enter release ID: ";
    std::cin >> releaseID;

    Bug newBug = Bug(bugID, description, severity, status, productID, releaseID);

    Bug::writeBug(newBug);

    Bug readBug;

    Bug::getNext(readBug, 0);

    std::cout << readBug.getDescription() << std::endl;

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
    int customerID;
    std::string name;
    std::string phone;
    std::string email;

    std::cout << "Enter Customer ID: ";
    std::cin >> customerID;
    std::cin.ignore(); // To ignore the newline character left by std::cin

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
    int requestID;
    std::string description;
    std::string priority;
    std::string status;
    std::string dateOfRequest;
    int productID;
    std::string customerName;
    int releaseID;

    std::cout << "Enter Request ID: ";
    std::cin >> requestID;
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

    std::cout << "Enter Customer Name: ";
    std::getline(std::cin, customerName);

    std::cout << "Enter Release ID: ";
    std::cin >> releaseID;

    Request newRequest = Request(requestID, description, priority, status, dateOfRequest, productID, customerName, releaseID);
    std::cout << "Request created successfully!" << std::endl;
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
    // Function body not implemented
    return product.findProductRecord(productID);
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
    std::string customerName;

    std::cout << "Enter Request Description: ";
    std::getline(std::cin, customerName);

    return customer.findCustomerRecord(customerName);
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
    int productID;

    std::cout << "Enter Product ID: ";
    std::cin >> productID;
    std::cin.ignore();
    // Function body not implemented
    Bug::printBugsByProduct(productID);
}

void ScenarioControl::report2()
{
    std::string severity;

    std::cout << "Enter Severity: ";
    std::cin >> severity;
    std::cin.ignore();
    // Function body not implemented
    Bug::printBugsBySeverity(severity);
}
