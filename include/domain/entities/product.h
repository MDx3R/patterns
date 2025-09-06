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
    virtual std::unique_ptr<Product> copy() const = 0;

    bool operator==(const Product &other) const;
};