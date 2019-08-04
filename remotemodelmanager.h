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
    void remoteTournament(const QUuid &id);
    void remoteTournaments();
    void remoteRound(const QUuid &tournament);
    void remoteRounds(const QUuid &tournament);
    // Upload models to remote
    void createRemoteTournament(const QByteArray &json);
    void createRemoteRound(const QByteArray &json, const QUuid &tournament);
    void submitRemotePoint(const QByteArray &json, const QUuid &round);
    // Delete remote model
    void remoteRemoveTournament(const QUuid &tournament);
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
    void handleReply();

    // Handle requests
    virtual void handleRemoteTournament();
    virtual void handleRemoteTournaments();
    virtual void handleRemoteRound();
    virtual void handleRemoteRounds();
    virtual void handleSubmitPoint();
};

#endif // REMOTECONTEXT_H
