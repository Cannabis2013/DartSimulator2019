#ifndef MODELDB_H
#define MODELDB_H

#include <qlist.h>
#include <allmodels.h>
#include <idatabasemanager.h>
#include <imodelizer.h>
#include <QTreeWidgetItem>

/*
 *
 */

class ModelDB : public IDatabaseManager<Model,Model::ModelType>,
        public IModelizer<QTreeWidgetItem,Model>
{
public:
    ModelDB();
    virtual ~ModelDB();

    template<typename T>
    const T* model(const QUuid &id,Model::ModelType type);

    // Reimplemented pure virtual methods
    const Model *model(const QUuid &id) const;
    void addTopLevelModel(Model *m);
    void addSubModel(Model* m, const QUuid &parent = QUuid());
    void replaceModel(Model* newModel, const QUuid &id);
    QList<const Model*> topLevelModels() const;
    QList<const Model*> all_Children_Of(const QUuid &ancestor,const Model::ModelType &type = Model::DefaultModel) const;

    QList<QTreeWidgetItem*> toModels(const QUuid &parent = QUuid()) const;
private:
    QTreeWidgetItem* createModel(Model* m) const;

    bool isLeaf(Model* m) const;

    Model* _model(const QUuid &id) const;
    int _index_of(const QUuid &id);
    Model *_child(Model *parent, const QUuid &id) const;

    QList<Model*> _models;
};

#endif // MODELDB_H
