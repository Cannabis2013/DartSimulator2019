#include "localdatabasecontext.h"

LocalDatabaseContext::LocalDatabaseContext()
{

}

LocalDatabaseContext::~LocalDatabaseContext()
{

}

void LocalDatabaseContext::createTournament(const QByteArray &data)
{
    auto model = createModel(data,Tournament);
    emit sendTournament(model);
}

void LocalDatabaseContext::createTournaments(const QByteArray &data)
{
    auto models = createModels(data,Tournament);
    emit sendTournaments(models);
}

void LocalDatabaseContext::createRound(const QByteArray &data)
{
    auto model = createModel(data,Round);
    emit sendRound(model);
}

void LocalDatabaseContext::createRounds(const QByteArray &data)
{
    auto models = createModels(data,Round);
    emit sendRounds(models);
}

void LocalDatabaseContext::createPoint(const QByteArray &data)
{
    auto model = createModel(data,Point);
    emit sendPoint(model);
}

void LocalDatabaseContext::createPoints(const QByteArray &data)
{
    auto models = createModels(data,Point);
    emit sendPoints(models);
}


QTreeWidgetItem *LocalDatabaseContext::createModel(const QByteArray &item, const ModelType &type) const
{
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(item,&err);
    if(doc.isObject() || doc.isArray() || doc.isNull())
        throw err.errorString().toStdString();

    QJsonObject obj =  doc.object();
    QStringList data;
    if(type == ModelType::Tournament)
    {
        data << obj.value("Name").toString() <<
                obj.value("Date created").toString() <<
                obj.value("Date finished").toString() <<
                obj.value("Id").toString();

    }
    else if(type == ModelType::Round)
    {
        data << obj.value("Round number").toString() <<
                obj.value("Tournament").toString() <<
                obj.value("Id").toString();
    }
    else
    {
        data << obj.value("User id").toString() <<
                obj.value("Point").toString("0") <<
                obj.value("Id").toString();
    }

    return new QTreeWidgetItem(data);
}

QList<QTreeWidgetItem *> LocalDatabaseContext::createModels(const QByteArray &array, const ModelType &type) const
{
    auto result = QList<QTreeWidgetItem*>();
    QJsonParseError err;
    auto doc = QJsonDocument::fromJson(array,&err);
    if(doc.isObject() || doc.isArray() || doc.isNull())
        throw err.errorString().toStdString();
    QJsonArray objects = doc.array();
    for (auto val : objects)
    {
        QJsonObject obj = val.toObject();
        QStringList data;
        if(type == ModelType::Tournament)
        {
            data << obj.value("Name").toString() <<
                    obj.value("Date created").toString() <<
                    obj.value("Date finished").toString() <<
                    obj.value("Id").toString();

        }
        else if(type == ModelType::Round)
        {
            data << obj.value("Round number").toString() <<
                    obj.value("Tournament").toString() <<
                    obj.value("Id").toString();
        }
        else
        {
            data << obj.value("User id").toString() <<
                    obj.value("Point").toString("0") <<
                    obj.value("Id").toString();
        }

        result << new QTreeWidgetItem(data);
    }

    return result;
}
