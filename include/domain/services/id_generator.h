#pragma once
class IdGenerator
{
private:
    static inline int nextId = 1;

public:
    static int getNext() { return nextId++; }
};
