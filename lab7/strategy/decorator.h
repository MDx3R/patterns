#pragma once
#include "event.h"

class EventDecorator : public Event
{
protected:
    Event *component;

public:
    EventDecorator(Event *c) : component(c) {}
    ~EventDecorator() { delete component; }

    std::string print() const override
    {
        if (component)
            return component->print();
        return "";
    }
};

class PriorityDecorator : public EventDecorator
{
private:
    std::string priority;

public:
    PriorityDecorator(Event *c, const std::string &p) : EventDecorator(c), priority(p) {}

    std::string print() const override
    {
        return EventDecorator::print() + ", Priority: " + priority;
    }
};

class LocationDecorator : public EventDecorator
{
private:
    std::string location;

public:
    LocationDecorator(Event *c, const std::string &loc) : EventDecorator(c), location(loc) {}

    std::string print() const override
    {
        return EventDecorator::print() + ", Location: " + location;
    }
};