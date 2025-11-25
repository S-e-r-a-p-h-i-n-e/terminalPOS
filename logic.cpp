#include "logic.hpp" // Declaration of inventory and cart
#include <random> // for randomized stocks

std::vector<CartItem> cart;

// Helper for the inventory initialization below
int getRandomStock(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

std::vector<MenuItem> inventory = {
    {1, "Asus ROG Strix GeForce RTX 3090 EVA Edition", 2050.00, getRandomStock(0, 5)},
    {2, "Asus ROG Strix XG27AQM EVA Edition", 650.00, getRandomStock(3, 16)},
    {3, "Asus ROG Strix Helios EVA Edition", 1000.00, getRandomStock(0, 8)},
    {4, "Asus ROG MAXIMUS Z690 HERO EVA Edition", 1600.00, getRandomStock(4, 13)},
    {5, "Asus ROG Thor 1000W Platinum II EVA Edition", 700.00, getRandomStock(0, 10)},
    {6, "Intel Core i9-14900K", 450.00, getRandomStock(5, 17)}
};


void addToCartLogic(int id, int qty) {
    size_t index = static_cast<size_t>(id - 1);

    // Check if item is already in cart

    for (auto& c : cart) {
        if (c.id == id) {
            c.quantity += qty;
            c.subtotal = c.quantity * inventory[index].price;
            return;
        }
    }
    
    cart.push_back({id, qty, qty * inventory[index].price});
}

bool attemptPurchase(int index, int qty) {
    if (inventory[index].stock >= qty) {
        inventory[index].stock -= qty;
        return true;
    }
    return false;
}

void clearCartLogic() {
    cart.clear();
}
