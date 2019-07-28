#ifndef IMODELIZER_H
#define IMODELIZER_H

#include <qlist.h>
#include <quuid.h>

template<typename K,typename V,typename R = int>
class IModelizer
{
public:

    virtual const K* createModel(V* item)=0;
    virtual QList<K*> toModels(const R &parameter, const QUuid &parent = QUuid()) const=0;
};

#endif // IMODELIZER_H
