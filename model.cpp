#include "model.h"

Model::Model(ModelType type,QUuid id):
    _dateCreated(QDateTime::currentDateTime()),
    _type(type)
{
    if(id == QUuid())
        _id = QUuid::createUuid();
    else
        _id = id;
}

Model::~Model()
{

}

QUuid Model::id() const
{
    return _id;
}

QDateTime Model::dateCreated() const
{
    return _dateCreated;
}

Model::ModelType Model::type() const
{
    return _type;
}

void Model::setParentId(const QUuid &parentId)
{
    _parentId = parentId;
}

void Model::setId(const QUuid &id)
{
    _id = id;
}

QUuid Model::parentId() const
{
    return _parentId;
}

const QList<QUuid> *Model::allIdentifiers() const
{
    return &_subModels;
}


void Model::appendIdentifier(const QUuid id)
{
    _subModels << id;
}

void Model::appendIdentifiers(const QList<QUuid> identities)
{
    _subModels.append(identities);
}

void Model::removeIdentifier(const QUuid &id)
{
    _subModels.removeOne(id);
}

bool Model::operator ==(Model *comp)
{
    return comp->id() == this->id();
}

void Model::setDateCreated(const QDateTime &dateCreated)
{
    _dateCreated = dateCreated;
}
