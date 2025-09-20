#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <unordered_set>
#include <cstdlib>

#include "shape.h"
#include "shape_factory.h"

// Test fixture for shape factory tests
class ShapeFactoryTest : public ::testing::Test
{
protected:
    TetrisShapeFactory tetrisFactory;
    SuperShapeFactory superFactory;

    void SetUp() override
    {
        // Seed random number generator for reproducible testing
        std::srand(42);
    }

    std::unordered_set<std::string> generateMultipleShapes(IShapeFactory &factory, int count)
    {
        std::unordered_set<std::string> uniqueShapes;
        for (int i = 0; i < count; ++i)
        {
            auto shape = factory.createRandomShape();
            uniqueShapes.insert(shape->getName());
        }
        return uniqueShapes;
    }
};

// Test that TetrisShapeFactory creates valid ordinary shapes
TEST_F(ShapeFactoryTest, TetrisShapeFactory_CreatesValidOrdinaryShapes)
{
    // Act
    auto shape = tetrisFactory.createRandomShape();

    // Assert
    std::string name = shape->getName();
    EXPECT_TRUE(name == "I" || name == "O" || name == "T");
}

// Test that SuperShapeFactory creates valid super shapes
TEST_F(ShapeFactoryTest, SuperShapeFactory_CreatesValidSuperShapes)
{
    // Act
    auto shape = superFactory.createRandomShape();

    // Assert
    std::string name = shape->getName();
    EXPECT_TRUE(name == "SuperLine" || name == "SuperSquare");
}

// Test that TetrisShapeFactory can generate all possible ordinary shapes
TEST_F(ShapeFactoryTest, TetrisShapeFactory_GeneratesAllOrdinaryShapes)
{
    // Act
    auto uniqueShapes = generateMultipleShapes(tetrisFactory, 100);

    // Assert
    EXPECT_EQ(uniqueShapes.size(), 3);
    EXPECT_TRUE(uniqueShapes.count("I") == 1);
    EXPECT_TRUE(uniqueShapes.count("O") == 1);
    EXPECT_TRUE(uniqueShapes.count("T") == 1);
}

// Test that SuperShapeFactory can generate all possible super shapes
TEST_F(ShapeFactoryTest, SuperShapeFactory_GeneratesAllSuperShapes)
{
    // Act
    auto uniqueShapes = generateMultipleShapes(superFactory, 100);

    // Assert
    EXPECT_EQ(uniqueShapes.size(), 2);
    EXPECT_TRUE(uniqueShapes.count("SuperLine") == 1);
    EXPECT_TRUE(uniqueShapes.count("SuperSquare") == 1);
}

// Test that IShape returns correct name
TEST_F(ShapeFactoryTest, IShape_ReturnsCorrectName)
{
    // Arrange
    IShape iShape;

    // Act
    std::string name = iShape.getName();

    // Assert
    EXPECT_EQ(name, "I");
}

// Test that OShape returns correct name
TEST_F(ShapeFactoryTest, OShape_ReturnsCorrectName)
{
    // Arrange
    OShape oShape;

    // Act
    std::string name = oShape.getName();

    // Assert
    EXPECT_EQ(name, "O");
}

// Test that TShape returns correct name
TEST_F(ShapeFactoryTest, TShape_ReturnsCorrectName)
{
    // Arrange
    TShape tShape;

    // Act
    std::string name = tShape.getName();

    // Assert
    EXPECT_EQ(name, "T");
}

// Test that SuperLine returns correct name
TEST_F(ShapeFactoryTest, SuperLine_ReturnsCorrectName)
{
    // Arrange
    SuperLine superLine;

    // Act
    std::string name = superLine.getName();

    // Assert
    EXPECT_EQ(name, "SuperLine");
}

// Test that SuperSquare returns correct name
TEST_F(ShapeFactoryTest, SuperSquare_ReturnsCorrectName)
{
    // Arrange
    SuperSquare superSquare;

    // Act
    std::string name = superSquare.getName();

    // Assert
    EXPECT_EQ(name, "SuperSquare");
}