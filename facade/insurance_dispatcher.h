#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "facade.h"
#include "property.h"
#include "calculator.h"

class InsuranceDispatcher
{
public:
    InsuranceDispatcher(std::shared_ptr<InsuranceFacade> facade)
        : facade(std::move(facade)) {}

    void start()
    {
        std::cout << "=======================================\n";
        std::cout << "         Property Insurance Facade\n";
        std::cout << "=======================================\n";

        bool running = true;
        while (running)
        {
            showMainMenu();
            int choice;
            std::cin >> choice;
            std::cin.ignore();

            try
            {
                switch (choice)
                {
                case 1:
                    handleCreateProperty();
                    break;
                case 2:
                    handleCalculatePremium();
                    break;
                case 3:
                    handleGetRiskFactor();
                    break;
                case 4:
                    handleGetBaseTariff();
                    break;
                case 5:
                    handleSimulateScenarios();
                    break;
                case 6:
                    handleIsInsurable();
                    break;
                case 7:
                    std::cout << "Exiting...\n";
                    running = false;
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                }
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: " << e.what() << "\n";
            }
        }
    }

private:
    std::shared_ptr<InsuranceFacade> facade;
    std::shared_ptr<Property> currentProperty;

    void showMainMenu()
    {
        std::cout << "\n1. Create Property\n";
        std::cout << "2. Calculate Premium\n";
        std::cout << "3. Get Risk Factor\n";
        std::cout << "4. Get Base Tariff\n";
        std::cout << "5. Simulate Scenarios\n";
        std::cout << "6. Check if Insurable\n";
        std::cout << "7. Exit\n";
        std::cout << "Select an action: ";
    }

    void handleCreateProperty()
    {
        int type;
        std::cout << "Select property type:\n";
        std::cout << "1. Apartment\n";
        std::cout << "2. Townhouse\n";
        std::cout << "3. Cottage\n";
        std::cout << "Enter choice: ";
        std::cin >> type;
        std::cin.ignore();

        double area, wear;
        int yearBuilt, residents;
        std::cout << "Enter area: ";
        std::cin >> area;
        std::cout << "Enter year built: ";
        std::cin >> yearBuilt;
        std::cout << "Enter number of residents: ";
        std::cin >> residents;
        std::cout << "Enter wear (%): ";
        std::cin >> wear;
        std::cin.ignore();

        switch (type)
        {
        case 1:
            currentProperty = std::make_shared<subsystem::Apartment>(area, yearBuilt, residents, wear);
            break;
        case 2:
        {
            int numFloors;
            std::cout << "Enter number of floors: ";
            std::cin >> numFloors;
            std::cin.ignore();
            currentProperty = std::make_shared<subsystem::Townhouse>(area, yearBuilt, residents, wear, numFloors);
            break;
        }
        case 3:
        {
            bool hasGarden;
            std::cout << "Has garden? (1 for yes, 0 for no): ";
            std::cin >> hasGarden;
            std::cin.ignore();
            currentProperty = std::make_shared<subsystem::Cottage>(area, yearBuilt, residents, wear, hasGarden);
            break;
        }
        default:
            std::cout << "Invalid property type.\n";
            return;
        }
        std::cout << "Property created successfully.\n";
    }

    void handleCalculatePremium()
    {
        if (!currentProperty)
        {
            std::cout << "No property created yet.\n";
            return;
        }
        double premium = facade->calculatePremium(*currentProperty);
        std::cout << "Calculated Premium: " << premium << "\n";
    }

    void handleGetRiskFactor()
    {
        if (!currentProperty)
        {
            std::cout << "No property created yet.\n";
            return;
        }
        double risk = facade->getRiskFactor(*currentProperty);
        std::cout << "Risk Factor: " << risk << "\n";
    }

    void handleGetBaseTariff()
    {
        if (!currentProperty)
        {
            std::cout << "No property created yet.\n";
            return;
        }
        double tariff = facade->getBaseTariff(*currentProperty);
        std::cout << "Base Tariff: " << tariff << "\n";
    }

    void handleSimulateScenarios()
    {
        if (!currentProperty)
        {
            std::cout << "No property created yet.\n";
            return;
        }
        int numYears;
        std::cout << "Enter number of years to simulate: ";
        std::cin >> numYears;
        std::cin.ignore();

        std::vector<int> years;
        for (int i = 1; i <= numYears; ++i)
        {
            years.push_back(i);
        }

        auto scenarios = facade->simulateScenarios(*currentProperty, years);
        std::cout << "Simulation Results:\n";
        for (const auto &pair : scenarios)
        {
            std::cout << "Year " << pair.first << ": " << pair.second << "\n";
        }
    }

    void handleIsInsurable()
    {
        if (!currentProperty)
        {
            std::cout << "No property created yet.\n";
            return;
        }
        bool insurable = facade->isInsurable(*currentProperty);
        std::cout << "Is Insurable: " << (insurable ? "Yes" : "No") << "\n";
    }
};