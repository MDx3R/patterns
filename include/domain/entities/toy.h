#pragma once
#include "product.h"

class Toy : public Product
{
protected:
    int ageLimit;

public:
    Toy(int id, const std::string &name, double price, int quantity, int ageLimit);

    int getAgeLimit() const;

    bool operator==(const Toy &other) const
    {
        return Product::operator==(other) && ageLimit == other.ageLimit;
    }
};