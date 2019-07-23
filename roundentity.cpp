#include "roundentity.h"

RoundEntity::RoundEntity(int number):
    ModelEntity (ModelType::RoundModel),
    _roundNumber(number)
{
}

QList<QUuid> RoundEntity::allPointIdentities()
{
    return allIdentifiers();
}

int RoundEntity::roundNumber() const
{
    return _roundNumber;
}
