#pragma once

#include <memory>
#include <stdexcept>
#include "audio.h"
#include "subtitles.h"

class Movie
{
private:
    std::unique_ptr<AudioTrack> audio;
    std::unique_ptr<SubtitlesFile> subs;

public:
    Movie(std::unique_ptr<AudioTrack> audio,
          std::unique_ptr<SubtitlesFile> subs)
    {
        if (audio->language() != subs->language())
        {
            throw std::invalid_argument("Language for audio and subtitles must match");
        }
    };
};