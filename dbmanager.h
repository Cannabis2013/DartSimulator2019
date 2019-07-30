#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "localhttpclientapi.h"
#include <QFunctionPointer>

class DBManager : public LocalHTTPClientAPI
{
public:
    DBManager(const QString &serverUrl,const QString &key = QString());

    void requestAllTournaments();

public slots:
    void handleTournaments();
};

#endif // DBMANAGER_H
