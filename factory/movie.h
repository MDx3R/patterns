#pragma once

#include <memory>
#include <stdexcept>
#include "audio.h"
#include "subtitles.h"

class Movie
{
private:
    std::unique_ptr<AudioTrack> audio;
    std::unique_ptr<SubtitlesFile> subtitles;

public:
    Movie(std::unique_ptr<AudioTrack> aud,
          std::unique_ptr<SubtitlesFile> subs) : audio{std::move(aud)}, subtitles{std::move(subs)}
    {
        validateAudioAndSubtitles();
    };

    void setAudioAndSubtitles(std::unique_ptr<AudioTrack> aud, std::unique_ptr<SubtitlesFile> subs)
    {
        this->audio = std::move(aud);
        this->subtitles = std::move(subs);
        validateAudioAndSubtitles();
    }

private:
    void validateAudioAndSubtitles()
    {
        if (audio->language() != subtitles->language())
        {
            throw std::invalid_argument("Language for audio and subtitles must match");
        }
    }
};