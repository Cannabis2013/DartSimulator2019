#include "dbmanager.h"

DBManager::DBManager()
{
    db = new ModelDatabase();
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
    return db->items<TournamentModel>(season->allTournamentIdentities());
}

const QList<const RoundModel*> *DBManager::rounds()
{
    return db->items<RoundModel>(Model::RoundModel);
}

const QList<const RoundModel*> *DBManager::rounds(const QUuid &tournamentId)
{
    const TournamentModel* tournament = db->item<TournamentModel>(tournamentId);
    return db->items<RoundModel>(tournament->allRoundIdentities());
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
    const QList<const RoundModel*> *rounds = db->items<RoundModel>(tEntity->allRoundIdentities());

    QList<const PointModel*> *selectedPoints = new QList<const PointModel*>;

    for (const RoundModel* round : *rounds)
    {
        const QList<const PointModel*> *points = db->items<PointModel>(round->allPointIdentities());
        for (const PointModel* point : *points)
        {
            if(userId == QUuid() || point->userId() == userId)
                selectedPoints->append(point);
        }
    }

    return selectedPoints;
}

bool DBManager::addSubModel(const QUuid &subModel, const QUuid &parentModel)
{
    try {
        db->appendChild(subModel,parentModel);
        return true;
    } catch (invalid_argument e) {
        return false;
    }
}

bool DBManager::addSubModels(const QList<QUuid> &subModels, const QUuid &parentModel)
{
    try {
        db->appendChildren(subModels,parentModel);
        return true;
    } catch (invalid_argument e) {
        return false;
    }
}

void DBManager::addModel(Model *model)
{
    db->addItem(model);
}

void DBManager::removeModel(const QUuid &id)
{
    db->removeItem(id);
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
    for (Model* entity : _items) {
        if(entity->id() == id)
        {
            if(entity->parentId() != QUuid())
                _itemAt(entity->parentId())->removeIdentifier(entity->id());

            _items.removeOne(entity);
            return;
        }
    }
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

void ModelDatabase::appendChild(const QUuid &id, const QUuid &parentId)
{
    Model* childCandidate = _itemAt(id);
    Model* parentCandidate = _itemAt(parentId);

    if(parentCandidate->type() == Model::PointModel || childCandidate->type() == Model::SeasonModel)
        throw invalid_argument("One, or both, of the models is not applicable for the operation");
    parentCandidate->appendIdentifier(childCandidate->id());
    childCandidate->setParentId(parentCandidate->id());
}

void ModelDatabase::appendChildren(const QList<QUuid> &children, const QUuid &parentId)
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
const QList<const T *> *ModelDatabase::items(QList<QUuid> identities)
{
    QList<const T*> *result = new QList<const T*>();
    for (Model* entity : _items)
    {
        if(identities.contains(entity->id()))
            result->append(static_cast<T*>(entity));
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
