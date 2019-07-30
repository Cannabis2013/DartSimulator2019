#ifndef HTTPINTERFACE_H
#define HTTPINTERFACE_H

#include <qnetworkaccessmanager.h>
#include <qnetworkrequest.h>
#include <QNetworkReply>
#include <qnetworkconfiguration.h>
#include <qlist.h>
#include <qtimer.h>
#include <QTime>
#include <iostream>
#include <quuid.h>

using namespace std;

#include <exception>

#include "httpreplyobject.h"
#include "myobject.h"

class LocalHTTPClientAPI : public MyObject
{
    Q_OBJECT
public:
    LocalHTTPClientAPI(const QString &serverHostUrl, const QString &code = QString());

    QString getRootDomain() const;

    QString getUserCode() const;
    void setUserCode(const QString &value);

    bool isBusy() const;

    QStringList remoteMethods() const;

    void requestTournaments();
    void requestTournament(const QUuid &id);

signals:
    void sendAllTournamentsData(const QByteArray &data);
    void sendTournamentData(const QByteArray &data);

    void sendHTTPObject(const HTTPReplyObject *obj);
    void sendErrorString(const QString &err);
    void sendSslErrorStrings(const QStringList &err);


private slots:
    void handleRequestetTournaments();
    void handleRequestetTournament();


    void handleSslErrors(QNetworkReply *reply,const QList<QSslError>&errors);
    void handleRedirection(const QUrl &url);

private:

    QNetworkReply* tempReply;

    void sendGetRequest(const QString &method,
                        const QString &urlParameter = QString(),
                        void(LocalHTTPClientAPI::* slot)()= nullptr);
    void sendPostRequest(const QString &method,
                          const QJsonObject &JSON,
                         void(LocalHTTPClientAPI::* slot)()= nullptr);
    void sendDeleteRequest(const QString &method,
                           const QString &urlParameter,
                           void(LocalHTTPClientAPI::* slot)()= nullptr);

    void assembleBasicUrl(QString &hostUrl, QString method);
    void processAndAssembleUrl(QString &hostUrl, QString methodName, QString urlParameter);

    QNetworkAccessManager* _netMng;
    QString _rootDomain;
    QString _userCode;
    const QStringList _remoteMethods = {"GetTournaments",
                                       "GetTournament",
                                      "DeleteTournament",
                                      "UpdateTournament"};
    QTimer _timer;
    QTime _responseTimer;
    bool _isBusy = false;
};



#endif // HTTPINTERFACE_H


