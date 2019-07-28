#include "modeldb.h"

ModelDB::ModelDB()
{

}

ModelDB::~ModelDB()
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

void ModelDB::addTopLevelModel(Model *m)
{
    _models << m;
}

void ModelDB::addSubModel(Model *m, const QUuid &parent)
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

    auto replaceable = _model(id);
    if(replaceable == nullptr)
        throw  "No object to replace";
    if(replaceable->parent() != nullptr)
    {
        QList<Model*> children = replaceable->parent()->_childs();
        auto parent = replaceable->parent();
        for (int i = 0; i < children.count(); ++i) {
            if(children.at(i)->id() == id)
            {
                parent->_replaceChild(i,m);
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

const QList<const Model*> ModelDB::topLevelModels()
{
    QList<const Model*> result;
    for (auto m : _models)
        result << m;

    return result;
}

const QList<const Model *> ModelDB::all_Children_Of(const QUuid &ancestor, const Model::ModelType &type)
{
    QList<const Model*> result;
    Model* m = _model(ancestor);

    if(m == nullptr || m->isLeaf())
        throw "Is either null or leaf";

    QList<const Model*> children = m->childs();
    for (const Model* child : children)
    {
        if(child->type() == type || type == Model::DefaultModel)
            result << child;
        try {
            result << all_Children_Of(child->id(),type);
        } catch (const char* msg) {Q_UNUSED(msg);}
    }

    return result;
}

QList<QTreeWidgetItem *> ModelDB::toModels(const Model::ModelType &type, const QUuid &parent) const
{

}

const QTreeWidgetItem *ModelDB::createModel(Model *m)
{
    QStringList data;

    auto stringFromType = [](Model::ModelType t)->QString
    {
        if(t == Model::TournamentModel)
            return "Tournament";
        else if(t == Model::RoundModel)
            return "Round";
        else if(t == Model::PointModel)
            return "Point";
        else
            return QString();
    };

    if(m->type() == Model::TournamentModel)
    {
        auto M = dynamic_cast<Tournament*>(m);

        data << M->name() <<
                QString::number(M->numberOfRounds()) <<
                QString::number(M->maxUsersAllowed()) <<
                QString::number(M->numberOfUsersAssigned()) <<
                M->dateCreated().toString(DATEFORMAT) <<
                M->dateFinished().toString(DATEFORMAT) <<
                stringFromType(M->type()) <<
                M->id().toString(QUuid::WithoutBraces);

        return new QTreeWidgetItem(data);
    }
    else if(m->type() == Model::RoundModel)
    {
        auto M = dynamic_cast<Round*>(m);
        data << QString::number(M->roundNumber()) <<
                stringFromType(M->type()) <<
                M->id().toString(QUuid::WithoutBraces);

        return new QTreeWidgetItem(data);
    }
    else if(m->type() == Model::PointModel)
    {
        auto M = dynamic_cast<Point*>(m);

        data << M->userId().toString(QUuid::WithoutBraces) <<
                QString::number(M->point()) <<
                stringFromType(M->type()) <<
                M->id().toString(QUuid::WithoutBraces);

        return new QTreeWidgetItem(data);
    }
    else
        return nullptr;
}

Model *ModelDB::_model(const QUuid &id)
{
    for (auto* s : _models) {
        auto* m = _child(s,id);
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

    for (auto* c : m->_childs()) {
        auto* C = _child(c,id);
        if(C != nullptr)
            return C;
    }
    return nullptr;
}

template<typename T>
const T *ModelDB::model(const QUuid &id, Model::ModelType type)
{
    for (auto s : _models) {
        auto m = _child(s,id);
        if(m != nullptr && m->type() == type)
            return static_cast<T*>(m);
    }

    return nullptr;
}
