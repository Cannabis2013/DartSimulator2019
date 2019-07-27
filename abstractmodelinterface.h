#ifndef ABSTRACTMODELINTERFACE_H
#define ABSTRACTMODELINTERFACE_H

#include <quuid.h>
#include <allmodels.h>

class AbstractModelInterface
{
public:

    virtual ~AbstractModelInterface();
    virtual const Model* model(const QUuid &id) = 0;
    virtual void addModel(Model* m, const QUuid &parent)=0;
    virtual void replaceModel(Model* m, const QUuid &parent)=0;
    virtual const QList<const Model*>* models()=0;

};

#endif // ABSTRACTMODELINTERFACE_H
