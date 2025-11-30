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
                    handleDecorateHighPriority();
                    break;
                case 5:
                    handleDecorateReminder();
                    break;
                case 6:
                    handleSetTextStrategy();
                    break;
                case 7:
                    handleSetHtmlStrategy();
                    break;
                case 8:
                    handleDisplay();
                    break;
                case 9:
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
    Event *lastAddedEvent = nullptr; // To decorate the last added event

    void showMainMenu()
    {
        std::cout << "\n1. Create Calendar\n";
        std::cout << "2. Add OneTimeEvent\n";
        std::cout << "3. Add RecurringEvent\n";
        std::cout << "4. Decorate High Priority (on last event)\n";
        std::cout << "5. Decorate Reminder (on last event)\n";
        std::cout << "6. Set Text Strategy\n";
        std::cout << "7. Set HTML Strategy\n";
        std::cout << "8. Display Calendar\n";
        std::cout << "9. Exit\n";
        std::cout << "Select an action: ";
    }

    void handleCreateCalendar()
    {
        std::string n, addr;
        std::cout << "Enter name: ";
        std::getline(std::cin, n);
        std::cout << "Enter address: ";
        std::getline(std::cin, addr);
        calendar = std::make_shared<Calendar>(n, addr);
        std::cout << "Calendar created.\n";
    }

    void handleAddOneTimeEvent()
    {
        if (!calendar)
        {
            std::cout << "No calendar created.\n";
            return;
        }
        std::string date, en, desc;
        std::cout << "Enter date: ";
        std::getline(std::cin, date);
        std::cout << "Enter name: ";
        std::getline(std::cin, en);
        std::cout << "Enter description: ";
        std::getline(std::cin, desc);
        lastAddedEvent = new OneTimeEvent(date, en, desc);
        calendar->addEvent(lastAddedEvent);
        std::cout << "OneTimeEvent added.\n";
    }

    void handleAddRecurringEvent()
    {
        if (!calendar)
        {
            std::cout << "No calendar created.\n";
            return;
        }
        std::string date, en, desc, freq;
        std::cout << "Enter date: ";
        std::getline(std::cin, date);
        std::cout << "Enter name: ";
        std::getline(std::cin, en);
        std::cout << "Enter description: ";
        std::getline(std::cin, desc);
        std::cout << "Enter frequency: ";
        std::getline(std::cin, freq);
        lastAddedEvent = new RecurringEvent(date, en, desc, freq);
        calendar->addEvent(lastAddedEvent);
        std::cout << "RecurringEvent added.\n";
    }

    void handleDecorateHighPriority()
    {
        if (!calendar || !lastAddedEvent)
        {
            std::cout << "No event to decorate.\n";
            return;
        }
        auto decorated = new HighPriorityDecorator(std::unique_ptr<Event>(lastAddedEvent->clone()));
        replaceLastEvent(decorated);
        lastAddedEvent = decorated;
        std::cout << "Event decorated with high priority.\n";
    }

    void handleDecorateReminder()
    {
        if (!calendar || !lastAddedEvent)
        {
            std::cout << "No event to decorate.\n";
            return;
        }
        std::string rt;
        std::cout << "Enter reminder time: ";
        std::getline(std::cin, rt);
        auto decorated = new ReminderDecorator(std::unique_ptr<Event>(lastAddedEvent->clone()), rt);
        replaceLastEvent(decorated);
        lastAddedEvent = decorated;
        std::cout << "Event decorated with reminder.\n";
    }

    void replaceLastEvent(Event *newEvent)
    {
        auto &events = calendar->getEvents();
        if (!events.empty())
        {
            delete events.back();
            events.back() = newEvent;
        }
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