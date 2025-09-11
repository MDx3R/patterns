#pragma once

#include <memory>
#include "movie.h"
#include "movie_view.h"
#include "movie_service.h"

class MovieController
{
private:
    std::shared_ptr<Movie> model;
    std::shared_ptr<MovieService> service;

public:
    MovieController(std::shared_ptr<Movie> model, std::shared_ptr<MovieService> service)
    {
        this->model = model;
        this->service = service;
    }

    void changeLanguageToRussian()
    {
        service->changeLanguage(Language::RUSSIAN, *model);
    }

    void changeLanguageToEnglish()
    {
        service->changeLanguage(Language::ENGLISH, *model);
    }

    void clearLanguage()
    {
        model->clearAudioAndSubtitles();
    }
};