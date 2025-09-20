#pragma once
#include <iostream>
#include <memory>
#include <optional>

#include "movie_service.h"
#include "movie.h"

class MovieDispatcher
{
public:
    MovieDispatcher(std::shared_ptr<MovieService> movieService)
        : movieService(std::move(movieService)) {}

    void start()
    {
        std::cout << "=======================================\n";
        std::cout << "            Movie Rental System\n";
        std::cout << "=======================================\n";

        bool running = true;
        while (running)
        {
            showMainMenu();
            int choice;
            std::cin >> choice;
            std::cin.ignore();

            try
            {
                switch (choice)
                {
                case 1:
                    handleCreateMovie();
                    break;
                case 2:
                    handleChangeLanguage();
                    break;
                case 3:
                    handleViewMovie();
                    break;
                case 4:
                    std::cout << "Exiting...\n";
                    running = false;
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                }
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: " << e.what() << "\n";
            }
        }
    }

private:
    std::shared_ptr<MovieService> movieService;
    std::optional<Movie> currentMovie;

    void showMainMenu()
    {
        std::cout << "\n1. Create Movie\n";
        std::cout << "2. Change Movie Language\n";
        std::cout << "3. View Movie Info\n";
        std::cout << "4. Exit\n";
        std::cout << "Select an action: ";
    }

    Language askLanguage()
    {
        int langChoice;
        std::cout << "Select language:\n";
        std::cout << "1. Russian\n";
        std::cout << "2. English\n";
        std::cout << "Enter choice: ";
        std::cin >> langChoice;
        std::cin.ignore();

        switch (langChoice)
        {
        case 1:
            return Language::RUSSIAN;
        case 2:
            return Language::ENGLISH;
        default:
            throw std::invalid_argument("Invalid language selection");
        }
    }

    void handleCreateMovie()
    {
        auto lang = askLanguage();
        currentMovie = movieService->create(lang);
        std::cout << "Movie created successfully.\n";
    }

    void handleChangeLanguage()
    {
        if (!currentMovie)
        {
            std::cout << "No movie created yet.\n";
            return;
        }
        auto lang = askLanguage();
        movieService->changeLanguage(lang, *currentMovie);
        std::cout << "Movie language changed successfully.\n";
    }

    void handleViewMovie()
    {
        if (!currentMovie)
        {
            std::cout << "No movie created yet.\n";
            return;
        }
        std::cout << "Current movie:\n";
        std::cout << "Audio: " << (currentMovie->getAudioLanguage() == Language::ENGLISH ? "English" : "Russian") << "\n";
        std::cout << "Subtitles: " << (currentMovie->getSubtitlesLanguage() == Language::ENGLISH ? "English" : "Russian") << "\n";
    }
};
