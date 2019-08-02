#include "remoteservercontex.h"

RemoteServerContex::RemoteServerContex(const QString &server, const QString &userCode):
    NetworkManager(server,userCode)
{

}

void RemoteServerContex::createRemoteTournament(const QByteArray &json)
{
    sendPostRequest("CreateTournament",json,QString(),this,SLOT(handleNonPostReply()));
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

void RemoteServerContex::remoteRemoveTournament(const QUuid &tournament)
{
    sendDeleteRequest("DeleteTournament",
                      tournament.toString(QUuid::WithoutBraces),
                      this,
                      SLOT(handleNonPostReply()));
}

void RemoteServerContex::submitRemotePoint(const QUuid &round, const QByteArray &json)
{
    sendPostRequest("SubmitPoint",
                    json,
                    round.toString(QUuid::WithoutBraces),
                    this,
                    SLOT(handleSubmitPoint()));
}

void RemoteServerContex::handleNonPostReply()
{
    if(tempReply->error())
    {
        emit sendStatusMsg("Error",tempReply->errorString());
        return;
    }

    QString logMessage = "%1 ms";
    logMessage = logMessage.arg(QString::number(timeElapsed()));
    const QByteArray data = tempReply->readAll();
    QUuid id = QUuid::fromRfc4122(data);
    QString msg = "Operation successed on model with identification: %1";
    msg = msg.arg(id.toString(QUuid::WithoutBraces));

    emit sendStatusMsg("Success",msg);
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
        cout << tempReply->errorString().toStdString() << endl;
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
