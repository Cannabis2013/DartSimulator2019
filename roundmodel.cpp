#include "roundmodel.h"

RoundModel::RoundModel(int roundNumber, const QUuid &id):
    Model (ModelType::RoundModel,id),
    _roundNumber(roundNumber)
{
}

int RoundModel::roundNumber() const
{
    return _roundNumber;
}
