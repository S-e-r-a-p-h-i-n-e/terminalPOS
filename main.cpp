#include "inventory_and_frontend.hpp" // name is self explanatory

int main(){
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
                cout << "Thank you for visiting! Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    };
}

// tried to seperate inventory and ui as two different headers but failed miserably :c , almost went insane trying to do it, good lord
