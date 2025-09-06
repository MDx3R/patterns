#pragma once
#include "product.h"
#include <ctime>

class Milk : public Product
{
private:
    std::time_t expirationDate;

public:
    Milk(int id, const std::string &name, double price, int quantity, std::time_t expirationDate);

    std::time_t getExpirationDate() const;
    bool hasExpired(std::time_t now) const;

    bool operator==(const Milk &other) const
    {
        return Product::operator==(other) && expirationDate == other.expirationDate;
    }
};