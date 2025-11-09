#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include "atm.h"

class ATMDispatcher
{
public:
    ATMDispatcher(std::shared_ptr<ATM> atm) : atm(std::move(atm)) {}

    void start()
    {
        std::cout << "=======================================\n";
        std::cout << "               ATM System\n";
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
                    handleEnterPIN();
                    break;
                case 2:
                    handleWithdraw();
                    break;
                case 3:
                    handleFinish();
                    break;
                case 4:
                    handleLoadMoney();
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
    std::shared_ptr<ATM> atm;

    void showMainMenu()
    {
        std::cout << "\n1. Enter PIN\n";
        std::cout << "2. Withdraw Amount\n";
        std::cout << "3. Finish Session\n";
        std::cout << "4. Load Money\n";
        std::cout << "5. Exit\n";
        std::cout << "Select an action: ";
    }

    void handleEnterPIN()
    {
        int pin;
        std::cout << "Enter PIN: ";
        std::cin >> pin;
        std::cin.ignore();
        atm->enterPIN(pin);
    }

    void handleWithdraw()
    {
        double amount;
        std::cout << "Enter amount to withdraw: ";
        std::cin >> amount;
        std::cin.ignore();
        atm->withdraw(amount);
    }

    void handleFinish()
    {
        atm->finish();
    }

    void handleLoadMoney()
    {
        double amount;
        std::cout << "Enter amount to load: ";
        std::cin >> amount;
        std::cin.ignore();
        atm->loadMoney(amount);
    }
};