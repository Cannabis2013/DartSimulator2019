#include "remoteservercontex.h"

RemoteServerContex::RemoteServerContex(const QString &server, const QString &userCode):
    NetworkManager(server,userCode)
{

}

void RemoteServerContex::createRemoteTournament(const QByteArray &json)
{
    sendPostRequest("CreateTournament",json,QString(),this,SLOT(handleCreateTournamentReply()));
}

void RemoteServerContex::remoteTournament(const QUuid &id)
{
    sendGetRequest("GetTournament",id.toString(QUuid::WithoutBraces),this,SLOT(handleRemoteTournament()));
}

void RemoteServerContex::remoteTournaments()
{
    sendGetRequest("GetTournaments",QString(),this,SLOT(handleRemoteTournaments()));
}

void RemoteServerContex::createRemoteRound(const QByteArray &json, const QUuid &tournament)
{
    sendPostRequest("CreateRound",
                    json,tournament.toString(QUuid::WithoutBraces),
                    this,
                    SLOT(handleCreateRoundReply()));
}

void RemoteServerContex::remoteRound(const QUuid &tournament)
{
    sendGetRequest("GetRound",
                   tournament.toString(QUuid::WithoutBraces),
                   this,
                   SLOT(handleRemoteRound()));
}

void RemoteServerContex::remoteRounds(const QUuid &tournament)
{
    sendGetRequest("GetRounds",
                   tournament.toString(QUuid::WithoutBraces),
                   this,
                   SLOT(handleRemoteRounds()));
}

void RemoteServerContex::submitRemotePoint(const QUuid &round, const QByteArray &json)
{
    sendPostRequest("SubmitPoint",
                    json,
                    round.toString(QUuid::WithoutBraces),
                    this,
                    SLOT(handleSubmitPoint()));
}

void RemoteServerContex::handleSuccess()
{

}

void RemoteServerContex::handleCreateTournamentReply()
{
    if(tempReply->error())
    {
        emit sendErrorString(tempReply->errorString());
        return;
    }

    QString logMessage = "%1 ms";
    logMessage = logMessage.arg(QString::number(timeElapsed()));
    const QByteArray data = tempReply->readAll();
    emit sendCreatedTournamentId(data,logMessage);

}

void RemoteServerContex::handleRemoteTournament()
{
    if(tempReply->error())
    {
        emit sendErrorString(tempReply->errorString());
        return;
    }

    QString logMessage = "%1 ms";
    logMessage = logMessage.arg(QString::number(timeElapsed()));
    const QByteArray data = tempReply->readAll();
    emit sendTournamentData(data,logMessage);
}

void RemoteServerContex::handleRemoteTournaments()
{
    if(tempReply->error())
    {
        emit sendErrorString(tempReply->errorString());
        return;
    }

    QString logMessage = "%1 ms";
    logMessage = logMessage.arg(QString::number(timeElapsed()));
    const QByteArray data = tempReply->readAll();
    emit sendAllTournamentsData(data,logMessage);
}

void RemoteServerContex::handleCreateRoundReply()
{

}

void RemoteServerContex::handleRemoteRound()
{
    if(tempReply->error())
    {
        emit sendErrorString(tempReply->errorString());
        return;
    }

    QString logMessage = "%1 ms";
    logMessage = logMessage.arg(QString::number(timeElapsed()));
    const QByteArray data = tempReply->readAll();
    emit sendRoundData(data,logMessage);
}

void RemoteServerContex::handleRemoteRounds()
{
    if(tempReply->error())
    {
        emit sendErrorString(tempReply->errorString());
        return;
    }

    QString logMessage = "%1 ms";
    logMessage = logMessage.arg(QString::number(timeElapsed()));
    const QByteArray data = tempReply->readAll();
    emit sendRoundsData(data,logMessage);
}

void RemoteServerContex::handleSubmitPoint()
{
    if(tempReply->error())
    {
        emit sendErrorString(tempReply->errorString());
        return;
    }

    QString logMessage = "%1 ms";
    logMessage = logMessage.arg(QString::number(timeElapsed()));
    const QByteArray data = tempReply->readAll();
    emit sendPointData(data,logMessage);
}
