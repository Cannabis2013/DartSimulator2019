#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include <gamemanager.h>
#include <idartsimulator.h>
#include <remotedatabasecontext.h>
#include <localdatabasecontext.h>

#define USERCODE "wQ71HOHNXNaHkDxnnaZ7kj6ujWYW2xBsV1VXxRqp8C/83IgryF1ADA=="
#define HOSTURL "https://dartservice.azurewebsites.net/api/"

class MainApplication : public IDartSimulator
{
    Q_OBJECT
public:
    MainApplication();

    void requestAllTournaments();
    void requestTournament(const QUuid &tournament);
    void requestAllRounds(const QUuid &tournament);

    void createTournament(const QString &name, const int &maxUsers, const int &maxRounds);
    void deleteTournament(const QUuid &tournament);
    void appendNewRound();
    void submitPoint(const int &p, const QUuid &user);

private:
    LocalDatabaseContext* _lDb;
    RemoteDatabaseContext* _rDb;

    GameManager* _gMng;
};

#endif // MAINAPPLICATION_H
