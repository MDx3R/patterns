#pragma once

#include <unordered_map>
#include "language.h"
#include "movie.h"
#include "movie_factory.h"

class IMovieService
{
public:
    virtual Movie create(Language language) = 0;
    virtual void changeLanguage(Language language, Movie &movie) = 0;
};

class MovieService : public IMovieService
{
private:
    std::unordered_map<Language, std::shared_ptr<IMovieFactory>> factories;

public:
    MovieService(std::unordered_map<Language, std::shared_ptr<IMovieFactory>> factories)
        : factories(std::move(factories)) {}

    Movie create(Language language) override
    {
        auto factory = chooseFactory(language);
        return Movie(factory->createAudio(), factory->createSubtitles());
    };
    void changeLanguage(Language language, Movie &movie) override
    {
        auto factory = chooseFactory(language);
        return movie.setAudioAndSubtitles(factory->createAudio(), factory->createSubtitles());
    };

private:
    std::shared_ptr<IMovieFactory> chooseFactory(Language language)
    {
        auto it = factories.find(language);
        if (it == factories.end())
            throw std::invalid_argument("Unsupported language");
        return it->second;
    }
};