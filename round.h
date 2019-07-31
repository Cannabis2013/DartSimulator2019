#ifndef ROUNDENTITY_H
#define ROUNDENTITY_H

#include <model.h>
#include <point.h>

class Round : public Model
{
public:
    Round(int number, const QString &tournament);

    int roundNumber() const;


    QString tournamentId() const;

private:
    const QString _tournamentId;
    const int _roundNumber;
};

#endif // ROUNDENTITY_H
