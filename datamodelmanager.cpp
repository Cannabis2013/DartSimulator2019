#include "datamodelmanager.h"

DataModelManager::DataModelManager()
{

}

DataModelManager::~DataModelManager()
{

}

void DataModelManager::tournamentFromJson(const QByteArray &data, const QString &log)
{
    auto container = ConvertDataItem(data);
    emit parseTournamentToExternal(container.model,container.header,log);
}

void DataModelManager::tournamentsFromJson(const QByteArray &data, const QString &log)
{
    auto container = ConvertDataItems(data);
    emit parseTournamentsToExternal(container.models,container.header,log);
}

void DataModelManager::roundFromJson(const QByteArray &data, const QString &log)
{
    auto container = ConvertDataItem(data);
    emit parseRoundToExternal(container.model,container.header,log);
}

void DataModelManager::roundsFromJson(const QByteArray &data, const QString &log)
{
    auto container = ConvertDataItem(data);
    emit parseRoundsToExternal(container.models,container.header,log);
}

void DataModelManager::usersFromJson(const QByteArray &data, const QString &log)
{
    // TODO:
}

void DataModelManager::tournamentToJson(QTreeWidgetItem *model)
{

}

void DataModelManager::remoteAppendRound(const QUuid &tournament, const QUuid &round,const int &roundNumber)
{
    QJsonObject obj;
    obj["Id"] = round.toString(QUuid::WithoutBraces);
    obj["Round number"] = roundNumber;
    obj["Parent tournament:"] = tournament.toString(QUuid::WithoutBraces);
    obj["Point identities"] = QJsonArray();

    emit parseRoundToRemote(QJsonDocument(obj).toJson(),tournament);
}

void DataModelManager::remoteAppendPoint(const QUuid &round, const QUuid &userId, const quint32 &point)
{
    QJsonObject obj;
    obj["id"] = QUuid::createUuid().toString(QUuid::WithoutBraces);
    obj["userId"] = userId.toString(QUuid::WithoutBraces);
    obj["points"] = QJsonValue::fromVariant(point);

    emit parsePointToRemote(QJsonDocument(obj).toJson(),round);
}

QList<QTreeWidgetItem *> DataModelManager::extractChildren(const QJsonArray &json)
{
    auto result = QList<QTreeWidgetItem*>();
    for (auto val : json)
    {
        auto data = QStringList();
        auto children = QList<QTreeWidgetItem*>();

        for (QString key : val.toObject().keys()) {
            QJsonValue jVal = val.toObject().value(key);
            if(!jVal.isArray())
                data << val.toObject().value(key).toString("NULL");
            else
                children = extractChildren(jVal.toArray());
        }
        auto model = new QTreeWidgetItem(data);
        model->addChildren(children);
        result << model;
    }
    return result;
}

ModelContainer DataModelManager::ConvertDataItem(const QByteArray &item)
{
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(item,&err);
    if(!doc.isObject() || doc.isArray() || doc.isNull())
        throw err.errorString().toStdString();

    QJsonObject obj =  doc.object();

    QStringList data, header;

    QList<QTreeWidgetItem*> children;

    for (QString key : obj.keys())
    {
        QJsonValue jVal = obj.value(key);
        if(!jVal.isArray())
        {
            data << jVal.toString("Not defined");
            header << key;
        }
        else
            children = extractChildren(jVal.toArray());
    }
    auto result = new QTreeWidgetItem(data);
    result->addChildren(children);
    ModelContainer mContainer;
    mContainer.model = result;
    mContainer.header = header;
    return mContainer;
}

ModelContainer DataModelManager::ConvertDataItems(const QByteArray &array)
{
    auto result = QList<QTreeWidgetItem*>();
    QJsonParseError err;
    QStringList header;
    auto doc = QJsonDocument::fromJson(array,&err);
    if(doc.isObject() || !doc.isArray() || doc.isNull())
        throw err.errorString().toStdString();
    QJsonArray objects = doc.array();
    for (auto val : objects)
    {
        ModelContainer mContainer = ConvertDataItem(QJsonDocument(val.toObject()).toJson());
        if(header.isEmpty())
            header = mContainer.header;
        result << mContainer.model;
    }
    ModelContainer resultingContainer;
    resultingContainer.models = result;
    resultingContainer.header = header;
    return resultingContainer;
}

void DataModelManager::createTournament(const QString &name, const QString &startDate, const QString &endDate)
{
    QJsonObject obj;
    obj["id"] = QUuid::createUuid().toString(QUuid::WithoutBraces);
    obj["name"] = name;
    obj["startDateTime"] = QDateTime::fromString(startDate).toString("yyyy.MM.dd.hh.mm.ss.zzz");
    obj["endDateTime"] = QDateTime::fromString(endDate).toString("yyyy.MM.dd.hh.mm.ss.zzz");

    emit parseTournamentToRemote(QJsonDocument(obj).toJson());
}

