#ifndef IDARTSIMULATOR_H
#define IDARTSIMULATOR_H

#include <QTreeWidgetItem>
#include "myobject.h"
#include <quuid.h>

class IDartSimulator : public MyObject
{
    Q_OBJECT
public:
    virtual ~IDartSimulator();

public slots:
    // GUI related
    virtual void createTournament(const QString &name,
                          const int &maxUsers,
                          const int &maxRounds,
                          const QList<QUuid> &users)=0;
    virtual void tournaments()=0;
    virtual void tournament(const QUuid &tournament)=0;

    virtual void round(const QUuid &tournament)=0;
    virtual void rounds(const QUuid &tournament)=0;


    virtual void deleteTournament(const QUuid &tournament)=0;


    // Game control related..
    virtual void appendNewRound()=0;
    virtual void submitPoint(const int &p, const QUuid &user)=0;

signals:
    void sendTournament(QTreeWidgetItem* model,const QString &log);
    void sendTournaments(const QList<QTreeWidgetItem*> &models,const QString &log);

    void sendRound(QTreeWidgetItem* model,const QString &log);
    void sendRounds(QList<QTreeWidgetItem*> models,const QString &log);

    void sendPoint(QTreeWidgetItem* model,const QString &log);
    void sendPoints(QList<QTreeWidgetItem*> models,const QString &log);

    void externalRequestFailed(const QString &error);
};

#endif // IDARTSIMULATOR_H
