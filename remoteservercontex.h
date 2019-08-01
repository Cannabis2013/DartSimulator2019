#ifndef REMOTECONTEXT_H
#define REMOTECONTEXT_H

#include <networkmanager.h>

class RemoteServerContex : public NetworkManager
{
    Q_OBJECT
public:
    RemoteServerContex(const QString &server, const QString &userCode = QString());

    // Requests
    void remoteTournament(const QUuid &id);
    void remoteTournaments();
    void remoteRound(const QUuid &tournament);
    void remoteRounds(const QUuid &tournament);

public slots:
    void createRemoteTournament(const QByteArray &json);
    void createRemoteRound(const QByteArray &json, const QUuid &tournament);
    void submitRemotePoint(const QUuid &round, const QByteArray &json);

signals:
    void sendCreatedTournamentId(const QByteArray &data, const QString &log);
    void sendTournamentData(const QByteArray &data,const QString &log);
    void sendAllTournamentsData(const QByteArray &data,const QString &log);
    void sendRoundData(const QByteArray &data,const QString &log);
    void sendRoundsData(const QByteArray &data,const QString &log);
    void sendPointData(const QByteArray &data,const QString &log);

private slots:
    virtual void handleSuccess();

    // Handle requests

    virtual void handleCreateTournamentReply();
    virtual void handleRemoteTournament();
    virtual void handleRemoteTournaments();
    virtual void handleCreateRoundReply();
    virtual void handleRemoteRound();
    virtual void handleRemoteRounds();
    virtual void handleSubmitPoint();
};

#endif // REMOTECONTEXT_H
