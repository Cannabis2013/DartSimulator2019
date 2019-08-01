#ifndef LOCALDATABASECONTEXT_H
#define LOCALDATABASECONTEXT_H

#include <ijsonconverter.h>
#include <QTreeWidgetItem>
#include <QJsonDocument>
#include <QJsonObject>
#include <qjsonarray.h>


enum ModelType{Tournament,Round,Point};

class LocalDatabaseContext : public QObject,
        public IJsonConverter<QTreeWidgetItem*,QByteArray,ModelType>
{
    Q_OBJECT
public:
    LocalDatabaseContext();

    virtual ~LocalDatabaseContext();

    QUuid currentTournament() const;
    void setCurrentTournament(const QUuid &currentTournament);

    QUuid currentRound() const;
    void setCurrentRound(const QUuid &currentRound);

    void createTournament(const QString &name,
                          const int &maxRounds,
                          const int &maxUsers,
                          const QList<QUuid> &users);
    void submitPoint(const QUuid &user,const int &point);
public slots:
    void processTournament(const QByteArray &data, const QString &log);
    void processTournaments(const QByteArray &data, const QString &log);
    void processRound(const QByteArray &data, const QString &log);
    void processRounds(const QByteArray &data, const QString &log);
signals:

    void parseTournamentToExternal(QTreeWidgetItem* model,const QString &log);
    void parseTournamentsToExternal(QList<QTreeWidgetItem*> models,const QString &log);
    void parseRoundToExternal(QTreeWidgetItem* model,const QString &log);
    void parseRoundsToExternal(QList<QTreeWidgetItem*> models,const QString &log);

    void parseTournamentToRemote(const QByteArray &json);
    void parseRoundToRemote(const QByteArray &json,const QUuid &tournament);
    void parsePointToRemote(const QUuid &round,const QByteArray &json);

private:

    void appendRound();

    QTreeWidgetItem* createModel(const QByteArray &item, const ModelType &type) const;
    QList<QTreeWidgetItem*> createModels(const QByteArray &array, const ModelType &type) const;

    QUuid _currentTournament;
    QUuid _currentRound;
    QList<QUuid> _currentAssignedUsers;
    QList<QUuid> _rounds;
};

#endif // LOCALDATABASECONTEXT_H
