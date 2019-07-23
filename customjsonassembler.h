#ifndef CUSTOMJSONASSEMBLER_H
#define CUSTOMJSONASSEMBLER_H

#include <AllEntities.h>
#include <QList>
#include <QPair>
#include <QJsonObject>
#include <qjsondocument.h>
#include <QJsonArray>

/*
 * The structure and list of 'key|value' property pairs for the basic'ModelEntity' class
 *  - 'Id' : QUuid
 *  - 'Parent id' : QUuid
 *  - 'Model type' : enum
 *  - 'Date created' : QString/{string value}
 *  - 'Identities' : QJsonValue[]
 */

typedef QPair<QString,QJsonValue> _pair;

#define dateFormat "dd.MM.yyyy"
#define TournamentMaxRoundsKey "Number of rounds"
#define TournamentMaxUsersKey "Max users allowed"
#define DateFinishedKey "Date finished"
class CustomJsonAssembler
{
public:
    CustomJsonAssembler();

    static QJsonObject assembleJson(ModelEntity &entity);

    static QString JsonToString(const QJsonObject &object);

    template<typename T>
    static T assembleEntityFromJson(const QJsonObject &json);

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

    /*
     * Helper methods
     */

    static QList<QUuid> extractArray(const QJsonArray &arr);
};

#endif // CUSTOMJSONASSEMBLER_H
