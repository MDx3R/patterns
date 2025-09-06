#pragma once
#include <ctime>

class IPerishable
{
public:
    virtual ~IPerishable() = default;
    virtual std::time_t getExpirationDate() const = 0;
    virtual bool hasExpired(std::time_t) const = 0;
};