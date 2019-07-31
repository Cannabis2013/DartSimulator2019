#include "dbmanager.h"



DBManager::DBManager(const QString &serverUrl, const QString &key):
    RemoteDatabaseContext (serverUrl,key)
{

}

void DBManager::requestAllTournaments()
{

}

void DBManager::handleTournaments()
{
    // TODO: Handle the network reply
}

