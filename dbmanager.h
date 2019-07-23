#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <qlist.h>
#include <AllEntities.h>

namespace DBContext {
    class EntityDB;
    class DBManager;
}

class EntityDB
{
    QList<ModelEntity *> const entities();
    void setEntities(const QList<ModelEntity *> &entities);
    void addEntity(ModelEntity* entity);
    void removeEntity(const QUuid &id);

    template<typename T>
    T model(QUuid id)
    {
        for (ModelEntity* entity : _entities)
        {
            if(entity->id() == id)
                return static_cast<T>(entity);
        }
        return nullptr;
    }

    template<typename T>
    QList<T> models(QList<QUuid> identities)
    {
        QList<T> result;
        for (ModelEntity* entity : _entities)
        {
            if(identities.contains(entity->id()))
                result << static_cast<T>(entity);
        }
        return result;
    }

    template<typename T>
    QList<T> models(ModelEntity::ModelType type)
    {
        QList<T> result;
        for (ModelEntity* entity : _entities)
        {
            if(entity->type() == type)
                result << static_cast<T>(entity);
        }
        return result;
    }

    QList<ModelEntity*> _entities;

    friend class DBManager;
};

class DBManager
{
public:
    DBManager();

    QList<SeasonEntity*> seasons() const;

    QList<TournamentEntity*> tournaments() const;
    QList<TournamentEntity*> tournaments(const QUuid &seasonId) const;

    QList<RoundEntity*> rounds() const;
    QList<RoundEntity*> rounds(const QUuid &tournamentId) const;

    QList<PointEntity*> points() const;
    QList<PointEntity*> points(const QUuid &userId) const;
    QList<PointEntity*> points(const QUuid &tournamentId,const QUuid &userId = QUuid()) const;

private:
    EntityDB *db;
};

#endif // DBMANAGER_H
