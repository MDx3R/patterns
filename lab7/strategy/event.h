#pragma once
#include <string>
#include <memory>

class Event
{
protected:
    std::string date;
    std::string eventName;
    std::string description;

public:
    Event() : date(""), eventName(""), description("") {}
    Event(const std::string &d, const std::string &en, const std::string &desc)
        : date(d), eventName(en), description(desc) {}
    Event(const Event &other) : date(other.date), eventName(other.eventName), description(other.description) {}
    virtual ~Event() = default;

    virtual std::string print() const
    {
        return "Date: " + date + ", Name: " + eventName + ", Description: " + description;
    }

    virtual Event *clone() const = 0;
};

class OneTimeEvent : public Event
{
public:
    OneTimeEvent() = default;
    OneTimeEvent(const std::string &d, const std::string &en, const std::string &desc)
        : Event(d, en, desc) {}
    OneTimeEvent(const OneTimeEvent &other) : Event(other) {}

    std::string print() const override
    {
        return "OneTimeEvent - " + Event::print();
    }

    Event *clone() const override
    {
        return new OneTimeEvent(*this);
    }
};

class RecurringEvent : public Event
{
private:
    std::string frequency;

public:
    RecurringEvent() : frequency("") {}
    RecurringEvent(const std::string &d, const std::string &en, const std::string &desc, const std::string &freq)
        : Event(d, en, desc), frequency(freq) {}
    RecurringEvent(const RecurringEvent &other) : Event(other), frequency(other.frequency) {}

    std::string print() const override
    {
        return "RecurringEvent (Frequency: " + frequency + ") - " + Event::print();
    }

    Event *clone() const override
    {
        return new RecurringEvent(*this);
    }
};

class EventDecorator : public Event
{
protected:
    std::unique_ptr<Event> component;

public:
    EventDecorator(std::unique_ptr<Event> event) : component(std::move(event)) {}
    virtual ~EventDecorator() = default;

    Event *clone() const override = 0;
};

class HighPriorityDecorator : public EventDecorator
{
public:
    HighPriorityDecorator(std::unique_ptr<Event> event) : EventDecorator(std::move(event)) {}

    std::string print() const override
    {
        return "HIGH PRIORITY: " + component->print();
    }

    Event *clone() const override
    {
        return new HighPriorityDecorator(std::unique_ptr<Event>(component->clone()));
    }
};

class ReminderDecorator : public EventDecorator
{
private:
    std::string reminderTime;

public:
    ReminderDecorator(std::unique_ptr<Event> event, const std::string &rt)
        : EventDecorator(std::move(event)), reminderTime(rt) {}

    std::string print() const override
    {
        return component->print() + " (Reminder at " + reminderTime + ")";
    }

    Event *clone() const override
    {
        return new ReminderDecorator(std::unique_ptr<Event>(component->clone()), reminderTime);
    }
};