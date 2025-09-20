#pragma once
#include <vector>
#include <memory>
#include "domain/entities/product.h"

class IProductRepository
{
public:
    virtual ~IProductRepository() = default;

    virtual std::unique_ptr<Product> getById(int id) = 0;
    virtual std::vector<std::unique_ptr<Product>> all() = 0;
    virtual void save(const std::unique_ptr<Product> product) = 0;
};