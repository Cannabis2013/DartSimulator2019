#ifndef IDARTSIMULATOR_H
#define IDARTSIMULATOR_H

#include <QTreeWidgetItem>
#include "myobject.h"

class IDartSimulator : public MyObject
{
    Q_OBJECT
public:
    virtual ~IDartSimulator();

    virtual void requestAllTournaments()=0;
    virtual void requestTournament(const QUuid &tournament)=0;

    virtual void requestAllRounds(const QUuid &tournament)=0;


    // Tournament related..
    virtual void createTournament(const QString &name,
                                  const int &maxUsers,
                                  const int &maxRounds)=0;
    virtual void deleteTournament(const QUuid &tournament)=0;


    // Game control related..
    virtual void appendNewRound()=0;
    virtual void submitPoint(const int &p, const QUuid &user)=0;

signals:
    void sendTournament(QTreeWidgetItem* model);
    void sendTournaments(QList<QTreeWidgetItem*> models);

    void sendRound(QTreeWidgetItem* model);
    void sendRounds(QList<QTreeWidgetItem*> models);

    void sendPoint(QTreeWidgetItem* model);
    void sendPoints(QList<QTreeWidgetItem*> models);
};

#endif // IDARTSIMULATOR_H
