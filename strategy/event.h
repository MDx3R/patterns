#pragma once
#include <string>
#include <iostream>

class Event
{
protected:
    std::string date;
    std::string name;
    std::string description;

public:
    Event() : date(""), name(""), description("") {}
    Event(const std::string &d, const std::string &n, const std::string &desc)
        : date(d), name(n), description(desc) {}
    Event(const Event &other) : date(other.date), name(other.name), description(other.description) {}
    virtual ~Event() = default;

    virtual void print(std::ostream &os) const
    {
        os << "Date: " << date << ", Name: " << name << ", Description: " << description;
    }

    friend std::ostream &operator<<(std::ostream &os, const Event &e)
    {
        e.print(os);
        return os;
    }
};

class OneTimeEvent : public Event
{
public:
    OneTimeEvent() = default;
    OneTimeEvent(const std::string &d, const std::string &n, const std::string &desc)
        : Event(d, n, desc) {}
    OneTimeEvent(const OneTimeEvent &other) : Event(other) {}

    void print(std::ostream &os) const override
    {
        os << "OneTimeEvent - ";
        Event::print(os);
    }
};

class RecurringEvent : public Event
{
private:
    std::string frequency;

public:
    RecurringEvent() : frequency("") {}
    RecurringEvent(const std::string &d, const std::string &n, const std::string &desc, const std::string &freq)
        : Event(d, n, desc), frequency(freq) {}
    RecurringEvent(const RecurringEvent &other) : Event(other), frequency(other.frequency) {}

    void print(std::ostream &os) const override
    {
        os << "RecurringEvent (Frequency: " << frequency << ") - ";
        Event::print(os);
    }
};