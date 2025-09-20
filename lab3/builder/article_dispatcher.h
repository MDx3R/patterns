#pragma once
#include <iostream>
#include <memory>
#include <string>
#include "builder.h"
#include "director.h"
#include "builder.h"

class ArticleDispatcher
{
public:
    ArticleDispatcher() = default;

    void start()
    {
        std::cout << "=======================================\n";
        std::cout << "           TXT -> XML Converter\n";
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
                    handleConvertArticle();
                    break;
                case 2:
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
    void showMainMenu()
    {
        std::cout << "\n1. Convert TXT Article to XML\n";
        std::cout << "2. Exit\n";
        std::cout << "Select an action: ";
    }

    void handleConvertArticle()
    {
        std::string path;
        std::cout << "Enter path to TXT file: ";
        std::getline(std::cin, path);

        SimpleXmlArticleBuilder builder;
        XmlArticleDirector director(builder);

        director.constructFromFile(path);

        XmlArticle article = builder.getResult();
        std::cout << "Converted XML Article:\n";
        std::cout << article.getContent() << "\n";
    }
};
