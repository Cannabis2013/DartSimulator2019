#ifndef IMODELIZER_H
#define IMODELIZER_H

#include <qlist.h>
#include <quuid.h>

/*
 * Convert from type V to K.
 * Example:
 *      V = QBytearray, K = QTreeWidgetItem*
 *      QTreeWidgetItem* createModel(const QByteArray &paramter1);
 */

template<typename K,typename V,typename R = K>
struct IJsonConverter
{
    virtual K ConvertDataItem(V &parameter1)=0;
    virtual K ConvertDataItems(V &parameter1)=0;




};

#endif // IMODELIZER_H
