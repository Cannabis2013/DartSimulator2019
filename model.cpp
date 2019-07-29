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

void Model::_addChild(Model *child)
{
    _children << child;
    child->setParent(this);
}

void Model::_replaceChild(const int &index,Model *child)
{
    if(index >= _children.count() || index < 0)
        throw out_of_range("Index out of range!");

    _children.replace(index,child);
}

QList<Model *> Model::_childs() const
{
    return _children;
}

int Model::_numberOfChilds() const
{
    return _children.count();
}

void Model::_removeChild(Model *child)
{
    _children.removeOne(child);
}

bool Model::isRoot() const
{
    return parent() == nullptr;
}

bool Model::isLeaf() const
{
    return _children.count() == 0;
}

void Model::setChildren(const QList<Model *> &children)
{
    _children = children;
}

void Model::setParent(Model *parent)
{
    _parent = parent;
}

QList<const Model *> Model::childs() const
{
    QList<const Model*> result;

    for (const Model* child : _childs())
        result << child;

    return result;
}
