#include "toy.h"

Toy::Toy(int id, const std::string &name, double price, int quantity, int ageLimit)
    : Product(id, name, price, quantity), ageLimit(ageLimit) {}

int Toy::getAgeLimit() const
{
    return ageLimit;
}

std::string Toy::toString()
{
    return "Toy: ID=" + std::to_string(id) + ", Name=" + name + ", Price=" + std::to_string(price) +
           ", Quantity=" + std::to_string(quantity) + ", Age Limit=" + std::to_string(ageLimit) + "+";
}

std::unique_ptr<Product> Toy::copy() const
{
    return std::make_unique<Toy>(*this);
}

bool Toy::operator==(const Toy &other) const
{
    return Product::operator==(other) && ageLimit == other.ageLimit;
}