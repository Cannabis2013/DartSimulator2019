#include "localdatabasecontext.h"

LocalDatabaseContext::LocalDatabaseContext()
{

}

LocalDatabaseContext::~LocalDatabaseContext()
{

}

void LocalDatabaseContext::processTournament(const QByteArray &data, const QString &log)
{
    auto model = createModel(data,Tournament);
    emit parseTournamentToExternal(model,log);
}

void LocalDatabaseContext::processTournaments(const QByteArray &data, const QString &log)
{
    auto models = createModels(data,Tournament);
    emit parseTournamentsToExternal(models,log);
}

void LocalDatabaseContext::processRound(const QByteArray &data, const QString &log)
{
    auto model = createModel(data,Round);
    emit parseRoundToExternal(model,log);
}

void LocalDatabaseContext::processRounds(const QByteArray &data, const QString &log)
{
    auto models = createModels(data,Round);
    emit parseRoundsToExternal(models,log);
}

void LocalDatabaseContext::processUsers(const QByteArray &data, const QString &log)
{
    // TODO:
}

bool LocalDatabaseContext::allSubmittet()
{
    return _remainingSubmitters.isEmpty();
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
    if(doc.isObject() || !doc.isArray() || doc.isNull())
        throw err.errorString().toStdString();
    QJsonArray objects = doc.array();
    for (auto val : objects)
    {
        QJsonObject obj = val.toObject();
        QStringList data;
        if(type == ModelType::Tournament)
        {
            data << obj.value("Name").toString() <<
                    obj.value("StartDateTime").toString() <<
                    obj.value("EndDateTime").toString() <<
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

QList<QUuid> LocalDatabaseContext::restusers() const
{
    return _remainingSubmitters;
}

bool LocalDatabaseContext::hasSubmitted(const QUuid &user)
{
    return !_remainingSubmitters.contains(user);
}

QUuid LocalDatabaseContext::currentRound() const
{
    return _currentRound;
}

void LocalDatabaseContext::setCurrentRound(const QUuid &currentRound)
{
    _currentRound = currentRound;
}

void LocalDatabaseContext::appendRound()
{
    int roundNumber = _rounds.count();
    QJsonObject obj;
    obj["Id"] = QUuid::createUuid().toString(QUuid::WithoutBraces);
    obj["Round number"] = roundNumber;
    obj["Parent tournament:"] = currentRound().toString(QUuid::WithoutBraces);
    obj["Point identities"] = QJsonArray();

    emit parseRoundToRemote(QJsonDocument(obj).toJson(),currentTournament());
    _remainingSubmitters = _currentAssignedUsers;
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

void LocalDatabaseContext::submitPoint(const QUuid &user, const int &point)
{
    if(hasSubmitted(user))
        throw "User has already submittet point";

    QJsonObject obj;
    obj["User"] = user.toString(QUuid::WithoutBraces);
    obj["Point"] = point;

    emit parsePointToRemote(currentRound(),QJsonDocument(obj).toJson());

    _remainingSubmitters.append(user);
}

void LocalDatabaseContext::nextRound()
{
    if(allSubmittet())
        appendRound();
    else
        throw "All users needs to submit";
}

QUuid LocalDatabaseContext::currentTournament() const
{
    return _currentTournament;
}

void LocalDatabaseContext::setCurrentTournament(const QUuid &currentTournament)
{
    _currentTournament = currentTournament;
}
