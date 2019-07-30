#include "localhttpclientapi.h"

LocalHTTPClientAPI::LocalHTTPClientAPI(const QString &serverHostUrl, const QString &code):
    _rootDomain(serverHostUrl),_userCode(code)
{
    _netMng = new QNetworkAccessManager();
    connect(_netMng,&QNetworkAccessManager::sslErrors,this,&LocalHTTPClientAPI::handleSslErrors);

    qRegisterMetaType<HTTPReplyObject>("HTTPObject");

}

void LocalHTTPClientAPI::sendGetRequest(const QString &method,
                                        const QString &urlParameter,
                                        void(LocalHTTPClientAPI::* slot)())
{
    if(!_isBusy)
        _isBusy = true;
    else
    {
        emit sendErrorString("Client is busy. Awaiting response from server.");
        throw overflow_error("Client is busy and awaiting response from an unresolved request");
    }

    QString fullServerUrl;

    try {
        processAndAssembleUrl(fullServerUrl,method,urlParameter);
    } catch (invalid_argument e) {
        return;
    }

    tempReply = _netMng->get(QNetworkRequest(QUrl(fullServerUrl)));

    _responseTimer.start();

    connect(tempReply,&QNetworkReply::finished,this,slot);
    connect(tempReply,&QNetworkReply::finished,tempReply,&QNetworkReply::deleteLater);
}

void LocalHTTPClientAPI::sendPostRequest(const QString &method,
                                         const QJsonObject &JSON,
                                         void(LocalHTTPClientAPI::*slot)())
{
    if(!_isBusy)
        _isBusy = true;
    else
    {
        emit sendErrorString("Client is busy. Awaiting response from server.");
        return;
    }

    QString fullServerUrl;
    try {
        assembleBasicUrl(fullServerUrl,method);
    } catch (invalid_argument e) {
        return;
    }

    QUrl serverUrl = QUrl(fullServerUrl);
    QNetworkRequest req(serverUrl);

    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    tempReply = _netMng->post(req,QJsonDocument(JSON).toJson());

    _responseTimer.start();

    connect(tempReply,&QNetworkReply::finished,this,slot);
    connect(tempReply,&QNetworkReply::finished,tempReply,&QNetworkReply::deleteLater);
}


void LocalHTTPClientAPI::sendDeleteRequest(const QString &method,
                                           const QString &urlParameter,
                                           void(LocalHTTPClientAPI::*slot)())
{
    if(!_isBusy)
        _isBusy = true;
    else
    {
        emit sendErrorString("Client is busy. Awaiting response from server.");
        return;
    }

    QString fullServerUrl;
    try {
        processAndAssembleUrl(fullServerUrl,method,urlParameter);
    } catch (invalid_argument e) {
        return;
    }


    tempReply = _netMng->deleteResource(QNetworkRequest(QUrl(fullServerUrl)));

    _responseTimer.start();

    connect(tempReply,&QNetworkReply::finished,this,slot);
    connect(tempReply,&QNetworkReply::finished,tempReply,&QNetworkReply::deleteLater);
}

void LocalHTTPClientAPI::handleSslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    Q_UNUSED(reply);
    Q_UNUSED(errors);

    // TODO: Handle Ssl errors when its time for that
}

void LocalHTTPClientAPI::handleRedirection(const QUrl &url)
{
    Q_UNUSED(url);
    // TODO: Don't think this will be necessary, so I might delete this method until otherwise.
}

void LocalHTTPClientAPI::assembleBasicUrl(QString &hostUrl, QString method)
{
    /*
     * Primarily used for post requests
     */
    if(_rootDomain != QString())
        hostUrl += _rootDomain;
    else
        throw invalid_argument("Host url not valid or not set");;

    if(hostUrl.at(hostUrl.length() - 1) != '/')
        hostUrl.append('/');

    hostUrl += method + "?code=" + _userCode;
}

void LocalHTTPClientAPI::processAndAssembleUrl(QString &hostUrl, QString methodName, QString urlParameter)
{
    if(_rootDomain != QString())
        hostUrl = _rootDomain;
    else
        throw invalid_argument("Host url not valid or not set");

    if(hostUrl.at(hostUrl.length() - 1) != '/')
        hostUrl.append('/');

    if(methodName.at(methodName.length() - 1) != '/')
        methodName.append('/');

    methodName += urlParameter;

    hostUrl += methodName;

    if(_userCode != QString())
        hostUrl += "?code=" + _userCode;
}

QStringList LocalHTTPClientAPI::remoteMethods() const
{
    return _remoteMethods;
}

void LocalHTTPClientAPI::requestTournaments()
{
    sendGetRequest("GetTournaments",QString(),&LocalHTTPClientAPI::handleRequestetTournaments);
}

void LocalHTTPClientAPI::requestTournament(const QUuid &id)
{
    const QString uuid = id.toString(QUuid::WithoutBraces);
    sendGetRequest("GetTournament",uuid,&LocalHTTPClientAPI::handleRequestetTournament);
}

void LocalHTTPClientAPI::handleRequestetTournaments()
{
    const QByteArray data = tempReply->readAll();
    emit sendAllTournamentsData(data);
}

void LocalHTTPClientAPI::handleRequestetTournament()
{
    const QByteArray data = tempReply->readAll();
    emit sendTournamentData(data);
}

bool LocalHTTPClientAPI::isBusy() const
{
    return _isBusy;
}

QString LocalHTTPClientAPI::getUserCode() const
{
    return _userCode;
}

void LocalHTTPClientAPI::setUserCode(const QString &value)
{
    _userCode = value;
}

QString LocalHTTPClientAPI::getRootDomain() const
{
    return _rootDomain;
}
