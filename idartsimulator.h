#ifndef IDARTSIMULATOR_H
#define IDARTSIMULATOR_H

#include <QTreeWidgetItem>
#include <quuid.h>

class IDartSimulator : public QObject
{
    Q_OBJECT
public:
    virtual ~IDartSimulator();

public slots:

    // Game control related..

signals:

    // GameManager
    void appendNewRound();
    void submitPoint(const QUuid &userId,const quint32 &point);


    // Reqest models from remote
    void tournaments();
    void tournament(const QUuid &tournament);

    void round(const QUuid &tournament);
    void rounds(const QUuid &tournament);


    /*
     * Alter state of remote
     *  - Create remove models
     */
    void createTournament(const QString &name,
                                  const QString &startDate,
                                  const QString &endDate);

    void deleteTournament(const QUuid &tournament);

    void sendModel(const QTreeWidgetItem* model,const QStringList &headers,const QString &log);
    void sendModels(const QList<QTreeWidgetItem*> models,const QStringList &headers,const QString &log);

    void externalPopupMessage(const QString &title,const QString &msg);
    void externalNotifyResponse(const bool &status, const QTreeWidgetItem* model = nullptr);
    void externalRequestFailed(const QString &error);
    void externalGameResponse(const QString &msg);
};

#endif // IDARTSIMULATOR_H
