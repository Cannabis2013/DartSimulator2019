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

    if(model->_type == ModelEntity::SeasonModel)
        assembleSeasonJson(dynamic_cast<SeasonEntity*>(model),object);

    QJsonArray arr;
    QList<QUuid> subIdentities = model->allIdentifiers();

    for (int i = 0; i < subIdentities.count(); ++i)
        arr[i] = QJsonValue(subIdentities.at(i).toString());

    delete model;
    return object;
}

void CustomJsonAssembler::assembleSeasonJson(SeasonEntity* const entity, QJsonObject &obj)
{
    obj["Name"] = QJsonValue(entity->name());
    obj["DateFinished"] = entity->dateFinished().toString(dateFormat);
}

void CustomJsonAssembler::assembleTournamentJson(TournamentEntity * const entity, QJsonObject &obj)
{
    obj["Name"] = QJsonValue(entity->name());
    obj["Number of rounds"] = QJsonValue(entity->numberOfRounds());
    obj["Max users allowed"] = QJsonValue(entity->maxUsersAllowed());
    obj["Date finished"] = QJsonValue(entity->dateFinished().toString(dateFormat));
}
