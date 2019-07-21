#ifndef CUSTOMJSONASSEMBLER_H
#define CUSTOMJSONASSEMBLER_H

#include <seasonentity.h>
#include <tournamententity.h>
#include <roundentity.h>
#include <pointentity.h>
#include <QList>
#include <QPair>
#include <QJsonObject>
#include <QJsonArray>

typedef QPair<QString,QJsonValue> _pair;

#define dateFormat "dd.MM.yyyy"

class CustomJsonAssembler
{
public:
    CustomJsonAssembler();

    static QJsonObject assembleJson(ModelEntity &entity);

private:

    static void assembleSeasonJson(SeasonEntity * const entity, QJsonObject &obj);
    static void assembleTournamentJson(TournamentEntity * const entity, QJsonObject &obj);
    static void assembleRoundJson(RoundEntity *const entity,QJsonObject &obj);
    static void assemblePointJson(PointEntity *const entity,QJsonObject &obj);
};

#endif // CUSTOMJSONASSEMBLER_H
