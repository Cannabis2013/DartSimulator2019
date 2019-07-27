#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <allmodels.h>
#include <modeldb.h>
#include <QObject>

class GameManager : public QObject
{
    Q_OBJECT
public:
    GameManager(mInterface* database);

    QUuid currentTournament() const;
    void setCurrentTournament(const QUuid &value);

    QUuid currentRound() const;

public slots:
    void addPoint(Point* p);

private:
    QUuid appendNextRound();

    QUuid _currentTournament;
    mInterface* db;
};

#endif // GAMEMANAGER_H
