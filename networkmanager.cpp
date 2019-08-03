#include "networkmanager.h"

NetworkManager::NetworkManager(const QString &serverHostUrl, const QString &code):
    _baseUrl(serverHostUrl),_userCode(code)
{
    _netMng = new QNetworkAccessManager();

    connect(_netMng,&QNetworkAccessManager::sslErrors,this,&NetworkManager::handleSslErrors);
    setParserService(new UrlParser());

}

void NetworkManager::sendGetRequest(const QString &method,
                                    const QString &urlParameter,
                                    QObject *reciever,
                                    const char *slot)
{
    QUrl fullServerUrl = parserService()->parseUrl(_baseUrl,method,urlParameter,_userCode);

    tempReply = _netMng->get(QNetworkRequest(fullServerUrl));

    _responseTimer.start();


    connect(tempReply,SIGNAL(finished()),reciever,slot);
    ReplyTimeout::setTimer(tempReply,
                           timeoutThreshold(),
                           this,
                           SLOT(handleServerTimeout()),
                           ReplyTimeout::Close);
}

void NetworkManager::sendPostRequest(const QString &method,
                                     const QByteArray &data,
                                     const QString &urlParameter,
                                     QObject* reciever,
                                     const char* slot)
{
    QUrl fullServerUrl = parserService()->parseUrl(_baseUrl,method,urlParameter,_userCode);

    QNetworkRequest req(fullServerUrl);

    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    tempReply = _netMng->post(req,data);


    _responseTimer.start();
    if(slot != nullptr)
        connect(tempReply,SIGNAL(finished()),reciever,slot);

    ReplyTimeout::setTimer(tempReply,
                           timeoutThreshold(),
                           this,
                           SLOT(handleServerTimeout()),
                           ReplyTimeout::Close);
}


void NetworkManager::sendDeleteRequest(const QString &method,
                                       const QString &urlParameter,
                                       QObject *reciever,
                                       const char* slot)
{
    QUrl fullServerUrl = parserService()->parseUrl(_baseUrl,method,urlParameter,_userCode);
    tempReply = static_cast<NetworkReply*>(_netMng->deleteResource(QNetworkRequest(fullServerUrl)));

    _responseTimer.start();

    if(slot != nullptr)
        connect(tempReply,SIGNAL(finished()),reciever,slot);

    connect(tempReply,&QNetworkReply::finished,tempReply,&QNetworkReply::deleteLater);


    ReplyTimeout::setTimer(tempReply,
                           timeoutThreshold(),
                           this,
                           SLOT(handleServerTimeout()),
                           ReplyTimeout::Close);
}

void NetworkManager::handleSslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    Q_UNUSED(reply);
    Q_UNUSED(errors);

    // TODO: Handle Ssl errors when its time for that
}

void NetworkManager::handleServerTimeout()
{
    emit sendErrorString("Server time out. Try again later.");
    tempReply->close();
}

void NetworkManager::setBaseUrl(const QString &baseUrl)
{
    _baseUrl = baseUrl;
}

int NetworkManager::timeElapsed()
{
    return _responseTimer.elapsed();
}

void NetworkManager::setUserCode(const QString &value)
{
    _userCode = value;
}

QString NetworkManager::baseUrl() const
{
    return _baseUrl;
}


void NetworkManager::setParserService(IParserService *t)
{
    _parserService = t;
}

IParserService *NetworkManager::parserService()
{
    return _parserService;
}

int NetworkManager::timeoutThreshold() const
{
    return _timeoutThreshold;
}

void NetworkManager::setTimeoutThreshold(int timeoutThreshold)
{
    _timeoutThreshold = timeoutThreshold;
}

NetworkReply::NetworkReply():
    QNetworkReply (nullptr)
{

}
