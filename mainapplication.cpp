#include "mainapplication.h"

MainApplication::MainApplication()
{
    _lDb = new LocalDatabaseContext();
    _rDb = new RemoteDatabaseContext(HOSTURL,USERCODE);
    _gMng = new GameManager();

    connect(_rDb,&RemoteDatabaseContext::sendTournamentData,_lDb,&LocalDatabaseContext::createTournament);
    connect(_rDb,&RemoteDatabaseContext::sendAllTournamentsData,_lDb,&LocalDatabaseContext::createTournaments);

    connect(_lDb,&LocalDatabaseContext::sendTournament,this,&MainApplication::sendTournament);
    connect(_lDb,&LocalDatabaseContext::sendTournaments,this,&MainApplication::sendTournaments);
}

void MainApplication::createTournament(const QString &name, const int &maxUsers, const int &maxRounds)
{

}

void MainApplication::deleteTournament(const QUuid &tournament)
{
}

void MainApplication::appendNewRound()
{

}

void MainApplication::submitPoint(const int &p, const QUuid &user)
{
}



void MainApplication::requestAllTournaments()
{
}

void MainApplication::requestTournament(const QUuid &tournament)
{
}

void MainApplication::requestAllRounds(const QUuid &tournament)
{
}
