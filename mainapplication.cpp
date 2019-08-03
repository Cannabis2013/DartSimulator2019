#include "mainapplication.h"

MainApplication::MainApplication()
{
    _lDb = new LocalDatabaseContext();
    _rDb = new RemoteServerContext(HOSTURL,USERCODE);

    _rDb->setTimeoutThreshold(10000);

    // Parse data from local context to remote context
    connect(_lDb,&LocalDatabaseContext::parseTournamentToRemote,_rDb,&RemoteServerContext::createRemoteTournament);
    connect(_lDb,&LocalDatabaseContext::parseRoundToRemote,_rDb,&RemoteServerContext::createRemoteRound);
    connect(_lDb,&LocalDatabaseContext::parsePointToRemote,_rDb,&RemoteServerContext::submitRemotePoint);

    // Parse data from remote context to local context for processing
    connect(_rDb,&RemoteServerContext::sendTournamentData,_lDb,&LocalDatabaseContext::tournamentFromJson);
    connect(_rDb,&RemoteServerContext::sendAllTournamentsData,_lDb,&LocalDatabaseContext::tournamentsFromJson);

    // Return models to user domain
    connect(_lDb,&LocalDatabaseContext::parseTournamentToExternal,this,&IDartSimulator::sendModel);
    connect(_lDb,&LocalDatabaseContext::parseTournamentsToExternal,this,&IDartSimulator::sendModels);

    connect(_rDb,&RemoteServerContext::sendStatusMsg,this,&IDartSimulator::externalPopupMessage);
    connect(_rDb,&RemoteServerContext::sendNotification,this,&IDartSimulator::externalNotifyResponse);

    // Connection/request failed
    connect(_rDb,&RemoteServerContext::sendErrorString,this,&IDartSimulator::externalRequestFailed);
}

void MainApplication::createTournament(const QString &name,
                                       const int &maxUsers,
                                       const int &maxRounds,
                                       const QList<QUuid> &users)
{
    _lDb->createTournament(name,maxRounds,maxUsers,users);
}

void MainApplication::appendNewRound()
{
    try {
        _lDb->nextRound();
    } catch (const char* msg) {
        // TODO: Implement some error handling
    }
}

void MainApplication::submitPoint(const int &p, const QUuid &user)
{
    _lDb->submitPoint(user,p);
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
