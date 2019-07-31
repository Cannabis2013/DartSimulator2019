#include "round.h"

Round::Round(int number, const QString &tournament):
    Model (ModelType::RoundModel),
    _roundNumber(number),
    _tournamentId(tournament)
{
}

int Round::roundNumber() const
{
    return _roundNumber;
}

QString Round::tournamentId() const
{
    return _tournamentId;
}

