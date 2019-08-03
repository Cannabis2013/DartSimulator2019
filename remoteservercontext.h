#ifndef REMOTECONTEXT_H
#define REMOTECONTEXT_H

#include <networkmanager.h>

class RemoteServerContext : public NetworkManager
{
    Q_OBJECT
public:
    RemoteServerContext(const QString &server, const QString &userCode = QString());

    // Requests
    void remoteTournament(const QUuid &id);
    void remoteTournaments();
    void remoteRound(const QUuid &tournament);
    void remoteRounds(const QUuid &tournament);

    // Remote operations

    void remoteRemoveTournament(const QUuid &tournament);

public slots:
    void createRemoteTournament(const QByteArray &json);
    void createRemoteRound(const QByteArray &json, const QUuid &tournament);
    void submitRemotePoint(const QUuid &round, const QByteArray &json);

signals:
    void sendModelIdentity(const QByteArray &data, const QString &log);
    void sendTournamentData(const QByteArray &data,const QString &log);
    void sendAllTournamentsData(const QByteArray &data,const QString &log);
    void sendRoundData(const QByteArray &data,const QString &log);
    void sendRoundsData(const QByteArray &data,const QString &log);
    void sendPointData(const QByteArray &data,const QString &log);

    void sendStatusMsg(const QString &title, const QString &msg);
    void operationFinished(const QUuid &classId);

private slots:
    virtual void handleNonPostReply();

    // Handle requests

    virtual void handleRemoteTournament();
    virtual void handleRemoteTournaments();
    virtual void handleCreateRoundReply();
    virtual void handleRemoteRound();
    virtual void handleRemoteRounds();
    virtual void handleSubmitPoint();
};

#endif // REMOTECONTEXT_H
