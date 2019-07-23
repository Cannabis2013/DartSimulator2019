#ifndef ABSTRACTCOMPARABLE_H
#define ABSTRACTCOMPARABLE_H

#include <qobject.h>
template<class T>
class AbstractComparable
{
public:
    virtual bool operator ()(T a,T b) = 0;
};

#endif // ABSTRACTCOMPARABLE_H
