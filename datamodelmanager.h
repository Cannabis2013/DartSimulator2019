#ifndef LOCALDATABASECONTEXT_H
#define LOCALDATABASECONTEXT_H

#include <ijsonconverter.h>
#include <QTreeWidgetItem>
#include <QJsonDocument>
#include <QJsonObject>
#include <qjsonarray.h>
#include <qdatetime.h>

#define REMOTEDATEFORMAT "yyyy-MM-dd'T'hh:mm:ss.zzz'Z'"

struct ModelContainer
{
    QTreeWidgetItem* model = nullptr;
    QList<QTreeWidgetItem*> models;
    QStringList header;
};

enum ModelType{Tournament,Round,Point};

class DataModelManager : public QObject,
        public IJsonConverter<ModelContainer,const QByteArray>
{
    Q_OBJECT
public:
    DataModelManager();
    virtual ~DataModelManager();

public slots:
    void createTournament(const QString &name,
                          const QString &startDate,
                          const QString &endDate);

    // Convert models from remote to QTreeWidgetItem*
    void tournamentFromJson(const QByteArray &data, const QString &log);
    void tournamentsFromJson(const QByteArray &data, const QString &log);
    void roundFromJson(const QByteArray &data, const QString &log);
    void roundsFromJson(const QByteArray &data, const QString &log);

    void usersFromJson(const QByteArray &data, const QString &log);

    // Convert models from local to Json format
    void tournamentToJson(QTreeWidgetItem* model);

    void remoteAppendRound(const QUuid &tournament, const QUuid &round, const int &roundNumber);
    void remoteAppendPoint(const QUuid &round, const QUuid &userId, const quint32 &point);

    // Convert replies/updates from remote

    void ConvertreplyFromRemote(const bool &status = true,const QByteArray &data = QByteArray());

signals:
    void parseTournamentToExternal(const QTreeWidgetItem* model,const QStringList &headers,const QString &log);
    void parseTournamentsToExternal(const QList<QTreeWidgetItem*> models,const QStringList &headers,const QString &log);
    void parseRoundToExternal(QTreeWidgetItem* model,const QStringList &header,const QString &log);
    void parseRoundsToExternal(QList<QTreeWidgetItem*> models,const QStringList &header,const QString &log);

    void parseTournamentToRemote(const QByteArray &json);
    void parseRoundToRemote(const QByteArray &json,const QUuid &tournament);
    void parsePointToRemote(const QByteArray &json,const QUuid &round);

    void parseReplyFromRemote(const bool &status,const QTreeWidgetItem* model = nullptr);

private:
    QList<QTreeWidgetItem*> extractChildren(const QJsonArray &json);

    ModelContainer ConvertDataItem(const QByteArray &item);
    ModelContainer ConvertDataItems(const QByteArray &array);
};

#endif // LOCALDATABASECONTEXT_H
