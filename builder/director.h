#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <format>
#include "builder.h"

class XmlArticleDirector
{
private:
    XmlArticleBuilder &builder;
    int MIN_LINES_IN_FILE = 4;
    int TITLE_AT = 0;
    int AUTHORS_AT = 1;
    int BODY_STARTS_AT = 2;

public:
    explicit XmlArticleDirector(XmlArticleBuilder &b) : builder(b) {}

    void constructFromFile(const std::string &filename)
    {
        auto lines = readFileLines(filename);
        validateFileContent(lines);

        const std::string &title = lines[TITLE_AT];
        const std::string &authors = lines[AUTHORS_AT];
        const std::string &hash = lines.back();
        std::string body = extractBody(lines);

        verifyHash(body, hash);

        construct(title, authors, body, hash);
    }

    void construct(const std::string &title, const std::string &authors, const std::string &body, const std::string &hash)
    {
        builder.buildTitle(title);
        builder.buildAuthors(authors);
        builder.buildBody(body);
        builder.buildHash(hash);
    }

private:
    std::vector<std::string> readFileLines(const std::string &filename) const
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            throw std::runtime_error("Cannot open file: " + filename);
        }
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line))
        {
            lines.push_back(line);
        }
        return lines;
    }

    void validateFileContent(const std::vector<std::string> &lines) const
    {
        if (lines.size() < MIN_LINES_IN_FILE)
        {
            throw std::runtime_error("Article file format error: not enough lines");
        }
    }

    std::string extractBody(const std::vector<std::string> &lines) const
    {
        std::stringstream bodySS;
        for (size_t i = BODY_STARTS_AT; i < lines.size() - 1; ++i) // -1 for hash
        {
            bodySS << lines[i] << '\n';
        }
        return bodySS.str();
    }

    void verifyHash(const std::string &body, const std::string &hashStr) const
    {
        std::hash<std::string> hasher;
        size_t computedHash = hasher(body);
        size_t fileHash = std::stoull(hashStr);
        if (computedHash != fileHash)
        {
            throw std::runtime_error(std::format("{}: {} vs {}", "Hash mismatch", computedHash, fileHash));
        }
        return; // TODO
    }
};
