#ifndef REMOTEUSERMANAGER_H
#define REMOTEUSERMANAGER_H

#include <networkmanager.h>

class RemoteUserManager : public NetworkManager
{
public:
    RemoteUserManager(const QString &hostUrl,const QString &apiAccessCode);

public slots:

    void verifyCredentials(const QString &userName, const QString &password);

    void users();
    void user(const QUuid &user);

    // Alter remote state
    void addUser(const QByteArray &json);
    void removeUser(const QUuid &user);

private slots:

    // Handle recieved data from non-post requests
    void handleReply();
};

#endif // REMOTEUSERMANAGER_H
