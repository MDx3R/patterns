#pragma once
#include "strategy.h"

class Calendar
{
private:
    std::string name;
    std::string address;
    std::vector<Event *> events;
    std::unique_ptr<OutputStrategy> strategy;

public:
    Calendar() : name(""), address("") {}
    Calendar(const std::string &n, const std::string &addr) : name(n), address(addr) {}
    Calendar(const Calendar &other) : name(other.name), address(other.address)
    {
        for (const auto &e : other.events)
        {
            events.push_back(e->clone());
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

    std::string getName() const { return name; }
    std::string getAddress() const { return address; }
    std::vector<Event *> &getEvents() { return events; }
    const std::vector<Event *> &getEvents() const { return events; }
};

void TextOutput::print(const Calendar &calendar) const
{
    std::cout << "Calendar Name: " << calendar.getName() << ", Address: " << calendar.getAddress() << "\n";
    for (const auto &e : calendar.getEvents())
    {
        std::cout << e->print() << "\n";
    }
    std::cout << "\n";
}

void HtmlOutput::print(const Calendar &calendar) const
{
    std::cout << "<h1>" << calendar.getName() << "</h1>\n<p>Address: " << calendar.getAddress() << "</p>\n";
    for (const auto &e : calendar.getEvents())
    {
        std::cout << "<p>" << e->print() << "</p>\n";
    }
    std::cout << "\n";
}