#pragma once
#include <string>
#include "article.h"

class XmlArticleBuilder
{
public:
    virtual ~XmlArticleBuilder() = default;
    virtual void buildTitle(const std::string &title) = 0;
    virtual void buildAuthors(const std::string &authors) = 0;
    virtual void buildBody(const std::string &body) = 0;
    virtual void buildHash(const std::string &hash) = 0;
    virtual XmlArticle getResult() = 0;
};

#pragma once
#include "builder.h"
#include <sstream>

class SimpleXmlArticleBuilder : public XmlArticleBuilder
{
private:
    XmlArticle article;

public:
    void buildTitle(const std::string &title) override
    {
        article.addContent("<title>" + title + "</title>\n");
    }

    void buildAuthors(const std::string &authors) override
    {
        article.addContent("<authors>" + authors + "</authors>\n");
    }

    void buildBody(const std::string &body) override
    {
        article.addContent("<body>" + body + "</body>\n");
    }

    void buildHash(const std::string &hash) override
    {
        article.addContent("<hash>" + hash + "</hash>\n");
    }

    XmlArticle getResult() override
    {
        return article;
    }
};
