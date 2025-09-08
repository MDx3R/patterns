#pragma once
#include <string>

class XmlArticle
{
private:
    std::string xmlContent;

public:
    void addContent(const std::string &xml) { xmlContent += xml; }
    std::string getContent() const { return xmlContent; }
};
