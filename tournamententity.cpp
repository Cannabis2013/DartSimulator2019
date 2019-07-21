#include "tournamententity.h"

TournamentEntity::TournamentEntity():
    ModelEntity (ModelType::TournamentModel)
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

QDate TournamentEntity::dateFinished() const
{
    return _dateFinished;
}

void TournamentEntity::setDateFinished(const QDate &endDate)
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
