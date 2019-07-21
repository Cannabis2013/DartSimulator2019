#include "seasonentity.h"

SeasonEntity::SeasonEntity():
    ModelEntity (ModelType::SeasonModel)
{

}

QString SeasonEntity::name() const
{
    return _name;
}

void SeasonEntity::setName(const QString &value)
{
    _name = value;
}

QDateTime SeasonEntity::dateFinished() const
{
    return _dateFinished;
}

void SeasonEntity::setDateFinished(const QDateTime &value)
{
    _dateFinished = value;
}

void SeasonEntity::addTournamentIdentity(const QUuid &entityIdentity)
{
    appendIdentifier(entityIdentity);
}

void SeasonEntity::toJSON()
{

}
