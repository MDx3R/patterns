#pragma once

#include <map>
#include <vector>
#include "calculator.h"

// NOTE: Имеет смысл определить интерфейс фасада отдельно
// с целью повышения устойчивости клиентского кода
class InsuranceFacade
{
private:
    subsystem::RiskCalculator &riskCalc;
    subsystem::TariffCalculator &tariffCalc;
    subsystem::PremiumCalculator &premiumCalc;

public:
    double calculatePremium(Property property)
    {
        double base = tariffCalc.baseTariff(property);
        double risk = riskCalc.calculateRisk(property);
        return premiumCalc.calculatePremium(property, base, risk);
    }

    double getRiskFactor(Property property)
    {
        return riskCalc.calculateRisk(property);
    }

    double getBaseTariff(Property property)
    {
        return tariffCalc.baseTariff(property);
    }

    std::map<int, double> simulateScenarios(Property property, const std::vector<int> &years)
    {
        std::map<int, double> result;
        double base = tariffCalc.baseTariff(property);
        double risk = riskCalc.calculateRisk(property);
        double premium = premiumCalc.calculatePremium(property, base, risk);

        for (int y : years)
        {
            result[y] = premium * y;
        }
        return result;
    }

    bool isInsurable(Property property)
    {
        return property.getWear() < 80.0;
    }
};