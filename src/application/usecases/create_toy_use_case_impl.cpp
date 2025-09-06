#include "create_toy_use_case_impl.h"
#include "toy.h"

CreateToyUseCase::CreateToyUseCase(std::shared_ptr<IProductRepository> repo, std::shared_ptr<IIdGenerator> gen) : repository(repository), idGenerator(gen) {}

int CreateToyUseCase::execute(const CreateToyDTO &dto)
{
    auto toy = std::make_unique<Toy>(idGenerator->getNext(), dto.name, dto.price, dto.quantity, dto.ageLimit);
    repository->save(std::move(toy));
    return toy->getId();
}