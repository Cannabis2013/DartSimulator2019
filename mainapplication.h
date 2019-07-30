#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include <gamemanager.h>
#include <modeldb.h>
#include <idartsimulator.h>
#include <localhttpclientapi.h>

#define USERCODE "wQ71HOHNXNaHkDxnnaZ7kj6ujWYW2xBsV1VXxRqp8C/83IgryF1ADA=="
#define HOSTURL "https://dartservice.azurewebsites.net/api/"

class MainApplication :public MyObject, public IDartSimulator
{
    Q_OBJECT
public:
    MainApplication();

    const QList<QTreeWidgetItem *> tournaments();
    const QList<QTreeWidgetItem *> rounds(const QUuid &tournament);
    const QList<QTreeWidgetItem *> points(const QUuid &round);
    const QTreeWidgetItem *model(const QUuid &model);
    void createTournament(const QString &name, const int &maxUsers, const int &maxRounds);
    void deleteTournament(const QUuid &tournament);
    void newRound();
    QUuid detachHead(const int &round_Index);
    void submitPoint(const int &p, const QUuid &user);
    void submitPoints(const QList<int> &points, const QList<QUuid> &users);

signals:
    void sendDataReply(const HTTPReplyObject* reply);

private slots:
    void testSlot(const HTTPReplyObject* reply);

private:
    LocalHTTPClientAPI* networkManager;
    GameManager* gameMng;
    IDatabaseManager<Model,Model::ModelType> *dbMng;


};

#endif // MAINAPPLICATION_H
