#pragma once
#include "application/usecases/create_tv_use_case.h"
#include "application/repositories/product_repository.h"
#include "domain/services/id_generator.h"

class CreateTVUseCase : public ICreateTVUseCase
{
private:
    std::shared_ptr<IProductRepository> repository;
    std::shared_ptr<IIdGenerator> idGenerator;

public:
    explicit CreateTVUseCase(std::shared_ptr<IProductRepository> repo, std::shared_ptr<IIdGenerator> gen);
    int execute(const CreateTVDTO &dto) override;
};