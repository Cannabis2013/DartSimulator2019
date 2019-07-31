#include "model.h"

Model::Model(ModelType type):
    _id(QUuid::createUuid()),
    _dateCreated(QDateTime::currentDateTime()),
    _type(type)
{
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
