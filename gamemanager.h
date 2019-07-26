#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <allmodels.h>
#include <dbmanager.h>

class GameManager
{
public:
    GameManager(const QUuid &season,const QUuid &tournament);

    QUuid currentSeason() const;
    void setCurrentSeason(const QUuid &currentSeason);

    QUuid currentTournament() const;
    void setCurrentTournament(const QUuid &currentTournament);

    QUuid currentRound() const;
    void setCurrentRound(const QUuid &currentRound);
    void appendRound();
    const QList<QUuid>* allRounds();

    const QUuid *currentRound();
    
    void addPoint(PointModel* point);

    void assignUser(const QUuid &user);
    void unAssignUser(const QUuid &user);


private:

    int head() const;
    bool isDetached();

    QUuid _currentSeason = QUuid(), _currentTournament = QUuid(), _currentRound = QUuid();
    QList<QUuid> _rounds;
    int _indexHead = -1;
    DBManager *dbMng;
};

#endif // GAMEMANAGER_H
