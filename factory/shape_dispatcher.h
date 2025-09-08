#pragma once
#include <iostream>
#include <memory>
#include "shape_factory.h"

class Dispatcher
{
public:
    Dispatcher(std::shared_ptr<IShapeFactory> ordinaryFactory,
               std::shared_ptr<IShapeFactory> superFactory)
        : ordinaryFactory(std::move(ordinaryFactory)),
          superFactory(std::move(superFactory)) {}

    void start()
    {
        std::cout << "=======================================\n";
        std::cout << "              Tetris Shapes\n";
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
                    handleGenerateOrdinary();
                    break;
                case 2:
                    handleGenerateSuper();
                    break;
                case 3:
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
    std::shared_ptr<IShapeFactory> ordinaryFactory;
    std::shared_ptr<IShapeFactory> superFactory;

    void showMainMenu()
    {
        std::cout << "\n1. Generate Ordinary Shape\n";
        std::cout << "2. Generate Super Shape\n";
        std::cout << "3. Exit\n";
        std::cout << "Select an action: ";
    }

    void handleGenerateOrdinary()
    {
        auto shape = ordinaryFactory->createRandomShape();
        std::cout << "Generated Ordinary Shape: " << shape->getName() << "\n";
    }

    void handleGenerateSuper()
    {
        auto shape = superFactory->createRandomShape();
        std::cout << "Generated Super Shape: " << shape->getName() << "\n";
    }
};
