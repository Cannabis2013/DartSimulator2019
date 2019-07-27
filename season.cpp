#include "season.h"

Season::Season():
    Model (ModelType::SeasonModel)
{

}

QString Season::name() const
{
    return _name;
}

void Season::setName(const QString &value)
{
    _name = value;
}

QDateTime Season::dateFinished() const
{
    return _dateFinished;
}

void Season::setDateFinished(const QDateTime &value)
{
    _dateFinished = value;
}

void Season::addTournament(Tournament *tournament)
{
    addChild(tournament);
}

const QList<const Tournament *> *Season::tournaments()
{
    QList<const Tournament*> *result = new QList<const Tournament*>();
    for (Model* child : children())
        *result << dynamic_cast<const Tournament*>(child);

    return result;
}

void Season::removeTournament(Tournament *tournament)
{
    removeChild(tournament);
}
