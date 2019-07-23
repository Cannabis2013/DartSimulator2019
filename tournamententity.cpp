#include "tournamententity.h"

TournamentEntity::TournamentEntity(const QUuid &id):
    ModelEntity (ModelType::TournamentModel,id)
{
}


void TournamentEntity::toJSON()
{

}

QString TournamentEntity::name() const
{
    return _name;
}

void TournamentEntity::setName(const QString &name)
{
    _name = name;
}

int TournamentEntity::numberOfRounds() const
{
    return _numberOfRounds;
}

void TournamentEntity::setNumberOfRounds(int numberOfRounds)
{
    _numberOfRounds = numberOfRounds;
}

QDateTime TournamentEntity::dateFinished() const
{
    return _dateFinished;
}

void TournamentEntity::setDateFinished(const QDateTime &endDate)
{
    _dateFinished = endDate;
}

int TournamentEntity::maxUsersAllowed() const
{
    return _maxUsersAllowed;
}

void TournamentEntity::setMaxUsersAllowed(int maxUsersAllowed)
{
    _maxUsersAllowed = maxUsersAllowed;
}

QList<QUuid> TournamentEntity::allRoundIdentities()
{
    return allIdentifiers();
}

void TournamentEntity::addRoundIdentities(const QList<QUuid> &identities)
{
    appendIdentifiers(identities);
}
