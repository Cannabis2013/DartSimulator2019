#include "mainapplication.h"

MainApplication::MainApplication()
{
    _dataMng = new DataModelManager();
    _rDb = new RemoteServerContext(HOSTURL,USERCODE);
    _gMng = new GameManager();

    _rDb->setTimeoutThreshold(10000);

    // GameManager
    connect(_gMng,&GameManager::newRound,_dataMng,&DataModelManager::remoteAppendRound);
    connect(_gMng,&GameManager::sendPointSubmit,_dataMng,&DataModelManager::remoteAppendPoint);

    // Parse data from local context to remote context
    connect(_dataMng,&DataModelManager::parseTournamentToRemote,_rDb,&RemoteServerContext::createRemoteTournament);
    connect(_dataMng,&DataModelManager::parseRoundToRemote,_rDb,&RemoteServerContext::createRemoteRound);
    connect(_dataMng,&DataModelManager::parsePointToRemote,_rDb,&RemoteServerContext::submitRemotePoint);

    // Parse data from remote context to local context for processing
    connect(_rDb,&RemoteServerContext::sendTournamentData,_dataMng,&DataModelManager::tournamentFromJson);
    connect(_rDb,&RemoteServerContext::sendAllTournamentsData,_dataMng,&DataModelManager::tournamentsFromJson);

    // Return models to user domain
    connect(_dataMng,&DataModelManager::parseTournamentToExternal,this,&IDartSimulator::sendModel);
    connect(_dataMng,&DataModelManager::parseTournamentsToExternal,this,&IDartSimulator::sendModels);

    connect(_rDb,&RemoteServerContext::sendStatusMsg,this,&IDartSimulator::externalPopupMessage);
    connect(_rDb,&RemoteServerContext::sendNotification,this,&IDartSimulator::externalNotifyResponse);

    // Connection/request failed
    connect(_rDb,&RemoteServerContext::sendErrorString,this,&IDartSimulator::externalRequestFailed);
}

void MainApplication::appendNewRound()
{
    try {
        _gMng->initiateNewRound();
    } catch (const char* msg) {
        // TODO: Implement notification to external caller
        Q_UNUSED(msg);
    }
}

void MainApplication::submitPoint(const quint32 &point, const QUuid &userId)
{
    try {
        _gMng->submitPoint(userId,point);
    } catch (const char* msg) {
        // TODO: Implement notification to external caller
        Q_UNUSED(msg);
    }
}

void MainApplication::tournament(const QUuid &tournament)
{
    _rDb->remoteTournament(tournament);
}

void MainApplication::tournaments()
{
    _rDb->remoteTournaments();
}

void MainApplication::round(const QUuid &tournament)
{
    _rDb->remoteRound(tournament);
}


void MainApplication::rounds(const QUuid &tournament)
{
    _rDb->remoteRounds(tournament);
}

void MainApplication::deleteTournament(const QUuid &tournament)
{
    _rDb->remoteRemoveTournament(tournament);
}


void MainApplication::createTournament(const QString &name, const QString &startDate, const QString &endDate)
{
    _dataMng->createTournament(name,startDate,endDate);
}
