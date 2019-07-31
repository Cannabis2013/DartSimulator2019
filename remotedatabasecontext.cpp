#include "remotedatabasecontext.h"

RemoteDatabaseContext::RemoteDatabaseContext(const QString &serverHostUrl, const QString &code):
    _rootDomain(serverHostUrl),_userCode(code)
{
    _netMng = new QNetworkAccessManager();
    connect(_netMng,&QNetworkAccessManager::sslErrors,this,&RemoteDatabaseContext::handleSslErrors);

    qRegisterMetaType<HTTPReplyObject>("HTTPObject");
}

void RemoteDatabaseContext::sendGetRequest(const QString &method,
                                        const QString &urlParameter,
                                        void(RemoteDatabaseContext::* slot)())
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

void RemoteDatabaseContext::sendPostRequest(const QString &method,
                                         const QJsonObject &JSON, const QString &urlParameter,
                                         void(RemoteDatabaseContext::*slot)())
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
        processAndAssembleUrl(fullServerUrl,method);
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


void RemoteDatabaseContext::sendDeleteRequest(const QString &method,
                                           const QString &urlParameter,
                                           void(RemoteDatabaseContext::*slot)())
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

void RemoteDatabaseContext::handleSslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    Q_UNUSED(reply);
    Q_UNUSED(errors);

    // TODO: Handle Ssl errors when its time for that
}

void RemoteDatabaseContext::handleRedirection(const QUrl &url)
{
    Q_UNUSED(url);
    // TODO: Don't think this will be necessary, so I might delete this method until otherwise.
}


void RemoteDatabaseContext::processAndAssembleUrl(QString &hostUrl, QString method, QString urlParameter)
{
    /*
     * Template: {baseUrl}/{Method}/{urlParameter}?code={userCode}
     * Example: www.testapi.dk/api/DeleteTournament/ad4a22ee-4c5c-4911-a01f-d9578edb387c?code={{code}}
     */

    if(_rootDomain != QString())
        hostUrl = _rootDomain;
    else
        throw invalid_argument("Host url not valid or not set");

    if(hostUrl.at(hostUrl.length() - 1) != '/')
        hostUrl.append('/');

    if(urlParameter != QString())
    {
        if(method.at(method.length() - 1) != '/')
            method.append('/');

        hostUrl += method + urlParameter;
    }

    if(_userCode != QString())
        hostUrl += "?code=" + _userCode;
}

QStringList RemoteDatabaseContext::remoteMethods() const
{
    return _remoteMethods;
}

void RemoteDatabaseContext::requestTournaments()
{
    sendGetRequest("GetTournaments",QString(),&RemoteDatabaseContext::handleRequestetTournaments);
}

void RemoteDatabaseContext::requestTournament(const QUuid &id)
{
    const QString uuid = id.toString(QUuid::WithoutBraces);
    sendGetRequest("GetTournament",uuid,&RemoteDatabaseContext::handleRequestetTournament);
}

void RemoteDatabaseContext::requestRounds(const QUuid &tournament)
{
    // TODO: Endpoints for this call is not yet ready
}

void RemoteDatabaseContext::requestOrderedTable(const QUuid &tournament)
{
    // TODO: Endpoints for this call is not yet ready
}

void RemoteDatabaseContext::handleRequestetTournaments()
{
    const QByteArray data = tempReply->readAll();
    emit sendAllTournamentsData(data);
}

void RemoteDatabaseContext::handleRequestetTournament()
{
    const QByteArray data = tempReply->readAll();
    emit sendTournamentData(data);
}

bool RemoteDatabaseContext::isBusy() const
{
    return _isBusy;
}

QString RemoteDatabaseContext::getUserCode() const
{
    return _userCode;
}

void RemoteDatabaseContext::setUserCode(const QString &value)
{
    _userCode = value;
}

QString RemoteDatabaseContext::getRootDomain() const
{
    return _rootDomain;
}
