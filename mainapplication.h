#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include <idartsimulator.h>
#include <remoteservercontext.h>
#include <datamodelmanager.h>
#include <gamemanager.h>

#define USERCODE "wQ71HOHNXNaHkDxnnaZ7kj6ujWYW2xBsV1VXxRqp8C/83IgryF1ADA=="
#define HOSTURL "https://dartservice.azurewebsites.net/api/"

class MainApplication : public IDartSimulator
{
    Q_OBJECT
public:
    MainApplication();

public slots:
    void tournament(const QUuid &tournament);
    void tournaments();

    void round(const QUuid &tournament);
    void rounds(const QUuid &tournament);

    void deleteTournament(const QUuid &tournament);
    void createTournament(const QString &name, const QString &startDate, const QString &endDate);

    void appendNewRound();
    void submitPoint(const quint32 &point, const QUuid &userId);

private:
    DataModelManager* _dataMng;
    RemoteServerContext* _rDb;
    GameManager* _gMng;

};

#endif // MAINAPPLICATION_H
