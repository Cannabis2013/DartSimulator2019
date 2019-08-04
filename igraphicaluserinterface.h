#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <qstring.h>
#include <qobject.h>

template<typename K>
class IGraphicalUserInterface
{
public:
    virtual void setService(K* service)=0;
    virtual K* service()=0;

    virtual void setupLoginView()=0;
    virtual void setupTournamentView()=0;
};

#endif // UIMANAGER_H
