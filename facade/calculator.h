#pragma once

#include "property.h"

namespace subsystem
{
    class RiskCalculator
    {
    public:
        double calculateRisk(Property &p)
        {
            double risk = 1.0;
            if (p.getYearBuilt() < 1980)
                risk += 0.2;
            risk += p.getWear() / 100.0;
            return risk;
        }
    };

    class TariffCalculator
    {
    public:
        double baseTariff(Property &p)
        {
            // OCP :(
            if (p.getType() == "Apartment")
                return 10.0;
            else if (p.getType() == "Townhouse")
                return 15.0;
            else if (p.getType() == "Cottage")
                return 20.0;
            else
                return 12.0;
        }
    };

    class PremiumCalculator
    {
    private:
        double residentFactor = 0.05;

    public:
        double calculatePremium(const Property &property, double baseTariff, double risk) const
        {
            double area = property.getArea();
            int residents = property.getResidents();
            return baseTariff * area * risk * (1.0 + residents * residentFactor);
        }
    };
}