#include "roundentity.h"

RoundEntity::RoundEntity(int number):
    ModelEntity (ModelType::RoundModel),
    _roundNumber(number)
{
}

int RoundEntity::roundNumber() const
{
    return _roundNumber;
}
