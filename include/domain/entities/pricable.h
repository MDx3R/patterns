#pragma once

class IPricable
{
public:
    virtual ~IPricable() = default;
    virtual double getPrice() const = 0;
    virtual void applyDiscount(double) = 0;
};
