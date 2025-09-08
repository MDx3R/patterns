#pragma once

#include "language.h"

class AudioTrack
{
public:
    virtual ~AudioTrack() = default;
    virtual Language language() = 0;
};

class EnglishAudio : public AudioTrack
{
public:
    Language language() override { return Language::ENGLISH; };
};

class RussianAudio : public AudioTrack
{
public:
    Language language() override { return Language::RUSSIAN; };
};