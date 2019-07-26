#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <qlist.h>
#include <allmodels.h>

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
    const QList<const T*> *items(QList<QUuid> identities,Model::ModelType type);

    template<typename T>
    QList<const T*> *items(Model::ModelType type);

    void replaceItem(const QUuid &id,Model *model);

    void appendChildIdentity(const QUuid &id, const QUuid &parentId);
    void appendChildIdentities(const QList<QUuid> &children,const QUuid &parentId);
    void removeChildIdentity(const QUuid &child,const QUuid &parent);

private:

    Model *_itemAt(const QUuid &id);

    QList<Model*> _items;
};

class DBManager
{
public:
    DBManager();

    Model::ModelType modelType(const QUuid &id);

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

    template<typename T>
    const T* model(const QUuid &modelIdentity){return db->item<T>(modelIdentity);}

    void addModel(Model *model, const QUuid &parentId = QUuid());
    bool removeModel(const QUuid &id);
    void replaceModel(const QUuid &id, Model*& model);

    bool addSubIdentity(const QUuid &subModel, const QUuid &parentModel);
    bool addSubIdentities(const QList<QUuid> &subIdentities, const QUuid &parentIdentity);

    void removeChildIdentity(const QUuid &subModel, const QUuid &parentModel);

private:

    ModelDatabase *db;
};

#endif // DBMANAGER_H
