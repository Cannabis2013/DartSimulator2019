#ifndef REMOTEUSERMANAGER_H
#define REMOTEUSERMANAGER_H

#include <networkmanager.h>

class RemoteUserManager : public NetworkManager
{
public:
    RemoteUserManager(const QString &hostUrl,const QString &apiAccessCode);

public slots:

};

#endif // REMOTEUSERMANAGER_H
