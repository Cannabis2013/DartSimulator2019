#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <qstring.h>
#include <qobject.h>

template<typename K, typename V>
class IGraphicalUserInterface
{
public:
    virtual void setService(K* service)=0;
    virtual K* service()=0;

    virtual void setupLoginView(V v, const QString &frameTitle)=0;
    virtual void setupTournamentView(V v, const QString &frameTitle)=0;
};

#endif // UIMANAGER_H
