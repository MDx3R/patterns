#pragma once

#include <ctime>

class IClock
{
public:
    virtual ~IClock() = default;
    virtual std::time_t now() const = 0;
};

class SystemClock : public IClock
{
public:
    std::time_t now() const override
    {
        return std::time(nullptr);
    }
};
