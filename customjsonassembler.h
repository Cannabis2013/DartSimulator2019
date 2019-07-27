#ifndef CUSTOMJSONASSEMBLER_H
#define CUSTOMJSONASSEMBLER_H

#include <season.h>
#include <tournament.h>
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

    static QJsonObject assembleJson(Model &entity);

private:

    static void assembleSeasonJson(Season * const entity, QJsonObject &obj);
    static void assembleTournamentJson(Tournament * const entity, QJsonObject &obj);
};

#endif // CUSTOMJSONASSEMBLER_H
