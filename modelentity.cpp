#include "modelentity.h"

ModelEntity::ModelEntity(ModelType type):
    _id(QUuid::createUuid()),
    _dateCreated(QDateTime::currentDateTime()),
    _type(type)
{
}

ModelEntity::~ModelEntity()
{

}

QUuid ModelEntity::id() const
{
    return _id;
}

QDateTime ModelEntity::dateCreated() const
{
    return _dateCreated;
}

ModelEntity::ModelType ModelEntity::type()
{
    return _type;
}

void ModelEntity::setParentId(const QUuid &parentId)
{
    _parentId = parentId;
}

QUuid ModelEntity::parentId() const
{
    return _parentId;
}

QList<QUuid> ModelEntity::allIdentifiers() const
{
    return _subEntities;
}


void ModelEntity::appendIdentifier(const QUuid id)
{
    _subEntities << id;
}
