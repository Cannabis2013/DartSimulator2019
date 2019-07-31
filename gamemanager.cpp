#include "gamemanager.h"

GameManager::GameManager()
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
    // TODO: Implement functionality that gets the current round id from remote
    return QUuid();
}

const QList<const Point *> GameManager::points()
{
    // TODO: Implement functionality which retrieves point objects from remote
}

void GameManager::initiateNext()
{
    const QUuid round = appendNextRound();
    Q_UNUSED(round);
}

void GameManager::addPoint(const int point, const QUuid &user)
{
    // TODO: Implement functionality which add a point object to remote
}

QUuid GameManager::appendNextRound()
{
    // TODO: Implement functionality which adds a round object to remote
}
