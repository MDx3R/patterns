#include "domain/entities/milk.h"

Milk::Milk(int id, const std::string &name, double price, int quantity, std::time_t expirationDate)
    : Product(id, name, price, quantity), expirationDate(expirationDate) {}

std::time_t Milk::getExpirationDate() const
{
    return expirationDate;
}

bool Milk::hasExpired(std::time_t now) const
{
    return expirationDate < now;
}

std::string Milk::toString()
{
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", std::localtime(&expirationDate));

    return "Milk: ID=" + std::to_string(id) + ", Name=" + name + ", Price=" + std::to_string(price) +
           ", Quantity=" + std::to_string(quantity) + ", Expiration Date=" + buffer;
}

std::unique_ptr<Product> Milk::copy() const
{
    return std::make_unique<Milk>(*this);
}

std::shared_ptr<Product> Milk::copyShared() const
{
    return std::make_shared<Milk>(*this);
}

bool Milk::operator==(const Milk &other) const
{
    return Product::operator==(other) && expirationDate == other.expirationDate;
}