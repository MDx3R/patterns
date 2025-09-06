#include <gtest/gtest.h>
#include "domain/entities/product.h"
#include "domain/entities/milk.h"
#include "domain/entities/toy.h"
#include "domain/entities/tv.h"
#include "domain/services/id_generator.h"
#include "application/usecases/create_milk_use_case_impl.h"
#include "application/usecases/create_toy_use_case_impl.h"
#include "application/usecases/create_tv_use_case_impl.h"
#include "application/usecases/get_product_use_case_impl.h"
#include "infrastructure/repositories/inmemory_product_repository.h"
#include "presentation/controllers/query_controller.h"
#include "presentation/controllers/command_controller.h"
#include <ctime>

// Test fixture for functional tests
class FunctionalTest : public ::testing::Test
{
protected:
    std::shared_ptr<IdGenerator> idGenerator;
    std::shared_ptr<InMemoryProductRepository> productRepo;
    std::shared_ptr<CreateMilkUseCase> createMilkUseCase;
    std::shared_ptr<CreateToyUseCase> createToyUseCase;
    std::shared_ptr<CreateTVUseCase> createTVUseCase;
    std::shared_ptr<GetProductUseCase> getProductUseCase;
    std::shared_ptr<QueryController> queryController;
    std::shared_ptr<CommandController> commandController;

    void SetUp() override
    {
        idGenerator = std::make_shared<IdGenerator>();
        productRepo = std::make_shared<InMemoryProductRepository>();
        createMilkUseCase = std::make_shared<CreateMilkUseCase>(productRepo, idGenerator);
        createToyUseCase = std::make_shared<CreateToyUseCase>(productRepo, idGenerator);
        createTVUseCase = std::make_shared<CreateTVUseCase>(productRepo, idGenerator);
        getProductUseCase = std::make_shared<GetProductUseCase>(productRepo);
        queryController = std::make_shared<QueryController>(getProductUseCase);
        commandController = std::make_shared<CommandController>(createMilkUseCase, createToyUseCase, createTVUseCase);
    }

    CreateMilkDTO makeMilkDTO(const std::string &name, double price, int quantity, std::time_t expirationDate)
    {
        CreateMilkDTO dto;
        dto.name = name;
        dto.price = price;
        dto.quantity = quantity;
        dto.expirationDate = expirationDate;
        return dto;
    }

    CreateToyDTO makeToyDTO(const std::string &name, double price, int quantity, int ageLimit)
    {
        CreateToyDTO dto;
        dto.name = name;
        dto.price = price;
        dto.quantity = quantity;
        dto.ageLimit = ageLimit;
        return dto;
    }

    CreateTVDTO makeTVDTO(const std::string &name, double price, int quantity, int screenSize)
    {
        CreateTVDTO dto;
        dto.name = name;
        dto.price = price;
        dto.quantity = quantity;
        dto.screenSize = screenSize;
        return dto;
    }
};

// Test for CommandController creating a Milk product
TEST_F(FunctionalTest, CommandController_CreateMilk_CreatesAndSavesMilk)
{
    // Arrange
    std::time_t expirationDate = std::time(nullptr) + 86400; // Tomorrow
    CreateMilkDTO milkDTO = makeMilkDTO("Whole Milk", 2.99, 10, expirationDate);

    // Act
    int milkId = commandController->createMilk(milkDTO);

    // Assert
    auto retrievedProduct = queryController->getProduct(milkId);
    auto milk = dynamic_cast<Milk *>(retrievedProduct.get());
    ASSERT_NE(milk, nullptr);
    EXPECT_EQ(milk->getId(), milkId);
    EXPECT_EQ(milk->getName(), milkDTO.name);
    EXPECT_EQ(milk->getPrice(), milkDTO.price);
    EXPECT_EQ(milk->getQuantity(), milkDTO.quantity);
    EXPECT_EQ(milk->getExpirationDate(), milkDTO.expirationDate);
}

// Test for CommandController creating a Toy product
TEST_F(FunctionalTest, CommandController_CreateToy_CreatesAndSavesToy)
{
    // Arrange
    CreateToyDTO toyDTO = makeToyDTO("Action Figure", 15.99, 5, 6);

    // Act
    int toyId = commandController->createToy(toyDTO);

    // Assert
    auto retrievedProduct = queryController->getProduct(toyId);
    auto toy = dynamic_cast<Toy *>(retrievedProduct.get());
    ASSERT_NE(toy, nullptr);
    EXPECT_EQ(toy->getId(), toyId);
    EXPECT_EQ(toy->getName(), toyDTO.name);
    EXPECT_EQ(toy->getPrice(), toyDTO.price);
    EXPECT_EQ(toy->getQuantity(), toyDTO.quantity);
    EXPECT_EQ(toy->getAgeLimit(), toyDTO.ageLimit);
}

// Test for CommandController creating a TV product
TEST_F(FunctionalTest, CommandController_CreateTV_CreatesAndSavesTV)
{
    // Arrange
    CreateTVDTO tvDTO = makeTVDTO("Smart TV", 499.99, 3, 55);

    // Act
    int tvId = commandController->createTV(tvDTO);

    // Assert
    auto retrievedProduct = queryController->getProduct(tvId);
    auto tv = dynamic_cast<TV *>(retrievedProduct.get());
    ASSERT_NE(tv, nullptr);
    EXPECT_EQ(tv->getId(), tvId);
    EXPECT_EQ(tv->getName(), tvDTO.name);
    EXPECT_EQ(tv->getPrice(), tvDTO.price);
    EXPECT_EQ(tv->getQuantity(), tvDTO.quantity);
    EXPECT_EQ(tv->getScreenSize(), tvDTO.screenSize);
}

// Test for QueryController retrieving a non-existent product
TEST_F(FunctionalTest, QueryController_GetProduct_NonExistentProductThrows)
{
    // Arrange
    int nonExistentId = 999;

    // Act & Assert
    EXPECT_THROW(queryController->getProduct(nonExistentId), std::runtime_error);
}