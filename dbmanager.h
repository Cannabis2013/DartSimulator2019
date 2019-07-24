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
public:
    QList<Model *> const models();
    void setModels(const QList<Model *> &entities);
    void addModel(Model* model);
    void removeModel(const QUuid &id);

    template<typename T> const
    T* model(QUuid id)
    {
        for (Model* model : _models)
        {
            if(model->id() == id)
                return static_cast<T*>(model);
        }
        return nullptr;
    }

    template<typename T>
    const QList<const T*> *models(QList<QUuid> identities)
    {
        QList<const T*> *result = new QList<const T*>();
        for (Model* entity : _models)
        {
            if(identities.contains(entity->id()))
                result->append(static_cast<T*>(entity));
        }
        return result;
    }

    template<typename T>
    QList<const T*> *models(Model::ModelType type)
    {
        QList<const T*> *result = new QList<const T*>();
        for (Model* entity : _models)
        {
            if(entity->type() == type)
                result->append(static_cast<T*>(entity));
        }
        return result;
    }

private:

    QList<Model*> _models;
};

class DBManager
{
public:
    DBManager();

    const QList<const SeasonModel*> *seasons();

    const QList<const TournamentModel*> *tournaments();
    const QList<const TournamentModel*> *tournaments(const QUuid &seasonId);

    const QList<const RoundModel*> *rounds();
    const QList<const RoundModel*> *rounds(const QUuid &tournamentId);

    const QList<const PointModel*> *points();
    const QList<const PointModel*> *points(const QUuid &userId);
    const QList<const PointModel*> *points(const QUuid &tournamentId,const QUuid &userId = QUuid());

private:
    EntityDB *db;
};

#endif // DBMANAGER_H
