#pragma once

#include <string>

enum class Language
{
    RUSSIAN = 1,
    ENGLISH = 2
};

std::string toString(Language lang)
{
    switch (lang)
    {
    case Language::RUSSIAN:
        return "RUSSIAN";
    case Language::ENGLISH:
        return "ENGLISH";
    default:
        return "UNKNOWN";
    }
}