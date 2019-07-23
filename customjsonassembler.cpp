#include "customjsonassembler.h"

CustomJsonAssembler::CustomJsonAssembler()
{

}

QJsonObject CustomJsonAssembler::assembleJson(ModelEntity &entity)
{
    ModelEntity* model = &entity;
    initializer_list<_pair> list = {_pair("Id",model->_id.toString()),
                _pair("Parent id",model->_parentId.toString()),
                _pair("Model type",model->_type),
                _pair("Date created",model->dateCreated().toString(dateFormat))};

    QJsonObject object(list);

    if(model->type() == ModelEntity::SeasonModel)
        assembleSeasonJson(dynamic_cast<SeasonEntity*>(model),object);
    else if(model->type() == ModelEntity::TournamentModel)
        assembleTournamentJson(dynamic_cast<TournamentEntity*>(model),object);
    else if(model->type() == ModelEntity::RoundModel)
        assembleRoundJson(dynamic_cast<RoundEntity*>(model),object);
    else if(model->type() == ModelEntity::PointModel)
        assemblePointJson(dynamic_cast<PointEntity*>(model),object);
    else
        throw invalid_argument("Illegal type");

    /*
     * Setup child JSON array
     */

    QJsonArray arr;
    QList<QUuid> subIdentities = model->allIdentifiers();

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

void CustomJsonAssembler::assembleSeasonJson(SeasonEntity* const entity, QJsonObject &obj)
{
    obj["Name"] = entity->name();
    obj["DateFinished"] = entity->dateFinished().toString(dateFormat);
}

void CustomJsonAssembler::assembleTournamentJson(TournamentEntity * const entity, QJsonObject &obj)
{
    obj["Name"] = entity->name();
    obj[TournamentMaxRoundsKey] = entity->numberOfRounds();
    obj[TournamentMaxUsersKey] = entity->maxUsersAllowed();
    obj[DateFinishedKey] = entity->dateFinished().toString(dateFormat);
}

void CustomJsonAssembler::assembleRoundJson(RoundEntity * const entity, QJsonObject &obj)
{
    obj["Round number"] = entity->roundNumber();
}

void CustomJsonAssembler::assemblePointJson(PointEntity * const entity, QJsonObject &obj)
{
    obj["Point Value"] = entity->point();
    obj["User id"] = entity->userId().toString();
}

QList<QUuid> CustomJsonAssembler::extractArray(const QJsonArray &arr)
{
    QList<QUuid> allIdentitites;
    for (QJsonValue val : arr)
        allIdentitites << val.toVariant().toUuid();

    return allIdentitites;
}

template<typename T>
T CustomJsonAssembler::assembleEntityFromJson(const QJsonObject &json)
{
    /*
     * TODO: Lookup the necessary 'key/value' property pairs needed for the specific model
     */

    QUuid modelId = json.value("Id").toVariant().toUuid();
    QUuid parentModelId = json.value("Parent id").toVariant().toUuid();
    int modelTypeValue = json.value("Model type").toVariant().toInt();
    mType entityType = static_cast<mType>(modelTypeValue);
    QDateTime modelCreated = QDateTime::fromString(json.value("Date created").
                                                   toVariant().toString(),dateFormat);
    // TODO: Implement code defined by modeltype
    if(entityType == mType::SeasonModel)
    {
        SeasonEntity* sEntity = new SeasonEntity(modelId);
        sEntity->setParentId(parentModelId);
        sEntity->setDateCreated(modelCreated);
        QString entityName = json.value("Name").toString("Something went wrong");
        sEntity->setName(entityName);
        QString dateFinished = json.value(DateFinishedKey).toVariant().toString();
        sEntity->setDateFinished(QDateTime::fromString(dateFinished,dateFormat));

        if(json.value("Identities").isArray())
        {
            QJsonArray arr = json.value("Identities").toArray();
            sEntity->addTournamentIdentities(extractArray(arr));
        }

        return sEntity;
    }
    else if(entityType == mType::TournamentModel)
    {
        TournamentEntity* tEntity = new TournamentEntity(modelId);
        tEntity->setDateCreated(modelCreated);
        QString entityName = json.value("Name").toString("Something went wrong");
        tEntity->setName(entityName);
        int maxRounds = json.value(TournamentMaxRoundsKey).toVariant().toInt();
        tEntity->setNumberOfRounds(maxRounds);
        int maxUsers = json.value(TournamentMaxUsersKey).toInt();
        tEntity->setMaxUsersAllowed(maxUsers);
        QString dateFinished = json.value(DateFinishedKey).toVariant().toString();
        tEntity->setDateFinished(QDateTime::fromString(dateFinished,dateFormat));

        if(json.value("Identities").isArray())
        {
            QJsonArray arr = json.value("Identities").toArray();
            tEntity->addRoundIdentities(extractArray(arr));
        }

        return tEntity;
    }
}
