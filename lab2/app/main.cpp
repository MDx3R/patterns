#include "domain/entities/product.h"
#include "domain/entities/milk.h"
#include "domain/entities/toy.h"
#include "domain/entities/tv.h"
#include "domain/services/id_generator.h"
#include "application/usecases/create_milk_use_case_impl.h"
#include "application/usecases/create_toy_use_case_impl.h"
#include "application/usecases/create_tv_use_case_impl.h"
#include "application/usecases/get_product_use_case_impl.h"
#include "infrastructure/repositories/inmemory_product_repository.h"
#include "presentation/controllers/query_controller.h"
#include "presentation/controllers/command_controller.h"
#include "infrastructure/dispatcher/dispatcher.h"

int main()
{
    auto idGenerator = std::make_shared<IdGenerator>();

    auto productRepo = std::make_shared<InMemoryProductRepository>();

    auto createMilkUseCase = std::make_shared<CreateMilkUseCase>(productRepo, idGenerator);
    auto createToyUseCase = std::make_shared<CreateToyUseCase>(productRepo, idGenerator);
    auto createTVUseCase = std::make_shared<CreateTVUseCase>(productRepo, idGenerator);
    auto getProductUseCase = std::make_shared<GetProductUseCase>(productRepo);

    auto queryController = std::make_shared<QueryController>(getProductUseCase);
    auto commandController = std::make_shared<CommandController>(createMilkUseCase, createToyUseCase, createTVUseCase);

    auto dispatcher = Dispatcher(commandController, queryController);

    dispatcher.start();

    return 0;
}