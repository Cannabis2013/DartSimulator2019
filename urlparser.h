#ifndef MYPARSER_H
#define MYPARSER_H

#define SINGLELINE_QUERY_PARAMETERS

#include <iurlparser.h>

class UrlParser : public IParserService
{
public:
    UrlParser();

    QUrl parseUrl(const QString &baseUrl, const QString &method, const QString &urlParameter, const QString &apiCode);
};

#endif // MYPARSER_H
