#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <allmodels.h>
#include <dbmanager.h>
#include <qobject.h>

class GameManager : public QObject
{
    Q_OBJECT
public:
    GameManager(const QUuid &season,const QUuid &tournament);

    QUuid currentSeason() const;
    void setCurrentSeason(const QUuid &currentSeason);

    QUuid currentTournament() const;
    void setCurrentTournament(const QUuid &currentTournament);

    void setCurrentRound(const QUuid &currentRound);
    const QList<QUuid>* allRounds();

    const QUuid *currentRoundAtHead();
    
    void resetTournament();
    void resetRound();


public slots:
    void assignUser(const QUuid &user);
    void unAssignUser(const QUuid &user);

    void nextRound();

private:
    void appendNextRound();

    void addPoint(PointModel* point);

    int head() const;
    bool isDetached();

    QUuid _currentSeason = QUuid(), _currentTournament = QUuid(), _currentRound = QUuid();
    QList<QUuid> _rounds;
    int _indexHead = -1;
    DBManager *dbMng;
};

#endif // GAMEMANAGER_H
