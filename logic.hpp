#ifndef LOGIC_HPP
#define LOGIC_HPP

#include "struct.hpp"
#include <vector>

extern std::vector<MenuItem> inventory;
extern std::vector<CartItem> cart;

int getRandomStock(int min, int max);
void addToCartLogic(int id, int qty);
bool attemptPurchase(int index, int qty); // Returns true if stock is sufficient
void clearCartLogic();

#endif
