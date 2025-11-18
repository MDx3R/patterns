#pragma once
#include "strategy.h"

class Calendar
{
private:
    std::string roomName;
    std::string address;
    std::vector<Event *> events;
    std::unique_ptr<OutputStrategy> strategy;

public:
    Calendar() : roomName(""), address("") {}
    Calendar(const std::string &rn, const std::string &addr) : roomName(rn), address(addr) {}
    Calendar(const Calendar &other) : roomName(other.roomName), address(other.address)
    {
        for (const auto &e : other.events)
        {
            if (dynamic_cast<OneTimeEvent *>(e))
            {
                events.push_back(new OneTimeEvent(*static_cast<OneTimeEvent *>(e)));
            }
            else if (dynamic_cast<RecurringEvent *>(e))
            {
                events.push_back(new RecurringEvent(*static_cast<RecurringEvent *>(e)));
            }
            else
            {
                events.push_back(new Event(*e));
            }
        }
    }
    ~Calendar()
    {
        for (auto e : events)
            delete e;
    }

    void addEvent(Event *event) { events.push_back(event); }
    void setStrategy(std::unique_ptr<OutputStrategy> s) { strategy = std::move(s); }
    void display() const
    {
        if (strategy)
        {
            strategy->print(*this);
        }
        else
        {
            std::cout << "No strategy set.\n";
        }
    }

    std::string getRoomName() const { return roomName; }
    std::string getAddress() const { return address; }
    const std::vector<Event *> &getEvents() const { return events; }
};

void TextOutput::print(const Calendar &calendar) const
{
    std::cout << "Calendar Room: " << calendar.getRoomName() << ", Address: " << calendar.getAddress() << "\n";
    for (const auto &e : calendar.getEvents())
    {
        std::cout << *e << "\n";
    }
    std::cout << "\n";
}

void HtmlOutput::print(const Calendar &calendar) const
{
    std::cout << "<h1>" << calendar.getRoomName() << "</h1>\n<p>Address: " << calendar.getAddress() << "</p>\n";
    for (const auto &e : calendar.getEvents())
    {
        std::cout << "<p>" << *e << "</p>\n";
    }
    std::cout << "\n";
}