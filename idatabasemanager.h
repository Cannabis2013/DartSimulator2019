#ifndef ABSTRACTMODELINTERFACE_H
#define ABSTRACTMODELINTERFACE_H

#include <quuid.h>
#include <allmodels.h>

template<typename K,typename V = int>
class IDatabaseManager
{
public:
    virtual const K* model(const QUuid &id) = 0;
    virtual void addTopLevelModel(K* m)=0;
    virtual void addSubModel(K* m, const QUuid &parent)=0;
    virtual void replaceModel(K* m, const QUuid &parent)=0;
    virtual const QList<const K*> topLevelModels()=0;
    virtual const QList<const K*> all_Children_Of(const QUuid &ancestor, const V &type) = 0;
};

#endif // ABSTRACTMODELINTERFACE_H
