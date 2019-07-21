#include "customjsonassembler.h"

CustomJsonAssembler::CustomJsonAssembler()
{
}

QJsonObject CustomJsonAssembler::assembleJson(ModelEntity &entity)
{
    ModelEntity* model = &entity;
    initializer_list<_pair> list = {_pair("id",model->_id.toString()),
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

    QJsonArray arr;
    QList<QUuid> subIdentities = model->allIdentifiers();

    for (int i = 0; i < subIdentities.count(); ++i)
        arr[i] = QJsonValue(subIdentities.at(i).toString());

    delete model;
    return object;
}

void CustomJsonAssembler::assembleSeasonJson(SeasonEntity* const entity, QJsonObject &obj)
{
    obj["Name"] = entity->name();
    obj["DateFinished"] = entity->dateFinished().toString(dateFormat);
}

void CustomJsonAssembler::assembleTournamentJson(TournamentEntity * const entity, QJsonObject &obj)
{
    obj["Name"] = entity->name();
    obj["Number of rounds"] = entity->numberOfRounds();
    obj["Max users allowed"] = entity->maxUsersAllowed();
    obj["Date finished"] = entity->dateFinished().toString(dateFormat);
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
