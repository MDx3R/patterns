#pragma once

class IIdGenerator
{
public:
    virtual int getNext() = 0;
};

class IdGenerator : public IIdGenerator
{
private:
    int nextId = 1;

public:
    int getNext() override { return nextId++; }
};
