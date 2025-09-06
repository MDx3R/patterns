#pragma once
#include <vector>
#include "product.h"

class IProductRepository
{
public:
    virtual ~IProductRepository() = default;

    virtual Product getById(int id) = 0;
    virtual std::vector<Product> all() = 0;
    virtual void save(const Product &product) = 0;
};