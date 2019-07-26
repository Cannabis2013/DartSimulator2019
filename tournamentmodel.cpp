#include "tournamentmodel.h"

TournamentModel::TournamentModel(const QUuid &id):
    Model (ModelType::TournamentModel,id)
{
}

QString TournamentModel::name() const
{
    return _name;
}

void TournamentModel::setName(const QString &name)
{
    _name = name;
}

int TournamentModel::numberOfRounds() const
{
    return _numberOfRounds;
}

void TournamentModel::setNumberOfRounds(int numberOfRounds)
{
    _numberOfRounds = numberOfRounds;
}

QDateTime TournamentModel::dateFinished() const
{
    return _dateFinished;
}

void TournamentModel::setDateFinished(const QDateTime &endDate)
{
    _dateFinished = endDate;
}

int TournamentModel::maxUsersAllowed() const
{
    return _maxUsersAllowed;
}

void TournamentModel::setMaxUsersAllowed(int maxUsersAllowed)
{
    _maxUsersAllowed = maxUsersAllowed;
}
