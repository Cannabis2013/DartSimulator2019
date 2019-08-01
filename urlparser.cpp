#include "urlparser.h"

UrlParser::UrlParser()
{

}

QUrl UrlParser::parseUrl(const QString &baseUrl,
                        const QString &method,
                        const QString &urlParameter,
                        const QString &apiCode)
{
    /*
     * Template: {baseUrl}/{Method}/{urlParameter}?code={userCode}
     * Example: www.testapi.dk/api/DeleteTournament/ad4a22ee-4c5c-4911-a01f-d9578edb387c?code={{code}}
     */

    QString hostUrl = baseUrl;
    QString urlMethod = method;
    QString urlCode = apiCode;

    if(hostUrl.at(hostUrl.length() - 1) != '/')
        hostUrl.append('/');

    if(urlMethod.at(method.length() - 1) != '/')
        urlMethod.append('/');

    hostUrl += urlMethod;

    if(urlParameter != QString())
        hostUrl += urlParameter;

    if(urlCode != QString())
        hostUrl += "?code=" + urlCode;

    return QUrl(hostUrl);
}
