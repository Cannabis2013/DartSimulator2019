#include "dbmanager.h"

DBManager::DBManager()
{
    db = new EntityDB();
}

QList<SeasonEntity *> DBManager::seasons() const
{
    return db->models<SeasonEntity*>(ModelEntity::SeasonModel);
}

QList<TournamentEntity *> DBManager::tournaments() const
{
    return db->models<TournamentEntity*>(ModelEntity::TournamentModel);
}

QList<TournamentEntity *> DBManager::tournaments(const QUuid &seasonId) const
{
    SeasonEntity* season = db->model<SeasonEntity*>(seasonId);
    return db->models<TournamentEntity*>(season->allTournamentIdentities());
}

QList<RoundEntity *> DBManager::rounds() const
{
    return db->models<RoundEntity*>(ModelEntity::RoundModel);
}

QList<RoundEntity *> DBManager::rounds(const QUuid &tournamentId) const
{
    TournamentEntity* tournament = db->model<TournamentEntity*>(tournamentId);
    return db->models<RoundEntity*>(tournament->allRoundIdentities());
}

QList<PointEntity *> DBManager::points() const
{
    return db->models<PointEntity*>(ModelEntity::PointModel);
}

QList<PointEntity *> DBManager::points(const QUuid &userId) const
{
    QList<PointEntity*> allPoints = db->models<PointEntity*>(ModelEntity::PointModel);
    QList<PointEntity*> userPoints;
    for (PointEntity* point : allPoints)
    {
        if(point->userId() == userId)
            allPoints << point;
    }
    return allPoints;
}

QList<PointEntity *> DBManager::points(const QUuid &tournamentId, const QUuid &userId) const
{
    TournamentEntity* tEntity = db->model<TournamentEntity*>(tournamentId);
    QList<RoundEntity*> rounds = db->models<RoundEntity*>(tEntity->allRoundIdentities());

    QList<PointEntity*> allPoints;

    for (RoundEntity* round : rounds)
    {
        QList<PointEntity*> points = db->models<PointEntity*>(round->allPointIdentities());
        for (PointEntity* point : points)
        {
            if(userId == QUuid() || point->userId() == userId)
                allPoints << point;
        }
    }

    return allPoints;
}

QList<ModelEntity *> const EntityDB::entities()
{
    return _entities;
}

void EntityDB::setEntities(const QList<ModelEntity *> &entities)
{
    _entities = entities;
}

void EntityDB::addEntity(ModelEntity *entity)
{
    _entities << entity;
}

void EntityDB::removeEntity(const QUuid &id)
{
    for (ModelEntity* entity : _entities) {
        if(entity->id() == id)
        {
            _entities.removeOne(entity);
            return;
        }
    }
}
