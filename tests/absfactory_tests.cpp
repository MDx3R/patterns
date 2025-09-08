#include <gtest/gtest.h>
#include <memory>
#include <unordered_map>

#include "movie.h"
#include "movie_service.h"
#include "movie_factory.h"
#include "audio.h"
#include "subtitles.h"
#include "language.h"

// Test fixture for functional tests
class MovieFunctionalTest : public ::testing::Test
{
protected:
    std::shared_ptr<IMovieService> movieService;
    std::unordered_map<Language, std::shared_ptr<IMovieFactory>> factories;

    void SetUp() override
    {
        factories[Language::ENGLISH] = std::make_shared<EnglishMovieFactory>();
        factories[Language::RUSSIAN] = std::make_shared<RussianMovieFactory>();
        movieService = std::make_shared<MovieService>(factories);
    }
};

// Test for Movie creation with matching audio and subtitles languages
TEST_F(MovieFunctionalTest, Movie_CreateWithMatchingLanguages_Succeeds)
{
    // Arrange
    auto audio = std::make_unique<EnglishAudio>();
    auto subtitles = std::make_unique<EnglishSubtitles>();

    // Act
    Movie movie(std::move(audio), std::move(subtitles));

    // Assert
    EXPECT_EQ(movie.getAudioLanguage(), Language::ENGLISH);
    EXPECT_EQ(movie.getSubtitlesLanguage(), Language::ENGLISH);
}

// Test for Movie creation with mismatched audio and subtitles languages
TEST_F(MovieFunctionalTest, Movie_CreateWithMismatchedLanguages_Throws)
{
    // Arrange
    auto audio = std::make_unique<EnglishAudio>();
    auto subtitles = std::make_unique<RussianSubtitles>();

    // Act & Assert
    EXPECT_THROW(Movie(std::move(audio), std::move(subtitles)), std::invalid_argument);
}

// Test for MovieService creating a movie with English language
TEST_F(MovieFunctionalTest, MovieService_CreateEnglishMovie_CreatesCorrectly)
{
    // Act
    Movie movie = movieService->create(Language::ENGLISH);

    // Assert
    EXPECT_EQ(movie.getAudioLanguage(), Language::ENGLISH);
    EXPECT_EQ(movie.getSubtitlesLanguage(), Language::ENGLISH);
}

// Test for MovieService creating a movie with Russian language
TEST_F(MovieFunctionalTest, MovieService_CreateRussianMovie_CreatesCorrectly)
{
    // Act
    Movie movie = movieService->create(Language::RUSSIAN);

    // Assert
    EXPECT_EQ(movie.getAudioLanguage(), Language::RUSSIAN);
    EXPECT_EQ(movie.getSubtitlesLanguage(), Language::RUSSIAN);
}

// Test for MovieService creating a movie with unsupported language
TEST_F(MovieFunctionalTest, MovieService_CreateWithUnsupportedLanguage_Throws)
{
    // Arrange
    std::unordered_map<Language, std::shared_ptr<IMovieFactory>> emptyFactories;
    auto serviceWithNoFactories = std::make_shared<MovieService>(emptyFactories);

    // Act & Assert
    EXPECT_THROW(serviceWithNoFactories->create(Language::ENGLISH), std::invalid_argument);
}

// Test for MovieService changing movie language to Russian
TEST_F(MovieFunctionalTest, MovieService_ChangeLanguageToRussian_ChangesCorrectly)
{
    // Arrange
    Movie movie = movieService->create(Language::ENGLISH);

    // Act
    movieService->changeLanguage(Language::RUSSIAN, movie);

    // Assert
    EXPECT_EQ(movie.getAudioLanguage(), Language::RUSSIAN);
    EXPECT_EQ(movie.getSubtitlesLanguage(), Language::RUSSIAN);
}

// Test for MovieService changing movie language to unsupported language
TEST_F(MovieFunctionalTest, MovieService_ChangeToUnsupportedLanguage_Throws)
{
    // Arrange
    Movie movie = movieService->create(Language::ENGLISH);
    std::unordered_map<Language, std::shared_ptr<IMovieFactory>> emptyFactories;
    auto serviceWithNoFactories = std::make_shared<MovieService>(emptyFactories);

    // Act & Assert
    EXPECT_THROW(serviceWithNoFactories->changeLanguage(Language::RUSSIAN, movie), std::invalid_argument);
}

// Test for EnglishMovieFactory creating audio and subtitles
TEST_F(MovieFunctionalTest, EnglishMovieFactory_CreatesEnglishAudioAndSubtitles)
{
    // Arrange
    EnglishMovieFactory factory;

    // Act
    auto audio = factory.createAudio();
    auto subtitles = factory.createSubtitles();

    // Assert
    EXPECT_EQ(audio->getLanguage(), Language::ENGLISH);
    EXPECT_EQ(subtitles->getLanguage(), Language::ENGLISH);
}

// Test for RussianMovieFactory creating audio and subtitles
TEST_F(MovieFunctionalTest, RussianMovieFactory_CreatesRussianAudioAndSubtitles)
{
    // Arrange
    RussianMovieFactory factory;

    // Act
    auto audio = factory.createAudio();
    auto subtitles = factory.createSubtitles();

    // Assert
    EXPECT_EQ(audio->getLanguage(), Language::RUSSIAN);
    EXPECT_EQ(subtitles->getLanguage(), Language::RUSSIAN);
}