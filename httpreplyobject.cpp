#include "httpreplyobject.h"

HTTPReplyObject::HTTPReplyObject()
{
}

HTTPReplyObject::HTTPReplyObject(const QByteArray &data)
{
    _data = data;
    _jSONDocument = QJsonDocument::fromBinaryData(data);
}

HTTPReplyObject::objectType HTTPReplyObject::getObjectType() const
{
    if(_jSONDocument.isArray())
        return objectType::Array;
    else
        return objectType::Object;
}

QJsonObject HTTPReplyObject::getObject() const
{
    if(!_jSONDocument.isArray())
        return _jSONDocument.object();
    else
        return QJsonObject();
}

QJsonArray HTTPReplyObject::getArray() const
{
    if(_jSONDocument.isArray())
        return _jSONDocument.array();
    else
        return QJsonArray();
}

QByteArray HTTPReplyObject::getRawData() const
{
    return _data;
}
