#pragma once

#include <memory>
#include "audio.h"
#include "subtitles.h"

class IMovieFactory
{
public:
    virtual ~IMovieFactory() = default;
    virtual std::unique_ptr<AudioTrack> createAudio() = 0;
    virtual std::unique_ptr<SubtitlesFile> createSubtitles() = 0;
};

class EnglishMovieFactory : public IMovieFactory
{
public:
    std::unique_ptr<AudioTrack> createAudio() override { return std::make_unique<EnglishAudio>(); };
    std::unique_ptr<SubtitlesFile> createSubtitles() override { return std::make_unique<EnglishSubtitles>(); };
};

class RussianMovieFactory : public IMovieFactory
{
public:
    std::unique_ptr<AudioTrack> createAudio() override { return std::make_unique<RussianAudio>(); };
    std::unique_ptr<SubtitlesFile> createSubtitles() override { return std::make_unique<RussianSubtitles>(); };
};