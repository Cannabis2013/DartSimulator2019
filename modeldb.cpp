#include "modeldb.h"

ModelDB::ModelDB()
{

}

const Model *ModelDB::model(const QUuid &id)
{
    for (Model* s : _models) {
        const Model* m = _child(s,id);
        if(m != nullptr)
            return m;
    }

    return nullptr;
}

void ModelDB::addModel(Model *m, const QUuid &parent)
{
    if(parent == QUuid())
        _models.append(m);

    if(_model(parent) == nullptr)
        throw "Parent object doesn't exist!";

    if(_model(parent)->type() == Model::PointModel)
        throw "Adding children to this type of model not allowed!";

    _model(parent)->_addChild(m);
}

void ModelDB::replaceModel(Model *m, const QUuid &id)
{

    Model* replaceable = _model(id);
    if(replaceable == nullptr)
        throw  "No object to replace";
    if(replaceable->parent() != nullptr)
    {
        QList<Model*> children = replaceable->parent()->_childs();
        for (int i = 0; i < children.count(); ++i) {
            if(children.at(i)->id() == id)
            {
                replaceable->_replaceChild(i,m);
                return;
            }
        }
    }
    else
    {
        int index = _index_of(id);
        if(index != -1)
        {
            _models.replace(index,m);
            return;
        }
    }
    throw "Model not found!";
}

const QList<const Model *> *ModelDB::topLevelModels()
{
    QList<const Model*> *result = new QList<const Model*>;
    for (const Model* m : _models)
        *result << m;

    return result;
}

const QList<const Model *> *ModelDB::children_of(const QUuid &parent)
{
    return model(parent)->childs();
}

Tournament *ModelDB::_topLevelModel(const QUuid &id)
{
    for (Model* s : _models) {
        if(s->id() == id)
            return dynamic_cast<Tournament*>(s);
    }

    return nullptr;
}

Model *ModelDB::_model(const QUuid &id)
{
    for (Model* s : _models) {
        Model* m = _child(s,id);
        if(m != nullptr)
            return m;
    }

    return nullptr;
}

int ModelDB::_index_of(const QUuid &id)
{
    for (int i = 0; i < _models.count(); ++i)
    {
        if(_models.at(i)->id() == id)
            return i;
    }

    return -1;
}

Model *ModelDB::_child(Model *m, const QUuid &id)
{
    if(m->id() == id)
        return m;

    for (Model* c : m->_childs()) {
        Model* C = _child(c,id);
        if(C != nullptr)
            return C;
    }
    return nullptr;
}

template<typename T>
const T *ModelDB::model(const QUuid &id, Model::ModelType type)
{
    for (Model* s : _models) {
        Model* m = _child(s,id);
        if(m != nullptr && m->type() == type)
            return static_cast<T*>(m);
    }

    return nullptr;
}
