#ifndef CUSTOMJSONASSEMBLER_H
#define CUSTOMJSONASSEMBLER_H

#include <allmodels.h>
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
};

#endif // CUSTOMJSONASSEMBLER_H
