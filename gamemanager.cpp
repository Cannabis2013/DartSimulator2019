#include "gamemanager.h"



GameManager::GameManager(const QUuid &season, const QUuid &tournament):
    _currentSeason(season),_currentTournament(tournament)
{
    dbMng = new DBManager();

    const TournamentModel* tModel = dbMng->model<TournamentModel>(tournament);
    _rounds = *tModel->allIdentifiers();
}
QUuid GameManager::currentSeason() const
{
    return _currentSeason;
}

void GameManager::setCurrentSeason(const QUuid &currentSeason)
{
    _currentSeason = currentSeason;
}

QUuid GameManager::currentTournament() const
{
    return _currentTournament;
}

void GameManager::setCurrentTournament(const QUuid &currentTournament)
{
    _currentTournament = currentTournament;
}

void GameManager::setCurrentRound(const QUuid &currentRound)
{
    _currentRound = currentRound;
}

void GameManager::appendNextRound()
{
    RoundModel* round = new RoundModel(_rounds.count());
    dbMng->addModel(round,currentTournament());
}

const QList<QUuid> *GameManager::allRounds()
{
    return &_rounds;
}

const QUuid *GameManager::currentRoundAtHead()
{
    return &_rounds.at(_indexHead);
}

void GameManager::addPoint(PointModel *point)
{
    if(!isDetached())
        dbMng->addModel(point,*currentRoundAtHead());
}

void GameManager::resetTournament()
{
    dbMng->resetModel(currentTournament());
}

void GameManager::resetRound()
{
    dbMng->resetModel(*currentRoundAtHead());
}

void GameManager::assignUser(const QUuid &user)
{
    dbMng->addSubIdentity(user,currentTournament());
}

void GameManager::unAssignUser(const QUuid &user)
{
    if(dbMng->modelType(user) == mType::UserModel)
        dbMng->removeChildIdentity(user,currentTournament());
}

void GameManager::nextRound()
{
    appendNextRound();
}

int GameManager::head() const
{
    return _indexHead;
}

bool GameManager::isDetached()
{
    return _indexHead != _rounds.count() - 1 || _indexHead == -1;
}
