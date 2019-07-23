#include "modelentity.h"

ModelEntity::ModelEntity(ModelType type,QUuid id):
    _dateCreated(QDateTime::currentDateTime()),
    _type(type)
{
    if(id == QUuid())
        _id = QUuid::createUuid();
    else
        _id = id;
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

void ModelEntity::setId(const QUuid &id)
{
    _id = id;
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

bool ModelEntity::operator ==(ModelEntity *comp)
{
    return comp->id() == this->id();
}
