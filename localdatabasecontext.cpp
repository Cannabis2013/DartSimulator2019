#include "localdatabasecontext.h"

LocalDatabaseContext::LocalDatabaseContext()
{

}

LocalDatabaseContext::~LocalDatabaseContext()
{

}

void LocalDatabaseContext::tournamentFromJson(const QByteArray &data, const QString &log)
{
    auto container = processDataItem(data);
    emit parseTournamentToExternal(container.model,container.header,log);
}

void LocalDatabaseContext::tournamentsFromJson(const QByteArray &data, const QString &log)
{
    auto container = processDataItems(data);
    emit parseTournamentsToExternal(container.models,container.header,log);
}

void LocalDatabaseContext::roundFromJson(const QByteArray &data, const QString &log)
{
    auto container = processDataItem(data);
    emit parseRoundToExternal(container.model,container.header,log);
}

void LocalDatabaseContext::roundsFromJson(const QByteArray &data, const QString &log)
{
    auto container = processDataItem(data);
    emit parseRoundsToExternal(container.models,container.header,log);
}

void LocalDatabaseContext::usersFromJson(const QByteArray &data, const QString &log)
{
    // TODO:
}

void LocalDatabaseContext::tournamentToJson(QTreeWidgetItem *model)
{

}

QList<QTreeWidgetItem *> LocalDatabaseContext::extractChildren(const QJsonArray &json)
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

ModelContainer LocalDatabaseContext::processDataItem(const QByteArray &item)
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

ModelContainer LocalDatabaseContext::processDataItems(const QByteArray &array)
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
        ModelContainer mContainer = processDataItem(QJsonDocument(val.toObject()).toJson());
        if(header.isEmpty())
            header = mContainer.header;
        result << mContainer.model;
    }
    ModelContainer resultingContainer;
    resultingContainer.models = result;
    resultingContainer.header = header;
    return resultingContainer;
}

void LocalDatabaseContext::createTournament(const QString &name, const int &maxRounds, const int &maxUsers, const QList<QUuid> &users)
{
    QJsonObject obj;
    obj["Id"] = QUuid::createUuid().toString(QUuid::WithoutBraces);
    obj["Name"] = name;
    obj["Maximum allowed rounds"] = maxRounds;
    obj["Maximum allowed users"] = maxRounds;
    obj["Users assigned"] = QJsonArray();

    emit parseTournamentToRemote(QJsonDocument(obj).toJson());
}

QUuid LocalDatabaseContext::currentTournament() const
{
    return _currentTournament;
}

void LocalDatabaseContext::setCurrentTournament(const QUuid &currentTournament)
{
    _currentTournament = currentTournament;
}

const QByteArray LocalDatabaseContext::deProcessDataItem(const QTreeWidgetItem *&parameter1)
{

}

const QByteArray LocalDatabaseContext::deProcessDataItems(const QTreeWidgetItem *&parameter1)
{
}
