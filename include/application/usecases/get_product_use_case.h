#pragma once
#include <string>
#include "product.h"

class IGetProductUseCase
{
public:
    virtual ~IGetProductUseCase() = default;
    virtual Product execute(int id) = 0;
};