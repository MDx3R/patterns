#pragma once
#include "event.h"
#include <vector>
#include <memory>

class Calendar;

class OutputStrategy
{
public:
    virtual ~OutputStrategy() = default;
    virtual void print(const Calendar &calendar) const = 0;
};

class TextOutput : public OutputStrategy
{
public:
    void print(const Calendar &calendar) const override;
};

class HtmlOutput : public OutputStrategy
{
public:
    void print(const Calendar &calendar) const override;
};