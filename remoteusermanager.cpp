#include "remoteusermanager.h"

RemoteUserManager::RemoteUserManager(const QString &hostUrl, const QString &apiAccessCode):
    NetworkManager (hostUrl,apiAccessCode)
{

}

void RemoteUserManager::verifyCredentials(const QString &userName, const QString &password)
{
    Q_UNUSED(userName);
    Q_UNUSED(password);
    // TODO: Implement logic when details about remote  endpoints are available
}

void RemoteUserManager::addUser(const QByteArray &json)
{
    Q_UNUSED(json);
    // TODO: Implement logic when details about remote  endpoints are available
}

void RemoteUserManager::user(const QUuid &user)
{
    Q_UNUSED(user);
    // TODO: Implement logic when details about remote  endpoints are available
}

void RemoteUserManager::removeUser(const QUuid &user)
{
    Q_UNUSED(user);
    // TODO: Implement logic when details about remote  endpoints are available
}


void RemoteUserManager::handleReply()
{
    if(errorOccured())
    {
        QString err = errorString();
        emit notifyCallers(false);
    }
}
