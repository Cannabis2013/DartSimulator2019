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

    // Verify credentials
    void parseCredentials(const QString &userName,const QString &password);

    // GameManager - alter remote state
    void appendNewRound();
    void submitPoint(const QUuid &userId,const quint32 &point);


    // Reqest models from remote
    void tournaments();
    void tournament(const QUuid &tournament);

    void round(const QUuid &tournament);
    void rounds(const QUuid &tournament);

    // Alter remote state
    void parseTournament(const QString &name,
                                  const QString &startDate,
                                  const QString &endDate);

    void removeTournament(const QUuid &tournament);

    // Recieve models from remote processed
    void sendModel(const QTreeWidgetItem* model,const QStringList &headers,const QString &log);
    void sendModels(const QList<QTreeWidgetItem*> models,const QStringList &headers,const QString &log);

    // Notify external callers
    void externalPopupMessage(const QString &title,const QString &msg);
    void externalNotifyResponse(const bool &status, const QString &msg = QString(),const QTreeWidgetItem* model = nullptr);
    void externalGameResponse(const QString &msg);
};

#endif // IDARTSIMULATOR_H
