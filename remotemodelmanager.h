#ifndef REMOTECONTEXT_H
#define REMOTECONTEXT_H

#include <networkmanager.h>

class RemoteModelManager : public NetworkManager
{
    Q_OBJECT
public:
    RemoteModelManager(const QString &server, const QString &userCode = QString());

public slots:
    // Requests models from remote
    void tournament(const QUuid &id);
    void tournaments();
    void round(const QUuid &tournament);
    void rounds(const QUuid &tournament);
    // Alter remote state
    void addTournament(const QByteArray &json);
    void removeTournament(const QUuid &tournament);
    void addRound(const QByteArray &json, const QUuid &tournament);
    void addPoint(const QByteArray &json, const QUuid &round);
signals:
    void sendModelIdentity(const QByteArray &data, const QString &log);
    void sendTournament(const QByteArray &data,const QString &log);
    void sendTournaments(const QByteArray &data,const QString &log);
    void sendRound(const QByteArray &data,const QString &log);
    void sendRounds(const QByteArray &data,const QString &log);
    void sendPoint(const QByteArray &data,const QString &log);

    void operationFinished(const QUuid &classId);

private slots:
    void handleReply();

    // Handle requests
    virtual void handleRemoteTournament();
    virtual void handleRemoteTournaments();
    virtual void handleRemoteRound();
    virtual void handleRemoteRounds();
    virtual void handleSubmitPoint();
};

#endif // REMOTECONTEXT_H
