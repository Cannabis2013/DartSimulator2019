#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <quuid.h>
#include <qlist.h>

class GameManager
{
public:
    GameManager();

    QUuid currentRound() const;
    void setCurrentRound(const QUuid &currentRound);

    QUuid currentTournament() const;
    void setCurrentTournament(const QUuid &currentTournament);

    void nextRound();

    void submitPoint(const QUuid &user,const int &point);
private:
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
