#pragma once

#include <memory>
#include <vector>
#include <cstdlib>
#include "shape.h"

class IShapeFactory
{
public:
    virtual ~IShapeFactory() = default;
    virtual std::shared_ptr<Shape> createRandomShape() = 0;
};

class TetrisShapeFactory : public IShapeFactory
{
private:
    std::vector<std::shared_ptr<Shape>> shapes{
        std::make_shared<IShape>(),
        std::make_shared<OShape>(),
        std::make_shared<TShape>()};

public:
    std::shared_ptr<Shape> createRandomShape() override
    {
        int r = std::rand() % shapes.size();
        return shapes[r];
    }
};

class SuperShapeFactory : public IShapeFactory
{
private:
    std::vector<std::shared_ptr<Shape>> shapes{
        std::make_shared<SuperLine>(),
        std::make_shared<SuperSquare>()};

public:
    std::shared_ptr<Shape> createRandomShape() override
    {
        int r = std::rand() % shapes.size();
        return shapes[r];
    }
};
