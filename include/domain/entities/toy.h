#pragma once
#include "product.h"

class Toy : public Product
{
protected:
    int ageLimit;

public:
    Toy(int id, const std::string &name, double price, int quantity, int ageLimit);

    int getAgeLimit() const;

    std::string toString() override;

    bool operator==(const Toy &other) const;
};