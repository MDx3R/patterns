#pragma once
#include <string>
#include <memory>
#include "pricable.h"

class Product
{
protected:
    int id;
    std::string name;
    double price;
    int quantity;

public:
    Product(int id, const std::string &name, double price, int quantity);
    virtual ~Product() = default;

    int getId() const;
    std::string getName() const;
    double getPrice() const;
    double getQuantity() const;

    virtual std::string toString() = 0;

    bool operator==(const Product &other) const
    {
        return id == other.id && name == other.name && price == other.price && quantity == other.quantity;
    };
};