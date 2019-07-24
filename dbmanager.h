#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <qlist.h>
#include <AllEntities.h>

/*
 * Model database provides the basic operation needed for manipulation of the state of the database
 * These operations is:
 *  - Add/remove models
 *  - Model lookup
 *  - Add/remove submodels
 */

class ModelDatabase
{
public:
    void setItems(const QList<Model *> &entities);
    void addItem(Model* model);
    void removeItem(const QUuid &id);

    template<typename T> const
    T* item(QUuid id);

    QList<Model *> const items();
    template<typename T>
    const QList<const T*> *items(QList<QUuid> identities);

    template<typename T>
    QList<const T*> *items(Model::ModelType type);

    void replaceItem(const QUuid &id,Model *model);

    void appendChild(const QUuid &id, const QUuid &parentId);
    void appendChildren(const QList<QUuid> &children,const QUuid &parentId);

private:

    Model *_itemAt(const QUuid &id);

    QList<Model*> _items;
};

class DBManager
{
public:
    DBManager();

    /*
     * Get model methods based on parameters
     */

    const QList<const SeasonModel*> *seasons();

    const QList<const TournamentModel*> *tournaments();
    const QList<const TournamentModel*> *tournaments(const QUuid &seasonId);

    const QList<const RoundModel*> *rounds();
    const QList<const RoundModel*> *rounds(const QUuid &tournamentId);

    const QList<const PointModel*> *points();
    const QList<const PointModel*> *points(const QUuid &userId);
    const QList<const PointModel*> *points(const QUuid &tournamentId,const QUuid &userId = QUuid());

    /*
     * Alter state of DB methods
     */

    void addModel(Model *model);
    void removeModel(const QUuid &id);
    void replaceModel(const QUuid &id, Model*& model);

    bool addSubModel(const QUuid &subModel, const QUuid &parentModel);
    bool addSubModels(const QList<QUuid> &subModels,const QUuid &parentModel);

private:
    ModelDatabase *db;
};

#endif // DBMANAGER_H
