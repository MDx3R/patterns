#pragma once
#include <string>
#include <ctime>

struct CreateMilkDTO
{
    std::string name;
    double price;
    int quantity;
    std::time_t expirationDate;
};

class ICreateMilkUseCase
{
public:
    virtual ~ICreateMilkUseCase() = default;
    virtual int execute(const CreateMilkDTO &dto) = 0;
};