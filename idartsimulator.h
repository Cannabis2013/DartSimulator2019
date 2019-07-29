#ifndef IDARTSIMULATOR_H
#define IDARTSIMULATOR_H

#include <QTreeWidgetItem>

struct IDartSimulator
{
    virtual ~IDartSimulator()=0;

    // Model/view related..
    virtual const QList<QTreeWidgetItem*> tournaments()=0;
    virtual const QList<QTreeWidgetItem*> rounds(const QUuid &tournament)=0;
    virtual const QList<QTreeWidgetItem*> points(const QUuid &round)=0;

    virtual const QTreeWidgetItem* model(const QUuid &model)=0;


    // Tournament related..
    virtual void createTournament(const QString &name,
                                  const int &maxUsers,
                                  const int &maxRounds)=0;
    virtual void deleteTournament(const QUuid &tournament)=0;


    // Game control related..
    virtual void newRound()=0;
    virtual QUuid detachHead(const int &round_Index)=0;
    virtual void submitPoint(const int &p, const QUuid &user)=0;
    virtual void submitPoints(const QList<int> &points, const QList<QUuid> &users)=0;
};

#endif // IDARTSIMULATOR_H
