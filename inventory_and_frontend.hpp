#ifndef FRONTEND_HPP
#define FRONTEND_HPP
#include <iostream>  // for console input and output
#include <vector> // for the menu and cart storage
#include <string> // for std::string
#include <chrono> // for time in sleep functionality
#include <thread> // for sleep functionality
#include <cctype> // to check if character is digit
#include <iomanip> // for setting decimal precision

using std::cout;                   
using std::cin;
using std::vector;        
using std::string;        
using std::fixed;                 // very polluted usage of namespace but still safer than using namespace std so i dont really mind
using std::setprecision;
using std::numeric_limits;
using std::streamsize;
using namespace std::this_thread; 
using namespace std::chrono; 

struct MenuItem {
    int id;
    string name;
    double price;
    int stock;
};

struct CartItem {
    int id;
    int quantity;
    double subtotal;
};

inline vector<MenuItem> inventory = {
    {1, "Asus ROG Strix GeForce RTX 3090 EVA Edition", 2050.00, 0},
    {2, "Asus ROG Strix XG27AQM EVA Edition", 650.00, 16},
    {3, "Asus ROG Strix Helios EVA Edition", 1000.00, 0},
    {4, "Asus ROG MAXIMUS Z690 HERO EVA Edition", 1600.00, 13},
    {5, "Asus ROG Thor 1000W Platinum II EVA Edition", 700.00, 10},
    {6, "Intel Core i9-14900K", 450.00, 4},
    
};

inline vector<CartItem> cart;

inline int getValidatedNumber(const string& prompt) { // helper function to validate number inputs just so
    int value;                                        // "if (!(cin >> var)) { cin.clear(); cin.ignore(); etc etc }"
    while (true) {                                    // isnt repeated EVERYWHERE
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

inline void displayMenu() {
    cout << "\n===== MAIN MENU =====\n";
    cout << "1. Place Order\n";
    cout << "2. View Cart\n";
    cout << "3. Checkout\n";
    cout << "4. Exit\n";
}
inline void displayInv() {
    cout << "\n===== MENU =====\n";
    for (auto& item : inventory) {
        cout << item.id << ". " << item.name
            << " - " << fixed << setprecision(2) << item.price
            << " (" << item.stock << " left)\n";
    }
}

inline void addToCart(int id, int qty) {
    size_t index = static_cast<size_t>(id - 1);
    // Check if item is already in cart
    for (auto& c : cart) {
        if (c.id == id) {
            c.quantity += qty;
            c.subtotal = c.quantity * inventory[index].price;
            return;
        }
    }
    // If not in cart, add new entry
    cart.push_back({id, qty, qty * inventory[index].price});
}

inline void takeOrder() {
    int id, qty;
    size_t index;

    while (true) {
        displayInv();
        cout << "7. Go Back to Main Menu\n";
        id = getValidatedNumber("Enter Item ID or 7 to go back: ");
        
        if (id == 7) return;
        else if (id == 3 || id == 1) {
            cout << "\n!! Sorry, this item is out of stock. Please choose another item. !!\n";
            sleep_for(seconds(1));
        }
        else if (id >= 1 && id <= static_cast<int>(inventory.size())) {
            index = static_cast<size_t>(id - 1);
            break;
        } else {
            cout << "\n!! Invalid item ID. Please try again. !!\n";
            sleep_for(seconds(1));
        }
    }

    while (true) {
        qty = getValidatedNumber("Enter quantity: ");
        if (qty <= 0) {
            cout << "!! Quantity must be more than zero. !!\n";
        } else if (qty > inventory[index].stock) {
            cout << "!! Insufficient stock. Available: " << inventory[index].stock << " !!\n";
        } else {
            break;
        }
        sleep_for(seconds(1));
    }

    inventory[index].stock -= qty;
    addToCart(id, qty);
    cout << "Added to cart! Subtotal: " << fixed << setprecision(2) << qty * inventory[index].price << "\n";
}

inline void viewCart(){
    cout << "\n===== YOUR CART =====\n";
    double total = 0.0;

    for (auto& c : cart) {
        size_t index = static_cast<size_t>(c.id - 1); 
        auto& item = inventory[index];
        cout << c.quantity << " x " << item.name
             << " - " << c.subtotal << "\n";
        total += c.subtotal;
    }
    cout << "Total: " << total << "\n";
}

inline void checkout(){
    viewCart();
    cout << "Proceeding to checkout...\n";
    sleep_for(seconds(3));
    cout << "Checkout complete! Thank you for your purchase!\n";
    cart.clear();
}

#endif

// explanation of the code:
// this header file is essentially the backbone of the application
// the main reason I used a header was to declutter main.cpp and make it more readable
