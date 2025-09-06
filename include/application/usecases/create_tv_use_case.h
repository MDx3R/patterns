#pragma once
#include <string>

struct CreateTVDTO
{
    std::string name;
    double price;
    int quantity;
    int screenSize;
};

class ICreateTVUseCase
{
public:
    virtual ~ICreateTVUseCase() = default;
    virtual int execute(const CreateTVDTO &dto) = 0;
};