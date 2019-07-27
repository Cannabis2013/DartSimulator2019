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

Model *Model::parent() const
{
    return _parent;
}

void Model::addChild(Model *child)
{
    _children << child;
    child->setParent(this);
}

void Model::replaceChild(const int &index,Model *child)
{
    _children.replace(index,child);
}

QList<Model *> Model::children() const
{
    return _children;
}

int Model::numberOfChilds() const
{
    return _children.count();
}

void Model::removeChild(Model *child)
{
    _children.removeOne(child);
}

bool Model::isRoot() const
{
    return parent() == nullptr;
}


void Model::setParent(Model *parent)
{
    _parent = parent;
}

const QList<const Model *> *Model::childs() const
{
    QList<const Model*> *result = new QList<const Model*>;

    for (const Model* child : children())
        *result << child;

    return result;
}
