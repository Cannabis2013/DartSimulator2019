#include "roundmodel.h"

RoundModel::RoundModel(int roundNumber, const QUuid &id):
    Model (ModelType::RoundModel,id),
    _roundNumber(roundNumber)
{
}

QList<QUuid> RoundModel::allPointIdentities() const
{
    return allIdentifiers();
}

void RoundModel::addPointIdentity(const QUuid &point)
{
    appendIdentifier(point);
}

void RoundModel::addPointIdentities(const QList<QUuid> &pointIdentities)
{
    appendIdentifiers(pointIdentities);
}

int RoundModel::roundNumber() const
{
    return _roundNumber;
}
