#ifndef STRUCT_HPP
#define STRUCT_HPP

#include <string>

struct MenuItem {
    int id;
    std::string name;
    double price;
    int stock;
};

struct CartItem {
    int id;
    int quantity;
    double subtotal;
};

#endif
