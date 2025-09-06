#pragma once
#include <string>
#include <memory>
#include "product.h"

class IGetProductUseCase
{
public:
    virtual ~IGetProductUseCase() = default;
    virtual std::unique_ptr<Product> execute(int id) = 0;
};