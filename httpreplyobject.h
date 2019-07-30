#ifndef HTTPOBJECTREPLY_H
#define HTTPOBJECTREPLY_H

#include <QJsonDocument>
#include <qjsonobject.h>
#include <qjsonarray.h>


class HTTPReplyObject
{
public:
    HTTPReplyObject();
    HTTPReplyObject(const QByteArray &data);

    enum action{Create_Tournament,
                Get_Tournaments,
                Get_Tournaement,
                Append_Round,
                Get_Rounds,
                Get_Round,
                Delete_Round,
                Append_Point,
                Get_Point,
                Get_Points,
                Delete_Point};

    enum objectType {Object,Array};

    objectType getObjectType() const;

    QJsonObject getObject() const;
    QJsonArray getArray() const;

    QByteArray getRawData() const;

private:
    QJsonDocument _jSONDocument;
    QByteArray _data;
};

#endif // HTTPOBJECTREPLY_H
