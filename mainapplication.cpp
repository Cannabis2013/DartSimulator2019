#include "mainapplication.h"

MainApplication::MainApplication()
{
    networkManager = new LocalHTTPClientAPI(HOSTURL,USERCODE);
    dbMng = new ModelDB();
    gameMng = new GameManager(dbMng);
}


const QList<QTreeWidgetItem *> MainApplication::tournaments()
{
}

const QList<QTreeWidgetItem *> MainApplication::rounds(const QUuid &tournament)
{
}

const QList<QTreeWidgetItem *> MainApplication::points(const QUuid &round)
{
}

const QTreeWidgetItem *MainApplication::model(const QUuid &model)
{
}

void MainApplication::createTournament(const QString &name, const int &maxUsers, const int &maxRounds)
{
}

void MainApplication::deleteTournament(const QUuid &tournament)
{
}

void MainApplication::newRound()
{
}

QUuid MainApplication::detachHead(const int &round_Index)
{
}

void MainApplication::submitPoint(const int &p, const QUuid &user)
{
}

void MainApplication::submitPoints(const QList<int> &points, const QList<QUuid> &users)
{
}

void MainApplication::testSlot(const HTTPReplyObject *reply)
{
    print(QString::fromLocal8Bit(reply->getRawData()));
}
