#pragma once
#include <string>

class Shape
{
public:
    virtual ~Shape() = default;
    virtual std::string getName() const = 0;
};

// 4-cell shapes

class IShape : public Shape
{
public:
    std::string getName() const override { return "I"; }
};

class OShape : public Shape
{
public:
    std::string getName() const override { return "O"; }
};

class TShape : public Shape
{
public:
    std::string getName() const override { return "T"; }
};

// 6-cell shapes

class SuperLine : public Shape
{
public:
    std::string getName() const override { return "SuperLine"; }
};

class SuperSquare : public Shape
{
public:
    std::string getName() const override { return "SuperSquare"; }
};