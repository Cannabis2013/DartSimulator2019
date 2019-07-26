#ifndef CUSTOMJSONASSEMBLER_H
#define CUSTOMJSONASSEMBLER_H

#include <allmodels.h>
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
#define RoundNumberKey "Round number"
#define PointValueKey "Point Value"
#define PointUserIdKey "User id"

class CustomJsonAssembler
{
public:
    CustomJsonAssembler();

    static QJsonObject assembleJson(Model &entity);

    static QString JsonToString(const QJsonObject &object);

    template<typename T>
    static T assembleModelFromJson(const QJsonObject &json);

private:

    /*
     * Assemble Json from objects
     */

    static void assembleSeasonJson(SeasonModel * const entity, QJsonObject &obj);
    static void assembleTournamentJson(TournamentModel * const entity, QJsonObject &obj);
    static void assembleRoundJson(RoundModel *const entity,QJsonObject &obj);
    static void assemblePointJson(PointModel *const entity,QJsonObject &obj);

    /*
     * Assemble objects from Json
     */
    static SeasonModel* assembleSeasonModel(const QJsonObject &json);
    static TournamentModel* assembleTournamentModel(const QJsonObject &json);
    static RoundModel* assembleRoundModel(const QJsonObject &json);
    static PointModel* assemblePointModel(const QJsonObject &json);
    /*
     * Helper methods
     */

    static QList<QUuid> extractArray(const QJsonArray &arr);
};

#endif // CUSTOMJSONASSEMBLER_H
