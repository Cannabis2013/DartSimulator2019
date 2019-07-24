#include "dbmanager.h"

DBManager::DBManager()
{
    db = new EntityDB();
}

const QList<const SeasonModel *> *DBManager::seasons()
{
    return db->models<SeasonModel>(Model::SeasonModel);
}

const QList<const TournamentModel *> *DBManager::tournaments()
{
    return db->models<TournamentModel>(Model::TournamentModel);
}

const QList<const TournamentModel*> *DBManager::tournaments(const QUuid &seasonId)
{
    const SeasonModel* season = db->model<SeasonModel>(seasonId);
    return db->models<TournamentModel>(season->allTournamentIdentities());
}

const QList<const RoundModel*> *DBManager::rounds()
{
    return db->models<RoundModel>(Model::RoundModel);
}

const QList<const RoundModel*> *DBManager::rounds(const QUuid &tournamentId)
{
    const TournamentModel* tournament = db->model<TournamentModel>(tournamentId);
    return db->models<RoundModel>(tournament->allRoundIdentities());
}

const QList<const PointModel*> *DBManager::points()
{
    return db->models<PointModel>(Model::PointModel);
}

const QList<const PointModel *> *DBManager::points(const QUuid &userId)
{
    QList<const PointModel*> *allPoints = db->models<PointModel>(Model::PointModel);
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
    const TournamentModel* tEntity = db->model<TournamentModel>(tournamentId);
    const QList<const RoundModel*> *rounds = db->models<RoundModel>(tEntity->allRoundIdentities());

    QList<const PointModel*> *selectedPoints = new QList<const PointModel*>;

    for (const RoundModel* round : *rounds)
    {
        const QList<const PointModel*> *points = db->models<PointModel>(round->allPointIdentities());
        for (const PointModel* point : *points)
        {
            if(userId == QUuid() || point->userId() == userId)
                selectedPoints->append(point);
        }
    }

    return selectedPoints;
}

QList<Model *> const EntityDB::models()
{
    return _models;
}

void EntityDB::setModels(const QList<Model *> &entities)
{
    _models = entities;
}

void EntityDB::addModel(Model *model)
{
    _models << model;
}

void EntityDB::removeModel(const QUuid &id)
{
    for (Model* entity : _models) {
        if(entity->id() == id)
        {
            _models.removeOne(entity);
            return;
        }
    }
}
