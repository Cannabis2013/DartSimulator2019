#include "dbmanager.h"



DBManager::DBManager(const QString &serverUrl, const QString &key):
    LocalHTTPClientAPI (serverUrl,key)
{

}

void DBManager::requestAllTournaments()
{

}

void DBManager::handleTournaments()
{
    // TODO: Handle the network reply
}

