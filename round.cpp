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
    addChild(point);
}

void Round::removePoint(Point *point)
{
    removeChild(point);
}
