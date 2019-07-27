#include "gamemanager.h"

GameManager::GameManager(mInterface *database):
    db(database)
{
}

QUuid GameManager::currentTournament() const
{
    return _currentTournament;
}

void GameManager::setCurrentTournament(const QUuid &value)
{
    _currentTournament = value;
}

QUuid GameManager::currentRound() const
{
    return db->children_of(currentTournament())->last()->id();
}

void GameManager::addPoint(Point *p)
{
    db->addModel(p,currentRound());
}

QUuid GameManager::appendNextRound()
{
    int roundNumber = db->children_of(currentTournament())->count();
    Round* r = new Round(roundNumber);
    db->addModel(r,currentTournament());
    return r->id();
}
