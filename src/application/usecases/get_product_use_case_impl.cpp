#include "get_product_use_case_impl.h"

GetProductUseCase::GetProductUseCase(std::shared_ptr<IProductRepository> repo) : repository(repo) {}

std::unique_ptr<Product> GetProductUseCase::execute(int id)
{
    return repository->getById(id); // Ok, moving implicitly
}