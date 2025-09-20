#pragma once

#include "language.h"

class AudioTrack
{
public:
    virtual ~AudioTrack() = default;
    virtual Language getLanguage() const = 0;
};

class EnglishAudio : public AudioTrack
{
public:
    Language getLanguage() const override { return Language::ENGLISH; };
};

class RussianAudio : public AudioTrack
{
public:
    Language getLanguage() const override { return Language::RUSSIAN; };
};