#pragma once
#include "application/usecases/create_milk_use_case.h"
#include "application/repositories/product_repository.h"
#include "domain/services/id_generator.h"

class CreateMilkUseCase : public ICreateMilkUseCase
{
private:
    std::shared_ptr<IProductRepository> repository;
    std::shared_ptr<IIdGenerator> idGenerator;

public:
    explicit CreateMilkUseCase(std::shared_ptr<IProductRepository> repo, std::shared_ptr<IIdGenerator> gen);
    int execute(const CreateMilkDTO &dto) override;
};