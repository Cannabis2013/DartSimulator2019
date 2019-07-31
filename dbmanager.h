#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "remotedatabasecontext.h"
#include <QFunctionPointer>

class DBManager : public RemoteDatabaseContext
{
public:
    DBManager(const QString &serverUrl,const QString &key = QString());

    void requestAllTournaments();

public slots:
    void handleTournaments();
};

#endif // DBMANAGER_H
