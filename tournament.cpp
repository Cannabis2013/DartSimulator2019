#include "tournament.h"

Tournament::Tournament():
    Model (ModelType::TournamentModel)
{
}

QString Tournament::name() const
{
    return _name;
}

void Tournament::setName(const QString &name)
{
    _name = name;
}

int Tournament::numberOfRounds() const
{
    return _numberOfRounds;
}

void Tournament::setNumberOfRounds(int numberOfRounds)
{
    _numberOfRounds = numberOfRounds;
}

int Tournament::numberOfUsersAssigned() const
{
    return _users.count();
}

QList<QUuid> Tournament::users() const
{
    return _users;
}

void Tournament::setUsers(const QList<QUuid> &users)
{
    _users = users;
}
