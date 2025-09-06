#pragma once
#include "product.h"

class TV : public Product
{
private:
    int screenSize;

public:
    TV(int id, const std::string &name, double price, int quantity, int screenSize);

    int getScreenSize() const;

    bool operator==(const TV &other) const
    {
        return Product::operator==(other) && screenSize == other.screenSize;
    }
};