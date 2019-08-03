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
                                  const QString &startDate,
                                  const QString &endDate)=0;
    virtual void tournaments()=0;
    virtual void tournament(const QUuid &tournament)=0;

    virtual void round(const QUuid &tournament)=0;
    virtual void rounds(const QUuid &tournament)=0;

    virtual void deleteTournament(const QUuid &tournament)=0;

    // Game control related..
    virtual void appendNewRound()=0;
    virtual void submitPoint(const quint32 &point, const QUuid &userId)=0;

signals:
    void sendModel(const QTreeWidgetItem* model,const QStringList &headers,const QString &log);
    void sendModels(const QList<QTreeWidgetItem*> models,const QStringList &headers,const QString &log);

    void externalPopupMessage(const QString &title,const QString &msg);
    void externalNotifyResponse();
    void externalRequestFailed(const QString &error);
    void externalGameResponse(const QString &msg);
};

#endif // IDARTSIMULATOR_H
