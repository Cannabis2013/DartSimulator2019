#ifndef LOCALDATABASECONTEXT_H
#define LOCALDATABASECONTEXT_H

#include <ijsonconverter.h>
#include <QTreeWidgetItem>
#include <QJsonDocument>
#include <QJsonObject>
#include <qjsonarray.h>

struct ModelContainer
{
    QTreeWidgetItem* model = nullptr;
    QList<QTreeWidgetItem*> models;
    QStringList header;
};

enum ModelType{Tournament,Round,Point};

class LocalDatabaseContext : public QObject,
        public IJsonConverter<ModelContainer,const QByteArray,const QTreeWidgetItem*>
{
    Q_OBJECT
public:
    LocalDatabaseContext();

    virtual ~LocalDatabaseContext();

    void createTournament(const QString &name,
                          const int &maxRounds,
                          const int &maxUsers,
                          const QList<QUuid> &users);

public slots:

    // Convert models from remote to QTreeWidgetItem*
    void tournamentFromJson(const QByteArray &data, const QString &log);
    void tournamentsFromJson(const QByteArray &data, const QString &log);
    void roundFromJson(const QByteArray &data, const QString &log);
    void roundsFromJson(const QByteArray &data, const QString &log);

    void usersFromJson(const QByteArray &data, const QString &log);

    // Convert models from local to Json format
    void tournamentToJson(QTreeWidgetItem* model);
signals:

    void parseTournamentToExternal(const QTreeWidgetItem* model,const QStringList &headers,const QString &log);
    void parseTournamentsToExternal(const QList<QTreeWidgetItem*> models,const QStringList &headers,const QString &log);
    void parseRoundToExternal(QTreeWidgetItem* model,const QStringList &header,const QString &log);
    void parseRoundsToExternal(QList<QTreeWidgetItem*> models,const QStringList &header,const QString &log);

    void parseTournamentToRemote(const QByteArray &json);
    void parseRoundToRemote(const QByteArray &json,const QUuid &tournament);
    void parsePointToRemote(const QUuid &round,const QByteArray &json);

private:

    QList<QTreeWidgetItem*> extractChildren(const QJsonArray &json);

    QList<QUuid> restusers() const;
    void appendRound();

    ModelContainer processDataItem(const QByteArray &item);
    ModelContainer processDataItems(const QByteArray &array);

    const QByteArray deProcessDataItem(const QTreeWidgetItem* &parameter1);
    const QByteArray deProcessDataItems(const QTreeWidgetItem* &parameter1);




};

#endif // LOCALDATABASECONTEXT_H
