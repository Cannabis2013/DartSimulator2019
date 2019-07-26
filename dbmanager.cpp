#include "dbmanager.h"

DBManager::DBManager()
{
    db = new ModelDatabase();
}

Model::ModelType DBManager::modelType(const QUuid &id)
{
    return db->item<Model>(id)->type();
}

const QList<const SeasonModel *> *DBManager::seasons()
{
    return db->items<SeasonModel>(Model::SeasonModel);
}

const QList<const TournamentModel *> *DBManager::tournaments()
{
    return db->items<TournamentModel>(Model::TournamentModel);
}

const QList<const TournamentModel*> *DBManager::tournaments(const QUuid &seasonId)
{
    const SeasonModel* season = db->item<SeasonModel>(seasonId);
    return db->items<TournamentModel>(*season->allIdentifiers(),Model::TournamentModel);
}

const QList<const RoundModel*> *DBManager::rounds()
{
    return db->items<RoundModel>(Model::RoundModel);
}

const QList<const RoundModel*> *DBManager::rounds(const QUuid &tournamentId)
{
    const TournamentModel* tournament = db->item<TournamentModel>(tournamentId);
    return db->items<RoundModel>(*tournament->allIdentifiers(),Model::RoundModel);
}

const QList<const PointModel*> *DBManager::points()
{
    return db->items<PointModel>(Model::PointModel);
}

const QList<const PointModel *> *DBManager::points(const QUuid &userId)
{
    QList<const PointModel*> *allPoints = db->items<PointModel>(Model::PointModel);
    QList<const PointModel*> *userPoints = new QList<const PointModel*>();
    for (const PointModel* point : *allPoints)
    {
        if(point->userId() == userId)
            userPoints->append(point);
    }
    return userPoints;
}

const QList<const PointModel *> *DBManager::points(const QUuid &tournamentId, const QUuid &userId)
{
    const TournamentModel* tEntity = db->item<TournamentModel>(tournamentId);
    const QList<const RoundModel*> *rounds = db->items<RoundModel>(*tEntity->allIdentifiers(),Model::RoundModel);

    QList<const PointModel*> *selectedPoints = new QList<const PointModel*>;

    for (const RoundModel* round : *rounds)
    {
        const QList<const PointModel*> *points = db->items<PointModel>(*round->allIdentifiers(),Model::PointModel);
        for (const PointModel* point : *points)
        {
            if(userId == QUuid() || point->userId() == userId)
                selectedPoints->append(point);
        }
    }

    return selectedPoints;
}

bool DBManager::addSubIdentity(const QUuid &subModel, const QUuid &parentModel)
{
    try {
        db->appendChildIdentity(subModel,parentModel);
        return true;
    } catch (invalid_argument e) {
        return false;
    }
}

bool DBManager::addSubIdentities(const QList<QUuid> &subIdentities, const QUuid &parentIdentity)
{
    try {
        db->appendChildIdentities(subIdentities,parentIdentity);
        return true;
    } catch (invalid_argument e) {
        return false;
    }
}

void DBManager::removeChildIdentity(const QUuid &subModel, const QUuid &parentModel)
{
    db->removeChildIdentity(subModel,parentModel);
}

void DBManager::addModel(Model *model, const QUuid &parentId)
{
    db->addItem(model);
    if(parentId != QUuid())
        addSubIdentity(model->id(),parentId);
}

bool DBManager::removeModel(const QUuid &id)
{
    try {
        db->removeItem(id);
        return true;
    } catch (out_of_range e) {
        return false;
    } catch (exception e){
        return false;
    }
}

void DBManager::replaceModel(const QUuid &id, Model *&model)
{
    db->replaceItem(id,model);
}

QList<Model *> const ModelDatabase::items()
{
    return _items;
}

void ModelDatabase::setItems(const QList<Model *> &entities)
{
    _items = entities;
}

void ModelDatabase::addItem(Model *model)
{
    _items << model;
}

void ModelDatabase::removeItem(const QUuid &id)
{
    Model* model;
    try {
        model = _itemAt(id);
    } catch (out_of_range e) {
        throw e;
    }
    if(model->parentId() != QUuid())
        _itemAt(model->parentId())->removeIdentifier(model->id());

    for (QUuid id : *model->allIdentifiers())
    {
        Model* m = _itemAt(id);
        if(m->type() != Model::UserModel)
        {
            m->setParentId(QUuid());
            try {
                removeItem(id);
            } catch (out_of_range e) {
                throw exception();
            } catch(exception e1){
                throw exception();
            }
        }
    }
    if(!_items.removeOne(model))
        throw exception();
}

void ModelDatabase::replaceItem(const QUuid &id, Model *model)
{
    for (int i = 0; i < _items.count(); ++i)
    {
        Model *m = _items.at(i);
        if(m->id() == id)
        {
            _items.replace(i,model);
            return;
        }
    }
}

void ModelDatabase::appendChildIdentity(const QUuid &id, const QUuid &parentId)
{
    Model* childCandidate = _itemAt(id);
    Model* parentCandidate = _itemAt(parentId);

    if(parentCandidate->type() == Model::PointModel || childCandidate->type() == Model::SeasonModel)
        throw invalid_argument("One, or both, of the models is not applicable for the operation");
    parentCandidate->appendIdentifier(childCandidate->id());
    childCandidate->setParentId(parentCandidate->id());
}

void ModelDatabase::appendChildIdentities(const QList<QUuid> &children, const QUuid &parentId)
{
    Model* parentCandidate = _itemAt(parentId);
    if(parentCandidate->type() == Model::PointModel)
        throw invalid_argument("One, or both, of the models is not applicable for the operation");

    for (QUuid id : children)
    {
        Model* childCandidate = _itemAt(id);
        if(childCandidate->type() == Model::SeasonModel)
            throw invalid_argument("One, or both, of the models is not applicable for the operation");
        parentCandidate->appendIdentifier(id);
        childCandidate->setParentId(parentId);
    }
}

void ModelDatabase::removeChildIdentity(const QUuid &child, const QUuid &parent)
{
    /*
     * Please note, this operation doesn't alter the state of the database,
     * which means that no object other than the objects internally stored UUID is removed.
     */

    Model* m = _itemAt(parent);
    m->removeIdentifier(child);
}

Model *ModelDatabase::_itemAt(const QUuid &id)
{
    for (Model* model : _items)
    {
        if(model->id() == id)
            return model;
    }
    throw out_of_range("Model not found");
}

template<typename T>
const T *ModelDatabase::item(QUuid id)
{
    for (Model* model : _items)
    {
        if(model->id() == id)
            return static_cast<T*>(model);
    }
    return nullptr;
}

template<typename T>
const QList<const T *> *ModelDatabase::items(QList<QUuid> identities, Model::ModelType type)
{
    QList<const T*> *result = new QList<const T*>();
    for (Model* model : _items)
    {
        if(identities.contains(model->id()) && model->type() == type)
            result->append(static_cast<T*>(model));
    }
    return result;
}

template<typename T>
QList<const T *> *ModelDatabase::items(Model::ModelType type)
{
    QList<const T*> *result = new QList<const T*>();
    for (Model* entity : _items)
    {
        if(entity->type() == type)
            result->append(static_cast<T*>(entity));
    }
    return result;
}
