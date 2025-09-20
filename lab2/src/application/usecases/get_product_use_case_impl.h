#pragma once
#include "application/usecases/get_product_use_case.h"
#include "application/repositories/product_repository.h"

class GetProductUseCase : public IGetProductUseCase
{
private:
    std::shared_ptr<IProductRepository> repository;

public:
    explicit GetProductUseCase(std::shared_ptr<IProductRepository> repo);
    std::unique_ptr<Product> execute(int id) override;
};