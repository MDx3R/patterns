#include <memory>
#include <iostream>
#include <ctime>

#include "movie_dispatcher.h"
#include "movie_service.h"
#include "movie_factory.h"

#include "shape_dispatcher.h"
#include "shape_factory.h"

#include "article_dispatcher.h"

#include <filesystem>

int main()
{
    std::srand(std::time(nullptr));

    std::cout << "Current path: " << std::filesystem::current_path() << "\n";

    bool running = true;
    while (running)
    {
        std::cout << "========================\n";
        std::cout << "  Choose Application\n";
        std::cout << "========================\n";
        std::cout << "1. Abstract Factory (Movies)\n";
        std::cout << "2. Factory Method (Tetris Shapes)\n";
        std::cout << "3. Builder (TXT to XML article)\n";
        std::cout << "4. Exit\n";
        std::cout << "Select: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice)
        {
        case 1:
        {
            auto englishFactory = std::make_shared<EnglishMovieFactory>();
            auto russianFactory = std::make_shared<RussianMovieFactory>();
            std::unordered_map<Language, std::shared_ptr<IMovieFactory>> mp = {{Language::ENGLISH, englishFactory},
                                                                               {Language::RUSSIAN, russianFactory}};
            auto movieService = std::make_shared<MovieService>(mp);
            MovieDispatcher movieDispatcher(movieService);
            movieDispatcher.start();
            break;
        }
        case 2:
        {
            auto ordinaryFactory = std::make_shared<TetrisShapeFactory>();
            auto superFactory = std::make_shared<SuperShapeFactory>();
            ShapeDispatcher shapeDispatcher(ordinaryFactory, superFactory);
            shapeDispatcher.start();
            break;
        }
        case 3:
            ArticleDispatcher articleDispatcher;
            articleDispatcher.start();
            break;
        case 4:
            running = false;
            break;
        default:
            std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}