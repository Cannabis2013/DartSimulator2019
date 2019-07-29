#ifndef IMODELIZER_H
#define IMODELIZER_H

#include <qlist.h>
#include <quuid.h>

template<typename K,typename V>
struct IModelizer
{
    virtual K* createModel(V* item) const=0;
    virtual QList<K*> toModels(const QUuid &parent = QUuid()) const=0;
};

#endif // IMODELIZER_H
