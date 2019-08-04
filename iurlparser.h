#ifndef IURLPARSER_H
#define IURLPARSER_H

#include <qurl.h>

class IParserService
{
public:
    virtual ~IParserService();

#ifdef SINGLELINE_QUERY_PARAMETERS
    virtual QUrl parseUrl(const QString &arg1,
                          const QString &arg2,
                          const QString &arg3,
                          const QString &arg4)=0;
#endif
#ifdef MULTILINE_QUERY_PARAMETERS
    virtual QUrl parseUrl(const QString &arg1,
                          const QString &arg2,
                          const QStringList &arg3,
                          const QString &arg4)=0;
#endif

#ifdef SINGLELINE_TWO_PARAMETERS
    virtual QUrl parseUrl(const QString &arg1,
                          const QString &arg2,
                          const QString &arg3)=0;
#endif
#ifdef MULTILINE_TWO_PARAMETERS
    virtual QUrl parseUrl(const QString &arg1,
                          const QStringList &arg2,
                          const QString &arg3)=0;
#endif
};
template<typename T>
struct IUrlParser
{
    virtual ~IUrlParser()
    {
    }
    virtual void setParserService(T t)=0;
    virtual IParserService* parserService()=0;
};

#endif // IURLPARSER_H
