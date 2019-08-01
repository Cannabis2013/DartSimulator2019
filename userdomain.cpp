#include "userdomain.h"

UserDomain::UserDomain()
{

}

UserDomain::~UserDomain()
{

}


void UserDomain::setService(IDartSimulator *service)
{
    _service = service;
}

IDartSimulator *UserDomain::service()
{
    return _service;
}

void UserDomain::setupTournamentView(View *v,const QString &frameTitle)
{
    QPointer<CustomDialog> view = new CustomDialog(v);
    view->setFrameTitle(frameTitle);

    /*
     * TODO: You have to figure out to connect necessary signals to appropriate slots.
     * TODO: You need to make some type of object conversion
     *          as the argument doesn't contain any slots suitet for the operation
     */

    connect(v,&View::requestModels,_service,&IDartSimulator::tournaments);
    connect(_service,&IDartSimulator::sendTournaments,v,&View::setModels);
    connect(_service,&IDartSimulator::externalRequestFailed,v,&View::handleError);

    view->show();
}

void UserDomain::requestAllTournaments()
{
    service()->tournaments();
}
