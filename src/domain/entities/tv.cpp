#include "tv.h"

TV::TV(int id, const std::string &name, double price, int quantity, int screenSize)
    : Product(id, name, price, quantity), screenSize(screenSize) {}

int TV::getScreenSize() const
{
    return screenSize;
}

std::string TV::toString()
{
    return "TV: ID=" + std::to_string(id) + ", Name=" + name + ", Price=" + std::to_string(price) +
           ", Quantity=" + std::to_string(quantity) + ", Screen Size=" + std::to_string(screenSize) + " inches";
}

std::unique_ptr<Product> TV::copy() const
{
    return std::make_unique<TV>(*this);
}

bool TV::operator==(const TV &other) const
{
    return Product::operator==(other) && screenSize == other.screenSize;
}