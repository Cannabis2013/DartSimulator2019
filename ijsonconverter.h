#ifndef IMODELIZER_H
#define IMODELIZER_H

#include <qlist.h>
#include <quuid.h>

template<typename K,typename V,typename R = int>
struct IJsonConverter
{
    virtual K createModel(const V &parameter1, const R &parameter2) const=0;
    virtual QList<K> createModels(const V &parameter1, const R&parameter2) const=0;


};

#endif // IMODELIZER_H
