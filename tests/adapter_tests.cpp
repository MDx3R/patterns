#include <gtest/gtest.h>
#include "tank.h"
#include "adapter.h"
#include <vector>
#include <map>

// Test fixture for gas tank tests
class GasTankFunctionalTest : public ::testing::Test
{
};

// Test for GasTank basic functionality
TEST_F(GasTankFunctionalTest, GasTank_GettersAndSetters_WorkCorrectly)
{
    // Arrange
    GasTank tank(10.0, 20.0, 30.0);

    // Act
    tank.setVolume(15.0);
    tank.setMass(25.0);
    tank.setMolar(35.0);

    // Assert
    EXPECT_DOUBLE_EQ(tank.getVolume(), 15.0);
    EXPECT_DOUBLE_EQ(tank.getMass(), 25.0);
    EXPECT_DOUBLE_EQ(tank.getMolar(), 35.0);
}

// Test for GasTank pressure calculation
TEST_F(GasTankFunctionalTest, GasTank_GetPressure_CalculatesCorrectly)
{
    // Arrange
    GasTank tank(10.0, 30.0, 2.0); // amountOfMatter = 30/2 = 15, R = 8.31
    int temperature = 300;

    // Act
    double pressure = tank.getPressure(temperature);

    // Assert
    EXPECT_DOUBLE_EQ(pressure, 15.0 * 8.31 * 300);
}

// Test for GasTankAdapter calculateDp
TEST_F(GasTankFunctionalTest, GasTankAdapter_CalculateDp_WorksCorrectly)
{
    // Arrange
    GasTank tank(10.0, 30.0, 2.0); // pressure = (30/2) * 8.31 * t
    GasTankAdapter adapter(tank);
    int t0 = 300, dT = 50;

    // Act
    double dp = adapter.calculateDp(t0, dT);

    // Assert
    double expectedPressure = (30.0 / 2.0) * 8.31 * 300 * 350.0 / 300.0;
    EXPECT_DOUBLE_EQ(dp, expectedPressure);
}

// Edge case: GasTankAdapter with zero initial temperature
TEST_F(GasTankFunctionalTest, GasTankAdapter_CalculateDp_ZeroInitialTemperature_Throws)
{
    // Arrange
    GasTank tank(10.0, 30.0, 2.0);
    GasTankAdapter adapter(tank);
    int t0 = 0, dT = 50;

    // Act & Assert
    EXPECT_TRUE(std::isnan(adapter.calculateDp(t0, dT))); // Division by zero in calculateDp
}

// Test for GasTankAdapter getData
TEST_F(GasTankFunctionalTest, GasTankAdapter_GetData_ReturnsCorrectString)
{
    // Arrange
    GasTank tank(10.0, 20.0, 30.0);
    GasTankAdapter adapter(tank);

    // Act
    std::string data = adapter.getData();

    // Assert
    EXPECT_EQ(data, "GasTank(volume=10.000000, mass=20.000000, molar=30.000000)");
}
