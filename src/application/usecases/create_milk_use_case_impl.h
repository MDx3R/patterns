#pragma once
#include "create_milk_use_case.h"
#include "product_repository.h"
#include "id_generator.h"

class CreateMilkUseCase : public ICreateMilkUseCase
{
private:
    std::shared_ptr<IProductRepository> repository;
    std::shared_ptr<IIdGenerator> idGenerator;

public:
    explicit CreateMilkUseCase(std::shared_ptr<IProductRepository> repo, std::shared_ptr<IIdGenerator> gen);
    int execute(const CreateMilkDTO &dto) override;
};