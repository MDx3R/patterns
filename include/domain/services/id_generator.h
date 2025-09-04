#pragma once
struct IIdGenerator
{
    virtual int getNext() = 0;
};

class IdGenerator : public IIdGenerator
{
private:
    int nextId = 1;

public:
    int getNext() override { return nextId++; }
};
