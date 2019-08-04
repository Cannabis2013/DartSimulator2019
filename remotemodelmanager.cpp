#include "remotemodelmanager.h"

RemoteModelManager::RemoteModelManager(const QString &server, const QString &userCode):
    NetworkManager(server,userCode)
{

}

void RemoteModelManager::addTournament(const QByteArray &json)
{
    sendPostRequest("CreateTournament",json,QString(),this,SLOT(handleReply()));
}

void RemoteModelManager::tournament(const QUuid &id)
{
    sendGetRequest("GetTournament",id.toString(QUuid::WithoutBraces),this,SLOT(handleRemoteTournament()));
}

void RemoteModelManager::tournaments()
{
    sendGetRequest("GetTournaments",QString(),this,SLOT(handleRemoteTournaments()));
}

void RemoteModelManager::addRound(const QByteArray &json, const QUuid &tournament)
{
    sendPostRequest("CreateRound",
                    json,tournament.toString(QUuid::WithoutBraces),
                    this,
                    SLOT(handleReply()));
}

void RemoteModelManager::round(const QUuid &tournament)
{
    sendGetRequest("GetRound",
                   tournament.toString(QUuid::WithoutBraces),
                   this,
                   SLOT(handleRemoteRound()));
}

void RemoteModelManager::rounds(const QUuid &tournament)
{
    sendGetRequest("GetRounds",
                   tournament.toString(QUuid::WithoutBraces),
                   this,
                   SLOT(handleRemoteRounds()));
}

void RemoteModelManager::removeTournament(const QUuid &tournament)
{
    sendDeleteRequest("DeleteTournament",
                      tournament.toString(QUuid::WithoutBraces),
                      this,
                      SLOT(handleReply()));
}

void RemoteModelManager::addPoint(const QByteArray &json,const QUuid &round)
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
                  "You probably already smoked 10 cigarettes since the request.";
        emit notifyCallers(false,err);
        return;
    }


    QString logMessage = "%1 ms";
    logMessage = logMessage.arg(QString::number(timeElapsed()));
    const QByteArray data = extractData();
    QUuid id = QUuid::fromRfc4122(data);
    QString msg = "Operation successed on model with identification: %1";
    msg = msg.arg(id.toString(QUuid::WithoutBraces));
    emit notifyCallers(true);
}

void RemoteModelManager::handleRemoteTournament()
{
    if(errorOccured())
    {
        emit notifyCallers(false,errorString());
        return;
    }

    QString logMessage = "%1 ms";
    logMessage = logMessage.arg(QString::number(timeElapsed()));
    const QByteArray data = extractData();
    emit sendTournament(data,logMessage);
}

void RemoteModelManager::handleRemoteTournaments()
{
    if(errorOccured())
    {
        emit notifyCallers(false,errorString());
        return;
    }

    QString logMessage = "%1 ms";
    logMessage = logMessage.arg(QString::number(timeElapsed()));
    const QByteArray data = extractData();
    emit sendTournaments(data,logMessage);
}

void RemoteModelManager::handleRemoteRound()
{
    if(errorOccured())
    {
        emit notifyCallers(false,errorString());
        return;
    }

    QString logMessage = "%1 ms";
    logMessage = logMessage.arg(QString::number(timeElapsed()));
    const QByteArray data = extractData();
    emit sendRound(data,logMessage);
}

void RemoteModelManager::handleRemoteRounds()
{
    if(errorOccured())
    {
        emit notifyCallers(false,errorString());
        return;
    }

    QString logMessage = "%1 ms";
    logMessage = logMessage.arg(QString::number(timeElapsed()));
    const QByteArray data = extractData();
    emit sendRounds(data,logMessage);
}

void RemoteModelManager::handleSubmitPoint()
{
    if(errorOccured())
    {
        emit notifyCallers(false,errorString());
        return;
    }

    QString logMessage = "%1 ms";
    logMessage = logMessage.arg(QString::number(timeElapsed()));
    const QByteArray data = extractData();
    emit sendPoint(data,logMessage);
}
