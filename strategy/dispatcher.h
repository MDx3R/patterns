#pragma once
#include <iostream>
#include <memory>
#include "calendar.h"

class CalendarDispatcher
{
public:
    CalendarDispatcher(std::shared_ptr<Calendar> cal) : calendar(std::move(cal)) {}

    void start()
    {
        std::cout << "=======================================\n";
        std::cout << "   Event Planning Calendar System\n";
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
                    handleCreateCalendar();
                    break;
                case 2:
                    handleAddOneTimeEvent();
                    break;
                case 3:
                    handleAddRecurringEvent();
                    break;
                case 4:
                    handleSetTextStrategy();
                    break;
                case 5:
                    handleSetHtmlStrategy();
                    break;
                case 6:
                    handleDisplay();
                    break;
                case 7:
                    std::cout << "Exiting...\n";
                    running = false;
                    break;
                default:
                    std::cout << "Invalid choice.\n";
                }
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: " << e.what() << "\n";
            }
        }
    }

private:
    std::shared_ptr<Calendar> calendar;

    void showMainMenu()
    {
        std::cout << "\n1. Create Calendar\n";
        std::cout << "2. Add OneTimeEvent\n";
        std::cout << "3. Add RecurringEvent\n";
        std::cout << "4. Set Text Strategy\n";
        std::cout << "5. Set HTML Strategy\n";
        std::cout << "6. Display Calendar\n";
        std::cout << "7. Exit\n";
        std::cout << "Select an action: ";
    }

    void handleCreateCalendar()
    {
        std::string room, addr;
        std::cout << "Enter room name: ";
        std::getline(std::cin, room);
        std::cout << "Enter address: ";
        std::getline(std::cin, addr);
        calendar = std::make_shared<Calendar>(room, addr);
        std::cout << "Calendar created.\n";
    }

    void handleAddOneTimeEvent()
    {
        if (!calendar)
        {
            std::cout << "No calendar created.\n";
            return;
        }
        std::string date, name, desc;
        std::cout << "Enter date: ";
        std::getline(std::cin, date);
        std::cout << "Enter name: ";
        std::getline(std::cin, name);
        std::cout << "Enter description: ";
        std::getline(std::cin, desc);
        calendar->addEvent(new OneTimeEvent(date, name, desc));
        std::cout << "OneTimeEvent added.\n";
    }

    void handleAddRecurringEvent()
    {
        if (!calendar)
        {
            std::cout << "No calendar created.\n";
            return;
        }
        std::string date, name, desc, freq;
        std::cout << "Enter date: ";
        std::getline(std::cin, date);
        std::cout << "Enter name: ";
        std::getline(std::cin, name);
        std::cout << "Enter description: ";
        std::getline(std::cin, desc);
        std::cout << "Enter frequency: ";
        std::getline(std::cin, freq);
        calendar->addEvent(new RecurringEvent(date, name, desc, freq));
        std::cout << "RecurringEvent added.\n";
    }

    void handleSetTextStrategy()
    {
        if (!calendar)
        {
            std::cout << "No calendar created.\n";
            return;
        }
        calendar->setStrategy(std::make_unique<TextOutput>());
        std::cout << "Text strategy set.\n";
    }

    void handleSetHtmlStrategy()
    {
        if (!calendar)
        {
            std::cout << "No calendar created.\n";
            return;
        }
        calendar->setStrategy(std::make_unique<HtmlOutput>());
        std::cout << "HTML strategy set.\n";
    }

    void handleDisplay()
    {
        if (!calendar)
        {
            std::cout << "No calendar created.\n";
            return;
        }
        calendar->display();
    }
};