#include "ui.hpp" // Declaration of functions
#include "logic.hpp" // UI needs access to Inventory/Cart to print them
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <limits>

using std::cout;
using std::cin;
using std::fixed;
using std::setprecision;
using std::numeric_limits;
using std::streamsize;
using namespace std::this_thread;
using namespace std::chrono;

// Helper for number input validation

int getValidatedNumber(const std::string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (!(cin >> value)) {
            cout << "\n!! Invalid input! Please enter a number. !!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            sleep_for(seconds(1));
            continue;
        }
        return value;
    }
} 

void displayMenu() {
    cout << "\n===== MAIN MENU =====\n";
    cout << "1. Place Order\n";
    cout << "2. View Cart\n";
    cout << "3. Checkout\n";
    cout << "4. Exit\n";
}

void displayInv() {
    cout << "\n===== MENU =====\n";
    for (const auto& item : inventory) {
        cout << item.id << ". " << item.name
            << " - " << fixed << setprecision(2) << item.price
            << " (" << item.stock << " left)\n";
    }
}

void viewCart(){
    cout << "\n===== YOUR CART =====\n";
    double total = 0.0;
    
    if (cart.empty()) {
        cout << " (Empty) \n";
        return;
    }

    for (const auto& c : cart) {
        size_t index = static_cast<size_t>(c.id - 1); 
        const auto& item = inventory[index];
        cout << c.quantity << " x " << item.name
             << " - " << c.subtotal << "\n";
        total += c.subtotal;
    }
    cout << "Total: " << total << "\n";
}


void takeOrder() {
    int id, qty;
    size_t index;

    while (true) {
        displayInv();
        cout << "7. Go Back to Main Menu\n";
        id = getValidatedNumber("Enter Item ID or 7 to go back: ");
        
        if (id == 7) return;

        if (id >= 1 && id <= static_cast<int>(inventory.size())) {
            index = static_cast<size_t>(id - 1);
            if (inventory[index].stock == 0) {
                cout << "\n!! Out of stock. !!\n";
                sleep_for(seconds(2));
                continue; 
            }
            break;
        } else {
            cout << "\n!! Invalid item ID. !!\n";
            sleep_for(seconds(2));
        }
    }

    while (true) {
        qty = getValidatedNumber("Enter quantity: ");
        if (qty <= 0) {
            cout << "!! Quantity must be positive. !!\n";
        } else if (inventory[index].stock < qty) {
            cout << "!! Insufficient stock. Available: " << inventory[index].stock << " !!\n";
        } else {
            break;
        }
        sleep_for(seconds(2));
    }

    if (attemptPurchase(static_cast<int>(index), qty)) {
        addToCartLogic(id, qty);
        cout << "Added to cart!\n";
    }
}

bool checkout(){
    viewCart();
    if (cart.empty()) {
        cout << "Your cart is empty! Cannot proceed.\n";
        return false;
    }
    cout << "Proceeding to checkout...\n";
    sleep_for(seconds(3));
    cout << "Checkout complete! Thank you!\n";
    
    clearCartLogic(); 
    return true;
}
