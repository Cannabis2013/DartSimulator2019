#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include <idartsimulator.h>
#include <remoteservercontext.h>
#include <localdatabasecontext.h>

#define USERCODE "wQ71HOHNXNaHkDxnnaZ7kj6ujWYW2xBsV1VXxRqp8C/83IgryF1ADA=="
#define HOSTURL "https://dartservice.azurewebsites.net/api/"

class MainApplication : public IDartSimulator
{
    Q_OBJECT
public:
    MainApplication();

    void tournament(const QUuid &tournament);
    void tournaments();

    void round(const QUuid &tournament);
    void rounds(const QUuid &tournament);

    void createTournament(const QString &name, const int &maxUsers, const int &maxRounds, const QList<QUuid> &users);
    void appendNewRound();
    void submitPoint(const int &p, const QUuid &user);

private:
    LocalDatabaseContext* _lDb;
    RemoteServerContext* _rDb;

    // IDartSimulator interface
public slots:
    void deleteTournament(const QUuid &tournament);
};

#endif // MAINAPPLICATION_H
