#pragma once

#include "tank.h"

class ITarget
{
public:
    virtual ~ITarget() = default;

    virtual double calculateDp(int t0, int dT) = 0;
    virtual void modifyMass(int dm) = 0;
    virtual std::string getData() = 0;
};

class GasTankAdapter : public ITarget
{
private:
    GasTank tank;

public:
    GasTankAdapter() = default;
    GasTankAdapter(GasTank &tank) : tank(tank) {} // TODO: Параменры для конструктора

    double calculateDp(int t0, int dT) override { return tank.getPressure(t0) * (t0 + dT) / t0; }
    void modifyMass(int dm) override { tank.setMass(dm); }
    std::string getData() override { return tank.toString(); }
};