#include "create_tv_use_case_impl.h"
#include "tv.h"

CreateTVUseCase::CreateTVUseCase(std::shared_ptr<IProductRepository> repo, std::shared_ptr<IIdGenerator> gen) : repository(repo), idGenerator(gen) {}

int CreateTVUseCase::execute(const CreateTVDTO &dto)
{
    auto tv = std::make_unique<TV>(idGenerator->getNext(), dto.name, dto.price, dto.quantity, dto.screenSize);
    int tvId = tv->getId();
    repository->save(std::move(tv));
    return tvId;
}