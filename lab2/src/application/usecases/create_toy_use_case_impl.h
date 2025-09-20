#pragma once
#include "application/usecases/create_toy_use_case.h"
#include "application/repositories/product_repository.h"
#include "domain/services/id_generator.h"

class CreateToyUseCase : public ICreateToyUseCase
{
private:
    std::shared_ptr<IProductRepository> repository;
    std::shared_ptr<IIdGenerator> idGenerator;

public:
    explicit CreateToyUseCase(std::shared_ptr<IProductRepository> repo, std::shared_ptr<IIdGenerator> gen);
    int execute(const CreateToyDTO &dto) override;
};