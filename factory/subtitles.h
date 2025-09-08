#pragma once

#include "language.h"

class SubtitlesFile
{
public:
    virtual ~SubtitlesFile() = default;
    virtual Language language() = 0;
};

class EnglishSubtitles : public SubtitlesFile
{
public:
    Language language() override { return Language::ENGLISH; };
};

class RussianSubtitles : public SubtitlesFile
{
public:
    Language language() override { return Language::RUSSIAN; };
};