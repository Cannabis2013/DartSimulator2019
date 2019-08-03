#include "gamemanager.h"

GameManager::GameManager()
{

}

bool GameManager::allSubmittet()
{
    return _remainingSubmitters.isEmpty();
}

bool GameManager::hasSubmitted(const QUuid &user)
{
    return !_remainingSubmitters.contains(user);
}

QList<QUuid> GameManager::remainingUsersToSubmit() const
{
    return _remainingSubmitters;
}

void GameManager::appendRound()
{
    auto roundNumber = _rounds_History.count();

    auto newRoundId = QUuid::createUuid();

    _currentRound = newRoundId;
    _rounds_History << newRoundId;
    _remainingSubmitters = _currentAssignedUsers;

    emit newRound(currentTournament(),newRoundId,roundNumber);
}

QUuid GameManager::currentTournament() const
{
    return _currentTournament;
}

void GameManager::setCurrentTournament(const QUuid &currentTournament)
{
    _currentTournament = currentTournament;
}

void GameManager::initiateNewRound()
{
    if(allSubmittet())
        appendRound();
    else
        throw "All users needs to submit";
}

void GameManager::submitPoint(const QUuid &userId, const quint32 &point)
{
    if(hasSubmitted(userId))
        throw "User has already submittet point";

    emit sendPointSubmit(currentRound(),userId,point);
    _remainingSubmitters.removeOne(userId);
}

QUuid GameManager::currentRound() const
{
    return _currentRound;
}

void GameManager::setCurrentRound(const QUuid &currentRound)
{
    _currentRound = currentRound;
}
