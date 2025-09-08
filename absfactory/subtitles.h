#pragma once

#include "language.h"

class SubtitlesFile
{
public:
    virtual ~SubtitlesFile() = default;
    virtual Language getLanguage() const = 0;
};

class EnglishSubtitles : public SubtitlesFile
{
public:
    Language getLanguage() const override { return Language::ENGLISH; };
};

class RussianSubtitles : public SubtitlesFile
{
public:
    Language getLanguage() const override { return Language::RUSSIAN; };
};