#ifndef HTTPINTERFACE_H
#define HTTPINTERFACE_H

#include <qnetworkaccessmanager.h>
#include <qnetworkrequest.h>
#include <QNetworkReply>
#include <qnetworkconfiguration.h>
#include <qlist.h>
#include <QTime>
#include <iostream>
#include <quuid.h>
#include <replytimeout.h>

#include <urlparser.h>

using namespace std;

class NetworkManager : public QObject,
        private IUrlParser<IParserService*>
{
    Q_OBJECT
public:
    NetworkManager(const QString &serverHostUrl, const QString &code = QString());

    QString baseUrl() const;
    void setBaseUrl(const QString &baseUrl);

    void setUserCode(const QString &value);

    int timeoutThreshold() const;
    void setTimeoutThreshold(int timeoutThreshold);

signals:
    void sendNotification();
    void sendErrorString(const QString &err);
    void sendSslErrorStrings(const QStringList &err);

protected:

    void sendGetRequest(const QString &method,
                        const QString &urlParameter = QString(),
                        QObject* reciever = nullptr,
                        const char* slot = nullptr);
    void sendPostRequest(const QString &method,
                          const QByteArray &data,
                         const QString &urlParameters = QString(),
                         QObject *reciever = nullptr,
                         const char *slot= nullptr);
    void sendDeleteRequest(const QString &method,
                           const QString &urlParameter = QString(),
                           QObject *reciever = nullptr,
                           const char* slot = nullptr);

    int timeElapsed();
    bool errorOccured();
    QString errorString();
    const QByteArray extractData();

private slots:
    void handleSslErrors(QNetworkReply *reply,const QList<QSslError>&errors);
    void handleServerTimeout();

private:
    void setParserService(IParserService* t);
    IParserService* parserService();

    QNetworkReply* tempReply;
    QNetworkAccessManager* _netMng = new QNetworkAccessManager();
    QString _baseUrl;
    QString _userCode;
    QTime _responseTimer;
    int _timeoutThreshold = 3000;

    IParserService* _parserService;
};

#endif // HTTPINTERFACE_H
