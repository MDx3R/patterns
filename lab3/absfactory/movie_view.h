#pragma once
#include "observer.h"
#include "movie.h"
#include <memory>
#include <iostream>

class MainMovieView : public Observer
{
private:
    std::shared_ptr<Movie> model;

public:
    MainMovieView(std::shared_ptr<Movie> model)
    {
        this->model = model;
        this->model->addObserver(std::make_shared<MainMovieView>(*this));
    }
    void update()
    {
        print();
    }
    void print()
    {
        std::cout << "Movie Main View" << '\n';
        std::cout << "Audio: " << toString(model->getAudioLanguage()) << '\n';
        std::cout << "Subtitles: " << toString(model->getSubtitlesLanguage()) << '\n';
    }
};

class SubMovieView : public Observer
{
private:
    std::shared_ptr<Movie> model;

    Language audioLanguage;
    Language subtitlesLanguage;

public:
    SubMovieView(std::shared_ptr<Movie> model)
    {
        this->model = model;
        init();
        this->model->addObserver(std::make_shared<SubMovieView>(*this));
    }
    void update()
    {
        print();
        init();
    }
    void print()
    {
        std::cout << "Movie updated" << '\n';
        std::cout << "From Audio: " << toString(audioLanguage) << " to " << toString(model->getAudioLanguage()) << '\n';
        std::cout << "Subtitles: " << toString(subtitlesLanguage) << " to " << toString(model->getSubtitlesLanguage()) << '\n';
    }
    void init()
    {
        audioLanguage = model->getAudioLanguage();
        subtitlesLanguage = model->getSubtitlesLanguage();
    }
};