#include "create_milk_use_case_impl.h"
#include "milk.h"

CreateMilkUseCase::CreateMilkUseCase(std::shared_ptr<IProductRepository> repo, std::shared_ptr<IIdGenerator> gen) : repository(repo), idGenerator(gen) {}

int CreateMilkUseCase::execute(const CreateMilkDTO &dto)
{
    auto milk = std::make_unique<Milk>(idGenerator->getNext(), dto.name, dto.price, dto.quantity, dto.expirationDate);
    int milkId = milk->getId();
    repository->save(std::move(milk));
    return milkId;
}