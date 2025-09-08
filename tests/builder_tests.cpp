#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <functional>

#include "article.h"
#include "builder.h"
#include "director.h"

// Test fixture for article-related tests
class ArticleFunctionalTest : public ::testing::Test
{
protected:
    std::string tempFilePath;

    void SetUp() override
    {
        tempFilePath = "test_article.txt";
    }

    void TearDown() override
    {
        if (std::filesystem::exists(tempFilePath))
        {
            std::filesystem::remove(tempFilePath);
        }
    }

    void createTestFile(const std::vector<std::string> &lines)
    {
        std::ofstream file(tempFilePath);
        ASSERT_TRUE(file.is_open()) << "Failed to create test file";
        for (const auto &line : lines)
        {
            file << line << "\n";
        }
        file.close();
    }

    std::string computeHash(const std::string &body)
    {
        std::hash<std::string> hasher;
        return std::to_string(hasher(body));
    }
};

// Test for XmlArticle adding and retrieving content
TEST_F(ArticleFunctionalTest, XmlArticle_AddAndGetContent_WorksCorrectly)
{
    // Arrange
    XmlArticle article;
    std::string content = "<title>Test Title</title>\n";

    // Act
    article.addContent(content);
    std::string result = article.getContent();

    // Assert
    EXPECT_EQ(result, content);
}

// Test for SimpleXmlArticleBuilder constructing article parts
TEST_F(ArticleFunctionalTest, SimpleXmlArticleBuilder_BuildsCorrectXmlStructure)
{
    // Arrange
    SimpleXmlArticleBuilder builder;
    std::string title = "Test Title";
    std::string authors = "John Doe";
    std::string body = "This is the body\nof the article.";
    std::string hash = "1234567890";

    // Act
    builder.buildTitle(title);
    builder.buildAuthors(authors);
    builder.buildBody(body);
    builder.buildHash(hash);
    XmlArticle article = builder.getResult();

    // Assert
    std::string expectedContent =
        "<title>" + title + "</title>\n" +
        "<authors>" + authors + "</authors>\n" +
        "<body>" + body + "</body>\n" +
        "<hash>" + hash + "</hash>\n";
    EXPECT_EQ(article.getContent(), expectedContent);
}

// Test for XmlArticleDirector constructing article from valid file
TEST_F(ArticleFunctionalTest, XmlArticleDirector_ConstructFromValidFile_Succeeds)
{
    // Arrange
    std::string title = "Test Title";
    std::string authors = "John Doe";
    std::string body = "This is the body\nof the article.\n";
    std::string hash = computeHash(body);
    std::vector<std::string> lines = {title, authors, "This is the body", "of the article.", hash};
    createTestFile(lines);

    SimpleXmlArticleBuilder builder;
    XmlArticleDirector director(builder);

    // Act
    director.constructFromFile(tempFilePath);
    XmlArticle article = builder.getResult();

    // Assert
    std::string expectedContent =
        "<title>" + title + "</title>\n" +
        "<authors>" + authors + "</authors>\n" +
        "<body>" + body + "</body>\n" +
        "<hash>" + hash + "</hash>\n";
    EXPECT_EQ(article.getContent(), expectedContent);
}

// Test for XmlArticleDirector with insufficient lines in file
TEST_F(ArticleFunctionalTest, XmlArticleDirector_InsufficientLines_Throws)
{
    // Arrange
    std::vector<std::string> lines = {"Test Title", "John Doe"}; // Less than 4 lines
    createTestFile(lines);

    SimpleXmlArticleBuilder builder;
    XmlArticleDirector director(builder);

    // Act & Assert
    EXPECT_THROW(director.constructFromFile(tempFilePath), std::runtime_error);
}

// Test for XmlArticleDirector with invalid hash
TEST_F(ArticleFunctionalTest, XmlArticleDirector_InvalidHash_Throws)
{
    // Arrange
    std::string title = "Test Title";
    std::string authors = "John Doe";
    std::string body = "This is the body\nof the article.\n";
    std::string invalidHash = "9999999999"; // Incorrect hash
    std::vector<std::string> lines = {title, authors, "This is the body", "of the article.", invalidHash};
    createTestFile(lines);

    SimpleXmlArticleBuilder builder;
    XmlArticleDirector director(builder);

    // Act & Assert
    EXPECT_THROW(director.constructFromFile(tempFilePath), std::runtime_error);
}

// Test for XmlArticleDirector with non-existent file
TEST_F(ArticleFunctionalTest, XmlArticleDirector_NonExistentFile_Throws)
{
    // Arrange
    SimpleXmlArticleBuilder builder;
    XmlArticleDirector director(builder);
    std::string nonExistentFile = "non_existent.txt";

    // Act & Assert
    EXPECT_THROW(director.constructFromFile(nonExistentFile), std::runtime_error);
}

// Test for XmlArticleDirector direct construction
TEST_F(ArticleFunctionalTest, XmlArticleDirector_DirectConstruction_WorksCorrectly)
{
    // Arrange
    std::string title = "Direct Title";
    std::string authors = "Jane Doe";
    std::string body = "Direct body content\nwith multiple lines.\n";
    std::string hash = computeHash(body);

    SimpleXmlArticleBuilder builder;
    XmlArticleDirector director(builder);

    // Act
    director.construct(title, authors, body, hash);
    XmlArticle article = builder.getResult();

    // Assert
    std::string expectedContent =
        "<title>" + title + "</title>\n" +
        "<authors>" + authors + "</authors>\n" +
        "<body>" + body + "</body>\n" +
        "<hash>" + hash + "</hash>\n";
    EXPECT_EQ(article.getContent(), expectedContent);
}