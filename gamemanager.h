#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <quuid.h>
#include <qlist.h>
#include <qobject.h>

class GameManager : public QObject
{
    Q_OBJECT
public:
    GameManager();

public slots:
    void initiateNewRound();
    void submitPoint(const QUuid &userId, const quint32 &point);

signals:
    void newRound(const QUuid &tournament,const QUuid &newRoundId,const int &roundNumber);
    void sendPointSubmit(const QUuid &round, const QUuid &userId, const quint32 &point);
private:

    QUuid currentRound() const;
    void setCurrentRound(const QUuid &currentRound);

    QUuid currentTournament() const;
    void setCurrentTournament(const QUuid &currentTournament);

    bool allSubmittet();
    bool hasSubmitted(const QUuid &user);
    QList<QUuid> remainingUsersToSubmit() const;
    void appendRound();

    QUuid _currentTournament;
    QUuid _currentRound;
    QList<QUuid> _currentAssignedUsers;
    QList<QUuid> _remainingSubmitters;
    QList<QUuid> _rounds_History;
};

#endif // GAMEMANAGER_H
