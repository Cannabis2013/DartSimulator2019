#include "round.h"

Round::Round(int number):
    Model (ModelType::RoundModel),
    _roundNumber(number)
{
}

int Round::roundNumber() const
{
    return _roundNumber;
}

void Round::addPoint(Point *point)
{
    _addChild(point);
}

void Round::removePoint(Point *point)
{
    _removeChild(point);
}
