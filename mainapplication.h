#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include <idartsimulator.h>
#include <remotemodelmanager.h>
#include <datamodelmanager.h>
#include <gamemanager.h>

#define USERCODE "wQ71HOHNXNaHkDxnnaZ7kj6ujWYW2xBsV1VXxRqp8C/83IgryF1ADA=="
#define HOSTURL "https://dartservice.azurewebsites.net/api/"

class MainApplication : public IDartSimulator
{
    Q_OBJECT
public:
    MainApplication();

private:
    DataModelManager* _dataModel;
    RemoteModelManager* _remote;
    GameManager* _game;

};

#endif // MAINAPPLICATION_H
