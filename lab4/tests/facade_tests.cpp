#include <gtest/gtest.h>
#include "property.h"
#include "facade.h"
#include "calculator.h"
#include <vector>
#include <map>

// Test fixture for insurance tests
class InsuranceFunctionalTest : public ::testing::Test
{
protected:
    subsystem::RiskCalculator riskCalc;
    subsystem::TariffCalculator tariffCalc;
    subsystem::PremiumCalculator premiumCalc;
    std::shared_ptr<InsuranceFacade> facade;

    void SetUp() override
    {
        facade = std::make_shared<InsuranceFacade>(riskCalc, tariffCalc, premiumCalc);
    }
};

// Test for Apartment property type
TEST_F(InsuranceFunctionalTest, Apartment_GetType_ReturnsCorrectType)
{
    // Arrange
    subsystem::Apartment apartment(100.0, 2000, 2, 10.0);

    // Act
    std::string type = apartment.getType();

    // Assert
    EXPECT_EQ(type, "Apartment");
}

// Test for Townhouse property type and numFloors
TEST_F(InsuranceFunctionalTest, Townhouse_GetTypeAndNumFloors_ReturnsCorrectValues)
{
    // Arrange
    subsystem::Townhouse townhouse(150.0, 1995, 4, 20.0, 2);

    // Act
    std::string type = townhouse.getType();
    int numFloors = townhouse.getNumFloors();

    // Assert
    EXPECT_EQ(type, "Townhouse");
    EXPECT_EQ(numFloors, 2);
}

// Test for Cottage property type and hasGarden
TEST_F(InsuranceFunctionalTest, Cottage_GetTypeAndHasGarden_ReturnsCorrectValues)
{
    // Arrange
    subsystem::Cottage cottage(200.0, 2010, 3, 15.0, true);

    // Act
    std::string type = cottage.getType();
    bool hasGarden = cottage.getHasGarden();

    // Assert
    EXPECT_EQ(type, "Cottage");
    EXPECT_TRUE(hasGarden);
}

// Test for RiskCalculator with old property
TEST_F(InsuranceFunctionalTest, RiskCalculator_OldProperty_IncreasesRisk)
{
    // Arrange
    subsystem::Apartment apartment(100.0, 1970, 2, 50.0);

    // Act
    double risk = riskCalc.calculateRisk(apartment);

    // Assert
    EXPECT_DOUBLE_EQ(risk, 1.0 + 0.2 + 50.0 / 100.0); // Base + old property + wear
}

// Test for RiskCalculator with new property
TEST_F(InsuranceFunctionalTest, RiskCalculator_NewProperty_CalculatesCorrectly)
{
    // Arrange
    subsystem::Apartment apartment(100.0, 2000, 2, 10.0);

    // Act
    double risk = riskCalc.calculateRisk(apartment);

    // Assert
    EXPECT_DOUBLE_EQ(risk, 1.0 + 10.0 / 100.0); // Base + wear
}

// Test for TariffCalculator with different property types
TEST_F(InsuranceFunctionalTest, TariffCalculator_ReturnsCorrectTariffForPropertyTypes)
{
    // Arrange
    subsystem::Apartment apartment(100.0, 2000, 2, 10.0);
    subsystem::Townhouse townhouse(150.0, 1995, 4, 20.0, 2);
    subsystem::Cottage cottage(200.0, 2010, 3, 15.0, true);

    // Act
    double apartmentTariff = tariffCalc.baseTariff(apartment);
    double townhouseTariff = tariffCalc.baseTariff(townhouse);
    double cottageTariff = tariffCalc.baseTariff(cottage);

    // Assert
    EXPECT_DOUBLE_EQ(apartmentTariff, 10.0);
    EXPECT_DOUBLE_EQ(townhouseTariff, 15.0);
    EXPECT_DOUBLE_EQ(cottageTariff, 20.0);
}

// Test for PremiumCalculator
TEST_F(InsuranceFunctionalTest, PremiumCalculator_CalculatesCorrectPremium)
{
    // Arrange
    subsystem::Apartment apartment(100.0, 2000, 2, 10.0);
    double baseTariff = 10.0;
    double risk = 1.1; // Base + 10% wear

    // Act
    double premium = premiumCalc.calculatePremium(apartment, baseTariff, risk);

    // Assert
    double expected = 10.0 * 100.0 * 1.1 * (1.0 + 2 * 0.05);
    EXPECT_DOUBLE_EQ(premium, expected);
}

// Test for InsuranceFacade calculatePremium
TEST_F(InsuranceFunctionalTest, InsuranceFacade_CalculatePremium_WorksCorrectly)
{
    // Arrange
    subsystem::Apartment apartment(100.0, 2000, 2, 10.0);

    // Act
    double premium = facade->calculatePremium(apartment);

    // Assert
    double risk = 1.0 + 10.0 / 100.0;
    double baseTariff = 10.0;
    double expected = baseTariff * 100.0 * risk * (1.0 + 2 * 0.05);
    EXPECT_DOUBLE_EQ(premium, expected);
}

// Edge case: InsuranceFacade with maximum wear
TEST_F(InsuranceFunctionalTest, InsuranceFacade_MaximumWear_AffectsPremium)
{
    // Arrange
    subsystem::Apartment apartment(100.0, 2000, 2, 79.9); // Just below insurable limit

    // Act
    double premium = facade->calculatePremium(apartment);

    // Assert
    double risk = 1.0 + 79.9 / 100.0;
    double baseTariff = 10.0;
    double expected = baseTariff * 100.0 * risk * (1.0 + 2 * 0.05);
    EXPECT_DOUBLE_EQ(premium, expected);
}

// Test for InsuranceFacade isInsurable
TEST_F(InsuranceFunctionalTest, InsuranceFacade_IsInsurable_ReturnsCorrectly)
{
    // Arrange
    subsystem::Apartment insurable(100.0, 2000, 2, 79.9);
    subsystem::Apartment notInsurable(100.0, 2000, 2, 80.0);

    // Act
    bool isInsurableResult = facade->isInsurable(insurable);
    bool isNotInsurableResult = facade->isInsurable(notInsurable);

    // Assert
    EXPECT_TRUE(isInsurableResult);
    EXPECT_FALSE(isNotInsurableResult);
}

// Test for InsuranceFacade simulateScenarios
TEST_F(InsuranceFunctionalTest, InsuranceFacade_SimulateScenarios_WorksCorrectly)
{
    // Arrange
    subsystem::Apartment apartment(100.0, 2000, 2, 10.0);
    std::vector<int> years = {1, 2, 3};

    // Act
    auto scenarios = facade->simulateScenarios(apartment, years);

    // Assert
    double risk = 1.0 + 10.0 / 100.0;
    double baseTariff = 10.0;
    double premium = baseTariff * 100.0 * risk * (1.0 + 2 * 0.05);
    EXPECT_DOUBLE_EQ(scenarios[1], premium * 1);
    EXPECT_DOUBLE_EQ(scenarios[2], premium * 2);
    EXPECT_DOUBLE_EQ(scenarios[3], premium * 3);
}

// Edge case: InsuranceFacade with empty years vector
TEST_F(InsuranceFunctionalTest, InsuranceFacade_SimulateScenarios_EmptyYears)
{
    // Arrange
    subsystem::Apartment apartment(100.0, 2000, 2, 10.0);
    std::vector<int> years;

    // Act
    auto scenarios = facade->simulateScenarios(apartment, years);

    // Assert
    EXPECT_TRUE(scenarios.empty());
}