#include "ui.hpp"
#include <iostream>

int main() {
    int choice;

    while (true) {
        displayMenu();
        choice = getValidatedNumber("Select an option: ");
        
        switch (choice) {
            case 1:
                takeOrder();
                break;
            case 2:
                viewCart();
                break;
            case 3:
                checkout();
                return 0;
            case 4:
                std::cout << "Thank you for visiting! Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}

// finally seperated ui and logic jesus christ, finally :pain:

