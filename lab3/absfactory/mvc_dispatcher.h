#pragma once
#include <iostream>
#include <memory>
#include <optional>
#include "movie_controller.h"
#include "movie_view.h"
#include "movie_service.h"

class MVCDispatcher
{
public:
    MVCDispatcher(std::shared_ptr<MovieService> movieService)
        : movieService(std::move(movieService)) {}

    void start()
    {
        std::cout << "=======================================\n";
        std::cout << "         MVC Movie Rental System\n";
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
                    handleChangeLanguageToRussian();
                    break;
                case 3:
                    handleChangeLanguageToEnglish();
                    break;
                case 4:
                    handleClearLanguage();
                    break;
                case 5:
                    handleViewMovie();
                    break;
                case 6:
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
    std::shared_ptr<Movie> currentMovie;
    std::shared_ptr<MovieController> controller;
    std::shared_ptr<MainMovieView> mainView;
    std::shared_ptr<SubMovieView> subView;

    void showMainMenu()
    {
        std::cout << "\n1. Create Movie\n";
        std::cout << "2. Change Language to Russian\n";
        std::cout << "3. Change Language to English\n";
        std::cout << "4. Clear Audio and Subtitles\n";
        std::cout << "5. View Movie Info\n";
        std::cout << "6. Exit\n";
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
        currentMovie = std::make_shared<Movie>(movieService->create(lang));
        controller = std::make_shared<MovieController>(currentMovie, movieService);
        mainView = std::make_shared<MainMovieView>(currentMovie);
        subView = std::make_shared<SubMovieView>(currentMovie);
        std::cout << "Movie created successfully.\n";
    }

    void handleChangeLanguageToRussian()
    {
        if (!controller)
        {
            std::cout << "No movie created yet.\n";
            return;
        }
        controller->changeLanguageToRussian();
        std::cout << "Movie language changed to Russian successfully.\n";
    }

    void handleChangeLanguageToEnglish()
    {
        if (!controller)
        {
            std::cout << "No movie created yet.\n";
            return;
        }
        controller->changeLanguageToEnglish();
        std::cout << "Movie language changed to English successfully.\n";
    }

    void handleClearLanguage()
    {
        if (!controller)
        {
            std::cout << "No movie created yet.\n";
            return;
        }
        controller->clearLanguage();
        std::cout << "Audio and subtitles cleared successfully.\n";
    }

    void handleViewMovie()
    {
        if (!mainView || !subView)
        {
            std::cout << "No movie created yet.\n";
            return;
        }
        mainView->print();
        subView->print();
    }
};