#include "remoteservercontext.h"

RemoteServerContext::RemoteServerContext(const QString &server, const QString &userCode):
    NetworkManager(server,userCode)
{

}

void RemoteServerContext::createRemoteTournament(const QByteArray &json)
{
    sendPostRequest("CreateTournament",json,QString(),this,SLOT(handleNonPostReply()));
}

void RemoteServerContext::remoteTournament(const QUuid &id)
{
    sendGetRequest("GetTournament",id.toString(QUuid::WithoutBraces),this,SLOT(handleRemoteTournament()));
}

void RemoteServerContext::remoteTournaments()
{
    sendGetRequest("GetTournaments",QString(),this,SLOT(handleRemoteTournaments()));
}

void RemoteServerContext::createRemoteRound(const QByteArray &json, const QUuid &tournament)
{
    sendPostRequest("CreateRound",
                    json,tournament.toString(QUuid::WithoutBraces),
                    this,
                    SLOT(handleCreateRoundReply()));
}

void RemoteServerContext::remoteRound(const QUuid &tournament)
{
    sendGetRequest("GetRound",
                   tournament.toString(QUuid::WithoutBraces),
                   this,
                   SLOT(handleRemoteRound()));
}

void RemoteServerContext::remoteRounds(const QUuid &tournament)
{
    sendGetRequest("GetRounds",
                   tournament.toString(QUuid::WithoutBraces),
                   this,
                   SLOT(handleRemoteRounds()));
}

void RemoteServerContext::remoteRemoveTournament(const QUuid &tournament)
{
    sendDeleteRequest("DeleteTournament",
                      tournament.toString(QUuid::WithoutBraces),
                      this,
                      SLOT(handleNonPostReply()));
}

void RemoteServerContext::submitRemotePoint(const QByteArray &json,const QUuid &round)
{
    sendPostRequest("SubmitPoint",
                    json,
                    round.toString(QUuid::WithoutBraces),
                    this,
                    SLOT(handleSubmitPoint()));
}

void RemoteServerContext::handleNonPostReply()
{
    if(tempReply->error())
    {
        QString err = tempReply->errorString();
        emit sendStatusMsg("Error",err);
        emit sendNotification();
        return;
    }


    QString logMessage = "%1 ms";
    logMessage = logMessage.arg(QString::number(timeElapsed()));
    const QByteArray data = tempReply->readAll();
    QUuid id = QUuid::fromRfc4122(data);
    QString msg = "Operation successed on model with identification: %1";
    msg = msg.arg(id.toString(QUuid::WithoutBraces));
    emit sendNotification();

    emit sendStatusMsg("Success",msg);
}

void RemoteServerContext::handleRemoteTournament()
{
    if(tempReply->error())
    {
        emit sendErrorString(tempReply->errorString());
        tempReply->close();
        return;
    }

    QString logMessage = "%1 ms";
    logMessage = logMessage.arg(QString::number(timeElapsed()));
    const QByteArray data = tempReply->readAll();
    emit sendTournamentData(data,logMessage);
}

void RemoteServerContext::handleRemoteTournaments()
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

void RemoteServerContext::handleCreateRoundReply()
{

}

void RemoteServerContext::handleRemoteRound()
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

void RemoteServerContext::handleRemoteRounds()
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

void RemoteServerContext::handleSubmitPoint()
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
