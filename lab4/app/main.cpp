#include <memory>
#include <iostream>
#include <ctime>

#include "tank_dispatcher.h"
#include "insurance_dispatcher.h"

#include <filesystem>

int main()
{
    bool running = true;
    while (running)
    {
        std::cout << "========================\n";
        std::cout << "  Choose Application\n";
        std::cout << "========================\n";
        std::cout << "1. Adapter (Gas Tank)\n";
        std::cout << "2. Facade (Insurance)\n";
        std::cout << "3. Exit\n";
        std::cout << "Select: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice)
        {
        case 1:
        {
            TankDispatcher tankDispatcher;
            tankDispatcher.start();
            break;
        }
        case 2:
        {
            auto riskCalc = std::make_shared<subsystem::RiskCalculator>();
            auto tariffCalc = std::make_shared<subsystem::TariffCalculator>();
            auto premiumCalc = std::make_shared<subsystem::PremiumCalculator>();

            auto insuranceFacade = std::make_shared<InsuranceFacade>(*riskCalc, *tariffCalc, *premiumCalc);

            InsuranceDispatcher insuranceDispatcher(insuranceFacade);
            insuranceDispatcher.start();
            break;
        }
        case 3:
            running = false;
            break;
        default:
            std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}