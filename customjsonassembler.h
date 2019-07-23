#ifndef CUSTOMJSONASSEMBLER_H
#define CUSTOMJSONASSEMBLER_H

#include <AllEntities.h>
#include <QList>
#include <QPair>
#include <QJsonObject>
#include <qjsondocument.h>
#include <QJsonArray>

typedef QPair<QString,QJsonValue> _pair;

#define dateFormat "dd.MM.yyyy"

class CustomJsonAssembler
{
public:
    CustomJsonAssembler();

    static QJsonObject assembleJson(ModelEntity &entity);

    static QString JsonToString(const QJsonObject &object);

    template<typename T>
    static T assembleEntityFromJson(const QByteArray);

private:

    /*
     * Assemble Json from objects
     */

    static void assembleSeasonJson(SeasonEntity * const entity, QJsonObject &obj);
    static void assembleTournamentJson(TournamentEntity * const entity, QJsonObject &obj);
    static void assembleRoundJson(RoundEntity *const entity,QJsonObject &obj);
    static void assemblePointJson(PointEntity *const entity,QJsonObject &obj);

    /*
     * Assemble objects from Json
     */
};

#endif // CUSTOMJSONASSEMBLER_H
