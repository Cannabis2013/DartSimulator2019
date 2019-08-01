#include "graphicaluserdomain.h"

GraphicalUserDomain::GraphicalUserDomain()
{

}

GraphicalUserDomain::~GraphicalUserDomain()
{

}


void GraphicalUserDomain::setService(IDartSimulator *service)
{
    _service = service;
}

IDartSimulator *GraphicalUserDomain::service()
{
    return _service;
}

void GraphicalUserDomain::setupTournamentView(AbstractFrameImplementable *v,const QString &frameTitle)
{
    QPointer<CustomDialog> view = new CustomDialog(v);
    view->setFrameTitle(frameTitle);

    /*
     * TODO: You have to figure out to connect necessary signals to appropriate slots.
     * TODO: You need to make some type of object conversion
     *          as the argument doesn't contain any slots suitet for the operation
     */

    view->show();
}

void GraphicalUserDomain::requestAllTournaments()
{
    service()->tournaments();
}
