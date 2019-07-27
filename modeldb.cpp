#include "modeldb.h"

ModelDB::ModelDB()
{

}

const Model *ModelDB::model(const QUuid &id)
{
    for (Model* s : _models) {
        const Model* m = child(s,id);
        if(m != nullptr)
            return m;
    }

    return nullptr;
}

void ModelDB::addModel(Model *m, const QUuid &parent)
{
    if(parent == QUuid())
        _models.append(m);

    if(M(parent) == nullptr)
        throw "Parent object doesn't exist!";

    if(M(parent)->type() == Model::PointModel)
        throw "Adding children to this type of model not allowed!";

    M(parent)->addChild(m);
}

void ModelDB::replaceModel(Model *m, const QUuid &id)
{

    Model* replaceable = M(id);
    if(replaceable == nullptr)
        throw  "No object to replace";
    if(replaceable->parent() != nullptr)
    {
        try {
            QList<Model*> children;
            for (int i = 0; i < children.count(); ++i) {
                if(children.at(i)->id() == id)
                {
                    replaceable->replaceChild(i,m);
                }
            }
        } catch (exception e) {
            throw e;
        }
        return;
    }
    else
    {
        int index = index_of(id);
        if(index != -1)
        {
            _models.replace(index,m);
            return;
        }
    }
    throw exception();
}

const QList<const Model *> *ModelDB::models()
{
    QList<const Model*> *result = new QList<const Model*>;
    for (const Model* m : _models)
        *result << m;

    return result;
}

Season *ModelDB::topLevelModel(const QUuid &id)
{
    for (Model* s : _models) {
        if(s->id() == id)
            return dynamic_cast<Season*>(s);
    }

    return nullptr;
}

Model *ModelDB::M(const QUuid &id)
{
    for (Model* s : _models) {
        Model* m = child(s,id);
        if(m != nullptr)
            return m;
    }

    return nullptr;
}

int ModelDB::index_of(const QUuid &id)
{
    for (int i = 0; i < _models.count(); ++i)
    {
        if(_models.at(i)->id() == id)
            return i;
    }

    return -1;
}

Model *ModelDB::child(Model *m, const QUuid &id)
{
    if(m->id() == id)
        return m;

    for (Model* c : m->children()) {
        Model* C = child(c,id);
        if(C != nullptr)
            return C;
    }
    return nullptr;
}

template<typename T>
const T *ModelDB::model(const QUuid &id, Model::ModelType type)
{
    for (Model* s : _models) {
        Model* m = child(s,id);
        if(m != nullptr && m->type() == type)
            return static_cast<T*>(m);
    }

    return nullptr;
}
