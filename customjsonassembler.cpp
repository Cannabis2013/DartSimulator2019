#include "customjsonassembler.h"

CustomJsonAssembler::CustomJsonAssembler()
{
}

QJsonObject CustomJsonAssembler::assembleJson(Model &entity)
{
    Model* model = &entity;
    initializer_list<_pair> list = {_pair("Id",model->id().toString()),
                _pair("Parent id",model->parentId().toString()),
                _pair("Model type",model->type()),
                _pair("Date created",model->dateCreated().toString(dateFormat))};

    QJsonObject object(list);

    if(model->type() == Model::SeasonModel)
        assembleSeasonJson(dynamic_cast<SeasonModel*>(model),object);
    else if(model->type() == Model::TournamentModel)
        assembleTournamentJson(dynamic_cast<TournamentModel*>(model),object);
    else if(model->type() == Model::RoundModel)
        assembleRoundJson(dynamic_cast<RoundModel*>(model),object);
    else if(model->type() == Model::PointModel)
        assemblePointJson(dynamic_cast<PointModel*>(model),object);
    else
        throw invalid_argument("Illegal type");

    /*
     * Setup child JSON array
     */

    QJsonArray arr;
    QList<QUuid> subIdentities = *model->allIdentifiers();

    for (int i = 0; i < subIdentities.count(); ++i)
        arr[i] = QJsonValue(subIdentities.at(i).toString());

    object["Identities"] = arr;
    model = nullptr;
    return object;
}

QString CustomJsonAssembler::JsonToString(const QJsonObject &object)
{
    return QString::fromStdString(QJsonDocument(object).toJson().toStdString());
}

void CustomJsonAssembler::assembleSeasonJson(SeasonModel* const entity, QJsonObject &obj)
{
    obj["Name"] = entity->name();
    obj["DateFinished"] = entity->dateFinished().toString(dateFormat);
}

void CustomJsonAssembler::assembleTournamentJson(TournamentModel * const entity, QJsonObject &obj)
{
    obj["Name"] = entity->name();
    obj[TournamentMaxRoundsKey] = entity->numberOfRounds();
    obj[TournamentMaxUsersKey] = entity->maxUsersAllowed();
    obj[DateFinishedKey] = entity->dateFinished().toString(dateFormat);
}

void CustomJsonAssembler::assembleRoundJson(RoundModel * const entity, QJsonObject &obj)
{
    obj[RoundNumberKey] = entity->roundNumber();
}

void CustomJsonAssembler::assemblePointJson(PointModel * const entity, QJsonObject &obj)
{
    obj[PointValueKey] = entity->point();
    obj[PointUserIdKey] = entity->userId().toString();
}

SeasonModel *CustomJsonAssembler::assembleSeasonModel(const QJsonObject &json)
{
    QUuid modelId = json.value("Id").toVariant().toUuid();
    QUuid parentModelId = json.value("Parent id").toVariant().toUuid();
    QDateTime modelCreated = QDateTime::fromString(json.value("Date created").
                                                   toVariant().toString(),dateFormat);


    SeasonModel* sEntity = new SeasonModel(modelId);
    sEntity->setParentId(parentModelId);
    sEntity->setDateCreated(modelCreated);
    QString entityName = json.value("Name").toString("Something went wrong");
    sEntity->setName(entityName);
    QString dateFinished = json.value(DateFinishedKey).toVariant().toString();
    sEntity->setDateFinished(QDateTime::fromString(dateFinished,dateFormat));

    if(json.value("Identities").isArray())
    {
        QJsonArray arr = json.value("Identities").toArray();
        sEntity->appendIdentifiers(extractArray(arr));
    }

    return sEntity;
}

TournamentModel *CustomJsonAssembler::assembleTournamentModel(const QJsonObject &json)
{
    QUuid modelId = json.value("Id").toVariant().toUuid();
    QUuid parentModelId = json.value("Parent id").toVariant().toUuid();
    QDateTime modelCreated = QDateTime::fromString(json.value("Date created").
                                                   toVariant().toString(),dateFormat);

    TournamentModel* tournament = new TournamentModel(modelId);
    tournament->setParentId(parentModelId);
    tournament->setDateCreated(modelCreated);
    QString entityName = json.value("Name").toString("Something went wrong");
    tournament->setName(entityName);
    int maxRounds = json.value(TournamentMaxRoundsKey).toVariant().toInt();
    tournament->setNumberOfRounds(maxRounds);
    int maxUsers = json.value(TournamentMaxUsersKey).toInt();
    tournament->setMaxUsersAllowed(maxUsers);
    QString dateFinished = json.value(DateFinishedKey).toVariant().toString();
    tournament->setDateFinished(QDateTime::fromString(dateFinished,dateFormat));

    if(json.value("Identities").isArray())
    {
        QJsonArray arr = json.value("Identities").toArray();
        tournament->appendIdentifiers(extractArray(arr));
    }

    return tournament;
}

RoundModel *CustomJsonAssembler::assembleRoundModel(const QJsonObject &json)
{
    QUuid modelId = json.value("Id").toVariant().toUuid();
    QUuid parentModelId = json.value("Parent id").toVariant().toUuid();
    QDateTime modelCreated = QDateTime::fromString(json.value("Date created").
                                                   toVariant().toString(),dateFormat);
    int roundNumber = json.value(RoundNumberKey).toInt();
    RoundModel* round = new RoundModel(roundNumber,modelId);
    round->setParentId(parentModelId);

    if(json.value("Identities").isArray())
    {
        QJsonArray arr = json.value("Identities").toArray();
        round->appendIdentifiers(extractArray(arr));
    }

    return round;
}

PointModel *CustomJsonAssembler::assemblePointModel(const QJsonObject &json)
{
    QUuid modelId = json.value("Id").toVariant().toUuid();
    QUuid parentModelId = json.value("Parent id").toVariant().toUuid();
    QDateTime modelCreated = QDateTime::fromString(json.value("Date created").
                                                   toVariant().toString(),dateFormat);
    QUuid pointUserId = json.value(PointUserIdKey).toVariant().toUuid();
    int pointValue = json.value(PointValueKey).toInt();
    PointModel* point = new PointModel(pointUserId,modelId);
    point->setParentId(parentModelId);
    point->setPoint(pointValue);

    return point;
}

QList<QUuid> CustomJsonAssembler::extractArray(const QJsonArray &arr)
{
    QList<QUuid> allIdentitites;
    for (QJsonValue val : arr)
        allIdentitites << val.toVariant().toUuid();

    return allIdentitites;
}

template<typename T>
T CustomJsonAssembler::assembleModelFromJson(const QJsonObject &json)
{
    int modelTypeValue = json.value("Model type").toInt();
    mType entityType = static_cast<mType>(modelTypeValue);
    QDateTime modelCreated = QDateTime::fromString(json.value("Date created").
                                                   toVariant().toString(),dateFormat);

    if(entityType == mType::SeasonModel)
        return assembleSeasonModel(json);
    else if(entityType == mType::TournamentModel)
        return assembleTournamentModel(json);
    else if(entityType == mType::RoundModel)
        return assembleRoundModel(json);
    else if(entityType == mType::PointModel)
        return assemblePointModel(json);
    else
        throw invalid_argument("Invalid Json parsed");
}
