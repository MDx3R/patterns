#pragma once
#include <iostream>
#include <memory>
#include "tank.h"
#include "adapter.h"

class TankDispatcher
{
public:
    TankDispatcher() = default;

    void start()
    {
        std::cout << "=======================================\n";
        std::cout << "            Gas Tank Adapter\n";
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
                    handleCreateTank();
                    break;
                case 2:
                    handleCalculateDp();
                    break;
                case 3:
                    handleModifyMass();
                    break;
                case 4:
                    handleGetData();
                    break;
                case 5:
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
    std::shared_ptr<GasTank> currentTank; // No star pointers
    std::shared_ptr<GasTankAdapter> adapter;

    void showMainMenu()
    {
        std::cout << "\n1. Create Gas Tank\n";
        std::cout << "2. Calculate Delta Pressure\n";
        std::cout << "3. Modify Mass\n";
        std::cout << "4. Get Tank Data\n";
        std::cout << "5. Exit\n";
        std::cout << "Select an action: ";
    }

    void handleCreateTank()
    {
        double volume, mass, molar;
        std::cout << "Enter volume: ";
        std::cin >> volume;
        std::cout << "Enter mass: ";
        std::cin >> mass;
        std::cout << "Enter molar: ";
        std::cin >> molar;
        std::cin.ignore();

        currentTank = std::make_shared<GasTank>(volume, mass, molar);
        adapter = std::make_shared<GasTankAdapter>(*currentTank);
        std::cout << "Gas Tank created and adapted successfully.\n";
    }

    void handleCalculateDp()
    {
        if (!adapter)
        {
            std::cout << "No tank created yet.\n";
            return;
        }
        int t0, dT;
        std::cout << "Enter initial temperature (t0): ";
        std::cin >> t0;
        std::cout << "Enter temperature change (dT): ";
        std::cin >> dT;
        std::cin.ignore();

        double dp = adapter->calculateDp(t0, dT);
        std::cout << "Calculated Delta Pressure: " << dp << "\n";
    }

    void handleModifyMass()
    {
        if (!adapter)
        {
            std::cout << "No tank created yet.\n";
            return;
        }
        int dm;
        std::cout << "Enter mass change (dm): ";
        std::cin >> dm;
        std::cin.ignore();

        adapter->modifyMass(dm);
        std::cout << "Mass modified successfully.\n";
    }

    void handleGetData()
    {
        if (!adapter)
        {
            std::cout << "No tank created yet.\n";
            return;
        }
        std::string data = adapter->getData();
        std::cout << "Tank Data: " << data << "\n";
    }
};