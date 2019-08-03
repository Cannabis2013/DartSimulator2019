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
    int roundNumber = _rounds_History.count();
    QJsonObject obj;
    obj["Id"] = QUuid::createUuid().toString(QUuid::WithoutBraces);
    obj["Round number"] = roundNumber;
    obj["Parent tournament:"] = currentRound().toString(QUuid::WithoutBraces);
    obj["Point identities"] = QJsonArray();

    emit parseRoundToRemote(QJsonDocument(obj).toJson(),currentTournament());
    _remainingSubmitters = _currentAssignedUsers;
}

QUuid GameManager::currentTournament() const
{
    return _currentTournament;
}

void GameManager::setCurrentTournament(const QUuid &currentTournament)
{
    _currentTournament = currentTournament;
}

void GameManager::nextRound()
{
    if(allSubmittet())
        appendRound();
    else
        throw "All users needs to submit";
}

void GameManager::submitPoint(const QUuid &user, const int &point)
{
    if(hasSubmitted(user))
        throw "User has already submittet point";

    QJsonObject obj;
    obj["User"] = user.toString(QUuid::WithoutBraces);
    obj["Point"] = point;

    emit parsePointToRemote(currentRound(),QJsonDocument(obj).toJson());

    _remainingSubmitters.append(user);
}

QUuid GameManager::currentRound() const
{
    return _currentRound;
}

void GameManager::setCurrentRound(const QUuid &currentRound)
{
    _currentRound = currentRound;
}
