#include "seasonentity.h"

SeasonEntity::SeasonEntity(const QUuid &id):
    ModelEntity (ModelType::SeasonModel,id)
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

void SeasonEntity::addTournamentIdentities(const QList<QUuid> identities)
{
    appendIdentifiers(identities);
}
