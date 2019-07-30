#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <allmodels.h>
#include <modeldb.h>
#include <QObject>



class GameManager : public QObject
{
    Q_OBJECT
public:
    GameManager(IDatabaseManager<Model,Model::ModelType>* database);

    QUuid currentTournament() const;
    void setCurrentTournament(const QUuid &value);

    QUuid currentRound() const;

    int totalPoints(const QUuid &user = QUuid());

    void initiateNext();

    void addPoint(const int point, const QUuid &user);

private:
    const QList<const Point *> points();

    bool isDetached() const;

    QUuid appendNextRound();

    int _HEAD = -1;
    QUuid _currentTournament;
    IDatabaseManager<Model,Model::ModelType>* db;
};

#endif // GAMEMANAGER_H
