#include "product.h"

Product::Product(int id, const std::string &name, double price, int quantity)
    : id(id), name(name), price(price), quantity(quantity) {}

int Product::getId() const
{
    return id;
}

std::string Product::getName() const
{
    return name;
}

double Product::getPrice() const
{
    return price;
}

double Product::getQuantity() const
{
    return quantity;
}

bool Product::operator==(const Product &other) const
{
    return id == other.id && name == other.name && price == other.price && quantity == other.quantity;
}