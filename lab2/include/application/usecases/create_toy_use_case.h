#pragma once
#include <string>

struct CreateToyDTO
{
    std::string name;
    double price;
    int quantity;
    int ageLimit;
};

class ICreateToyUseCase
{
public:
    virtual ~ICreateToyUseCase() = default;
    virtual int execute(const CreateToyDTO &dto) = 0;
};