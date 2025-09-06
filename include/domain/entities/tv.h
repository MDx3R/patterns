#pragma once
#include "product.h"

class TV : public Product
{
private:
    int screenSize;

public:
    TV(int id, const std::string &name, double price, int quantity, int screenSize);

    int getScreenSize() const;

    std::string toString() override;
    std::unique_ptr<Product> copy() const override;
    std::shared_ptr<Product> copyShared() const override;

    bool operator==(const TV &other) const;
};