#include "mainapplication.h"

MainApplication::MainApplication()
{
    _lDb = new LocalDatabaseContext();
    _rDb = new RemoteServerContex(HOSTURL,USERCODE);

    _rDb->setTimeoutThreshold(4500); // Initialize the timeout threshold to 4500 ms

    // Parse data from local context to remote context
    connect(_lDb,&LocalDatabaseContext::parseTournamentToRemote,_rDb,&RemoteServerContex::createRemoteTournament);
    connect(_lDb,&LocalDatabaseContext::parseRoundToRemote,_rDb,&RemoteServerContex::createRemoteRound);
    connect(_lDb,&LocalDatabaseContext::parsePointToRemote,_rDb,&RemoteServerContex::submitRemotePoint);

    // Parse data from remote context to local context for processing
    connect(_rDb,&RemoteServerContex::sendTournamentData,_lDb,&LocalDatabaseContext::processTournament);
    connect(_rDb,&RemoteServerContex::sendAllTournamentsData,_lDb,&LocalDatabaseContext::processTournaments);

    // Return models to user domain
    connect(_lDb,&LocalDatabaseContext::parseTournamentToExternal,this,&IDartSimulator::sendModel);
    connect(_lDb,&LocalDatabaseContext::parseTournamentsToExternal,this,&IDartSimulator::sendModels);

    connect(_rDb,&RemoteServerContex::sendStatusMsg,this,&IDartSimulator::externalPopupMessage);

    // Connection/request failed
    connect(_rDb,&RemoteServerContex::sendErrorString,this,&IDartSimulator::externalRequestFailed);
}

void MainApplication::createTournament(const QString &name,
                                       const int &maxUsers,
                                       const int &maxRounds,
                                       const QList<QUuid> &users)
{
    _lDb->createTournament(name,maxRounds,maxUsers,users);
}

void MainApplication::deleteTournament(const QUuid &tournament, const QUuid &callerId)
{
    _rDb->remoteRemoveTournament(tournament);
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

