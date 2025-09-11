#pragma once
#include <vector>
#include <memory>
#include "observer.h"

class Observable
{
protected:
    std::vector<std::shared_ptr<Observer>> observers;

public:
    void addObserver(std::shared_ptr<Observer> observer)
    {
        observers.push_back(observer);
    }
    void notifyUpdate()
    {
        for (auto obs : observers)
        {
            obs->update();
        }
    }
};