/// 
 // Filename: main.cpp
 // Description: Main driver for our program
 // 
 // Version History:
 // 1.0 2024-07-02 - Initial version
 ///

#include <iostream>
#include <limits>
#include "ScenarioControl.h"


#include <fstream>

//================================
// Application Menu
//================================
void ShowMenu() {
    std::cout << "Application Menu" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "1. Create Request" << std::endl;
    std::cout << "2. Modify Request" << std::endl;
    std::cout << "3. Modify Bug" << std::endl;
    std::cout << "4. Delete Bug" << std::endl;
    std::cout << "5. Report all Products" << std::endl;
    std::cout << "6. Create a Product" << std::endl;
    std::cout << "7. Create a Customer" << std::endl;
    std::cout << "8. Check if a Customer Exists" << std::endl;
    std::cout << "9. Check if Product exists" << std::endl;
    std::cout << "10. Report Bugs by Product" << std::endl;
    std::cout << "11. Report Bugs by Severity" << std::endl;
    std::cout << "12. Report Bugs by Status" << std::endl;
    
}


//================================
// Main Function
//================================
int main() {

    ScenarioControl control = ScenarioControl();

    int choice;

    // Main menu loop
    do {
        ShowMenu();
        std::cout << "Enter your choice (0-12): ";
        std::cin >> choice;

        // Update the static IDs with Last ID count
        Bug::readLastID();
        Request::readLastID();

        switch (choice) {
        case 0:
            std::cout << "Exiting the program..." << std::endl;
            return 0;
        case 1:
            std::cout << "You selected Create Request" << std::endl;
            control.createRequest();
            break;
        case 2:
            std::cout << "You selected Modify Request" << std::endl;
            control.modifyRequest();
            break;
        case 3:
            std::cout << "You selected Modify Bug" << std::endl;
            control.modifyBug();
            break;
        case 4:
            std::cout << "You selected Delete Bug" << std::endl;
            control.deleteBug();
            break;
        case 5:
            std::cout << "You selected Report all Products" << std::endl;
            control.printProducts();
            break;
        case 6:
            std::cout << "You selected Create Product" << std::endl;
            control.createProduct();
            break;
        case 7:
            std::cout << "You selected Create Customer" << std::endl;
            control.createCustomer();
            break;
        case 8:
            std::cout << "You selected Check if Customer Exists" << std::endl;
            control.findCustomer();
            break;
        case 9:
            std::cout << "You selected Check if Product Exists" << std::endl;
            control.findProduct();
            break;
        case 10:
            std::cout << "You selected Report Bugs by Product" << std::endl;
            control.report1();
            break;
        case 11:
            std::cout << "You selected Report Bugs by Severity" << std::endl;
            control.report2();
            break;
        case 12:
            std::cout << "You selected Report Bugs by Status" << std::endl;
            control.report3();
            break;
        default:
            std::cout << "Invalid choice. Please select a valid option (1-5)." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = 0; // reset choice, goes back up
            break;
        }

        std::cout << std::endl; // Print a new line for better readability
    } while (choice != 5);

    return 0;
}


///
 // Coding Convention
 //
 // 1. Each major section of a listing should be separated by a dividing comment line.
 //    e.g. //================================ or //-------------------------------------
 //    For classes, put public members first, then protected, then private.
 //
 // 2. Each module .cpp will start with a comment stating that file’s name, then should have a 
 //    paragraph-long comment describing the purpose of the class/module. After that, it should have 
 //    a Version History section, with oldest to newest.
 //
 // 3. Use descriptive names for all exported program entities, modules, and files. The first letter
 //    of a type or class is always upper case. Each parameter line should include the unit of measure
 //    for each parameter (e.g. radians or degrees, Celsius or Fahrenheit) if relevant. Variables will
 //    follow camel case convention. For functions, maximum 5 arguments in one line.
 //
 // 4. Indenting, spacing, and punctuation conventions:
 //    - Use tabs for indentation.
 //    - The opening brace “{“ goes on a new line by itself.
 //    - The body of an else clause is indented 4 spaces.
 //    - Surround “=” with spaces, and use spaces after commas and colons.
 ///