#ifndef MODELDB_H
#define MODELDB_H

#include <qlist.h>
#include <allmodels.h>
#include <abstractmodelinterface.h>

/*
 *
 */

class ModelDB : public AbstractModelInterface
{
public:
    ModelDB();

    template<typename T>
    const T* model(const QUuid &id,Model::ModelType type);

    // Reimplemented pure virtual methods
    const Model *model(const QUuid &id);
    void addModel(Model* m, const QUuid &parent = QUuid());
    void replaceModel(Model* m, const QUuid &id);
    const QList<const Model *> *topLevelModels();
    const QList<const Model *> *children_of(const QUuid &parent);

private:
    /*topLevelModel(id):
     *  - Get toplevel object from UUID. This method is faster than template 'Model'
     *    as it doesn't search the entire tree of childs.
     */

    Tournament *_topLevelModel(const QUuid &id);
    Model* _model(const QUuid &id);
    int _index_of(const QUuid &id);
    Model *_child(Model *m, const QUuid &id);

    QList<Model*> _models;
};

#endif // MODELDB_H
