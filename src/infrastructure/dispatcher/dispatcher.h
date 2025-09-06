#pragma once
#include <iostream>
#include <memory>
#include <string>

#include "presentation/controllers/command_controller.h"
#include "presentation/controllers/query_controller.h"

class ProductDispatcher
{
public:
    ProductDispatcher(std::shared_ptr<CommandController> cmdCtrl,
                      std::shared_ptr<QueryController> qryCtrl)
        : commandController(std::move(cmdCtrl)),
          queryController(std::move(qryCtrl))
    {
    }

    void start()
    {
        std::cout << "=======================================\n";
        std::cout << "          Product Management\n";
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
                    handleCreateMilk();
                    break;
                case 2:
                    handleCreateToy();
                    break;
                case 3:
                    handleCreateTV();
                    break;
                case 4:
                    handleGetProduct();
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
    std::shared_ptr<CommandController> commandController;
    std::shared_ptr<QueryController> queryController;

    void showMainMenu()
    {
        std::cout << "\n1. Create Milk\n";
        std::cout << "2. Create Toy\n";
        std::cout << "3. Create TV\n";
        std::cout << "4. View Product\n";
        std::cout << "5. Exit\n";
        std::cout << "Select an action: ";
    }

    void handleCreateMilk()
    {
        CreateMilkDTO dto;
        std::cout << "Enter name: ";
        std::getline(std::cin, dto.name);
        std::cout << "Enter price: ";
        std::cin >> dto.price;
        std::cout << "Enter quantity: ";
        std::cin >> dto.quantity;
        std::cin.ignore();
        std::cout << "Enter expiration date (timestamp): ";
        std::cin >> dto.expirationDate;
        std::cin.ignore();

        int id = commandController->createMilk(dto);
        std::cout << "Milk created with ID = " << id << "\n";
    }

    void handleCreateToy()
    {
        CreateToyDTO dto;
        std::cout << "Enter name: ";
        std::getline(std::cin, dto.name);
        std::cout << "Enter price: ";
        std::cin >> dto.price;
        std::cout << "Enter quantity: ";
        std::cin >> dto.quantity;
        std::cout << "Enter age limit: ";
        std::cin >> dto.ageLimit;
        std::cin.ignore();

        int id = commandController->createToy(dto);
        std::cout << "Toy created with ID = " << id << "\n";
    }

    void handleCreateTV()
    {
        CreateTVDTO dto;
        std::cout << "Enter name: ";
        std::getline(std::cin, dto.name);
        std::cout << "Enter price: ";
        std::cin >> dto.price;
        std::cout << "Enter quantity: ";
        std::cin >> dto.quantity;
        std::cout << "Enter screen size: ";
        std::cin >> dto.screenSize;
        std::cin.ignore();

        int id = commandController->createTV(dto);
        std::cout << "TV created with ID = " << id << "\n";
    }

    void handleGetProduct()
    {
        int id;
        std::cout << "Enter product ID to view: ";
        std::cin >> id;
        std::cin.ignore();

        auto product = queryController->getProduct(id);
        if (product)
        {
            std::cout << "Product details:\n"
                      << product->toString() << "\n";
        }
        else
        {
            std::cout << "Product not found.\n";
        }
    }
};
