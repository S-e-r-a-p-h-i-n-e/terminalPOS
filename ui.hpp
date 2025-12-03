#ifndef UI_HPP
#define UI_HPP

#include <string>

void displayMenu();
void displayInv();
void takeOrder();
void viewCart();
bool checkout();
int getValidatedNumber(const std::string& prompt);

#endif
