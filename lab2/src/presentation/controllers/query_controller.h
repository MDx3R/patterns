#pragma once
#include <memory>
#include "domain/entities/product.h"
#include "application/usecases/get_product_use_case.h"

class QueryController
{
private:
    std::shared_ptr<IGetProductUseCase> getProductUseCase;

public:
    explicit QueryController(std::shared_ptr<IGetProductUseCase> useCase)
        : getProductUseCase(std::move(useCase)) {}

    std::unique_ptr<Product> getProduct(int id)
    {
        return getProductUseCase->execute(id);
    }
};
