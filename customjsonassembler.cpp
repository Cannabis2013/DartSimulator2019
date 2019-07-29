#include "customjsonassembler.h"

CustomJsonAssembler::CustomJsonAssembler()
{
}

QJsonObject CustomJsonAssembler::assembleJson(Model &entity)
{
    // TODO: Implement Json functionality
}

void CustomJsonAssembler::assembleSeasonJson(Season* const entity, QJsonObject &obj)
{
    obj["Name"] = QJsonValue(entity->name());
    obj["DateFinished"] = entity->dateFinished().toString(dateFormat);
}

void CustomJsonAssembler::assembleTournamentJson(Tournament * const entity, QJsonObject &obj)
{
    obj["Name"] = QJsonValue(entity->name());
    obj["Number of rounds"] = QJsonValue(entity->numberOfRounds());
    obj["Max users allowed"] = QJsonValue(entity->maxUsersAllowed());
}
