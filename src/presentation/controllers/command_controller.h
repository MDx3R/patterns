#pragma once
#include <memory>
#include "application/usecases/create_milk_use_case.h"
#include "application/usecases/create_toy_use_case.h"
#include "application/usecases/create_tv_use_case.h"

class CommandController
{
private:
    std::shared_ptr<ICreateMilkUseCase> milkUseCase;
    std::shared_ptr<ICreateToyUseCase> toyUseCase;
    std::shared_ptr<ICreateTVUseCase> tvUseCase;

public:
    CommandController(std::shared_ptr<ICreateMilkUseCase> milk,
                      std::shared_ptr<ICreateToyUseCase> toy,
                      std::shared_ptr<ICreateTVUseCase> tv)
        : milkUseCase(std::move(milk)),
          toyUseCase(std::move(toy)),
          tvUseCase(std::move(tv)) {}

    int createMilk(const CreateMilkDTO &dto)
    {
        return milkUseCase->execute(dto);
    }

    int createToy(const CreateToyDTO &dto)
    {
        return toyUseCase->execute(dto);
    }

    int createTV(const CreateTVDTO &dto)
    {
        return tvUseCase->execute(dto);
    }
};
