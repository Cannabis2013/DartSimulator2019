#include "remotemodelmanager.h"

RemoteModelManager::RemoteModelManager(const QString &server, const QString &userCode):
    NetworkManager(server,userCode)
{

}

void RemoteModelManager::createRemoteTournament(const QByteArray &json)
{
    sendPostRequest("CreateTournament",json,QString(),this,SLOT(handleReply()));
}

void RemoteModelManager::remoteTournament(const QUuid &id)
{
    sendGetRequest("GetTournament",id.toString(QUuid::WithoutBraces),this,SLOT(handleRemoteTournament()));
}

void RemoteModelManager::remoteTournaments()
{
    sendGetRequest("GetTournaments",QString(),this,SLOT(handleRemoteTournaments()));
}

void RemoteModelManager::createRemoteRound(const QByteArray &json, const QUuid &tournament)
{
    sendPostRequest("CreateRound",
                    json,tournament.toString(QUuid::WithoutBraces),
                    this,
                    SLOT(handleReply()));
}

void RemoteModelManager::remoteRound(const QUuid &tournament)
{
    sendGetRequest("GetRound",
                   tournament.toString(QUuid::WithoutBraces),
                   this,
                   SLOT(handleRemoteRound()));
}

void RemoteModelManager::remoteRounds(const QUuid &tournament)
{
    sendGetRequest("GetRounds",
                   tournament.toString(QUuid::WithoutBraces),
                   this,
                   SLOT(handleRemoteRounds()));
}

void RemoteModelManager::remoteRemoveTournament(const QUuid &tournament)
{
    sendDeleteRequest("DeleteTournament",
                      tournament.toString(QUuid::WithoutBraces),
                      this,
                      SLOT(handleReply()));
}

void RemoteModelManager::submitRemotePoint(const QByteArray &json,const QUuid &round)
{
    sendPostRequest("SubmitPoint",
                    json,
                    round.toString(QUuid::WithoutBraces),
                    this,
                    SLOT(handleSubmitPoint()));
}

void RemoteModelManager::handleReply()
{
    if(errorOccured())
    {
        QString err = errorString();
        if(err == "Operation canceled")
            err = "Operation was abortet probably due to server timeout. \n "
                  "Go out and buy some more beer or cigarettes. \n "
                  "You probably already smoked 10 of those in the time you waited.";
        emit sendStatusMsg("Error",err);
        emit sendNotification();
        return;
    }


    QString logMessage = "%1 ms";
    logMessage = logMessage.arg(QString::number(timeElapsed()));
    const QByteArray data = extractData();
    QUuid id = QUuid::fromRfc4122(data);
    QString msg = "Operation successed on model with identification: %1";
    msg = msg.arg(id.toString(QUuid::WithoutBraces));
    emit sendNotification();

    emit sendStatusMsg("Success",msg);
}

void RemoteModelManager::handleRemoteTournament()
{
    if(errorOccured())
    {
        emit sendErrorString(errorString());
        return;
    }

    QString logMessage = "%1 ms";
    logMessage = logMessage.arg(QString::number(timeElapsed()));
    const QByteArray data = extractData();
    emit sendTournamentData(data,logMessage);
}

void RemoteModelManager::handleRemoteTournaments()
{
    if(errorOccured())
    {
        emit sendErrorString(errorString());
        return;
    }

    QString logMessage = "%1 ms";
    logMessage = logMessage.arg(QString::number(timeElapsed()));
    const QByteArray data = extractData();
    emit sendAllTournamentsData(data,logMessage);
}

void RemoteModelManager::handleRemoteRound()
{
    if(errorOccured())
    {
        emit sendErrorString(errorString());
        return;
    }

    QString logMessage = "%1 ms";
    logMessage = logMessage.arg(QString::number(timeElapsed()));
    const QByteArray data = extractData();
    emit sendRoundData(data,logMessage);
}

void RemoteModelManager::handleRemoteRounds()
{
    if(errorOccured())
    {
        emit sendErrorString(errorString());
        return;
    }

    QString logMessage = "%1 ms";
    logMessage = logMessage.arg(QString::number(timeElapsed()));
    const QByteArray data = extractData();
    emit sendRoundsData(data,logMessage);
}

void RemoteModelManager::handleSubmitPoint()
{
    if(errorOccured())
    {
        emit sendErrorString(errorString());
        return;
    }

    QString logMessage = "%1 ms";
    logMessage = logMessage.arg(QString::number(timeElapsed()));
    const QByteArray data = extractData();
    emit sendPointData(data,logMessage);
}
