#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <allmodels.h>
#include <QObject>

class GameManager : public QObject
{
    Q_OBJECT
public:
    GameManager();

    QUuid currentTournament() const;
    void setCurrentTournament(const QUuid &value);

    QUuid currentRound() const;

    void initiateNext();

    void addPoint(const int point, const QUuid &user);

private:
    const QList<const Point *> points();


    QUuid appendNextRound();

    int _HEAD = -1;
    QUuid _currentTournament;
};

#endif // GAMEMANAGER_H
