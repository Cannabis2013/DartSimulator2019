#ifndef LOCALDATABASECONTEXT_H
#define LOCALDATABASECONTEXT_H

#include <imodelizer.h>
#include <QTreeWidgetItem>
#include <QJsonDocument>
#include <QJsonObject>
#include <qjsonarray.h>

enum ModelType{Tournament,Round,Point};

class LocalDatabaseContext : public QObject,
        public IModelizer<QTreeWidgetItem*,QByteArray,ModelType>
{
    Q_OBJECT
public:
    LocalDatabaseContext();

    virtual ~LocalDatabaseContext();

public slots:
    void createTournament(const QByteArray &data);
    void createTournaments(const QByteArray &data);
    void createRound(const QByteArray &data);
    void createRounds(const QByteArray &data);
    void createPoint(const QByteArray &data);
    void createPoints(const QByteArray &data);
signals:

    void sendTournament(QTreeWidgetItem* model);
    void sendTournaments(QList<QTreeWidgetItem*> models);
    void sendRound(QTreeWidgetItem* model);
    void sendRounds(QList<QTreeWidgetItem*> models);
    void sendPoint(QTreeWidgetItem* model);
    void sendPoints(QList<QTreeWidgetItem*> models);

private:

    QTreeWidgetItem* createModel(const QByteArray &item, const ModelType &type) const;
    QList<QTreeWidgetItem*> createModels(const QByteArray &array, const ModelType &type) const;
};

#endif // LOCALDATABASECONTEXT_H
