#include <memory>
#include "movie_dispatcher.h"
#include "movie_service.h"
#include "movie_factory.h"

int main()
{
    auto englishFactory = std::make_shared<EnglishMovieFactory>();
    auto russianFactory = std::make_shared<RussianMovieFactory>();

    std::unordered_map<Language, std::shared_ptr<IMovieFactory>> mp = {{Language::ENGLISH, englishFactory},
                                                                       {Language::RUSSIAN, russianFactory}};

    auto movieService = std::make_shared<MovieService>(mp);

    MovieDispatcher dispatcher(movieService);

    dispatcher.start();

    return 0;
}
