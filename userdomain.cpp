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

    connect(_service,&IDartSimulator::externalPopupMessage,this,&UserDomain::showSystemTrayMessage);
}

IDartSimulator *UserDomain::service()
{
    return _service;
}

void UserDomain::setupTournamentView(View *v,const QString &frameTitle)
{
    _views.append(v);
    QPointer<CustomDialog> view = new CustomDialog(v);
    view->setFrameTitle(frameTitle);

    connect(v,&View::requestModels,_service,&IDartSimulator::tournaments);
    connect(_service,&IDartSimulator::sendModels,v,&View::setModels);
    connect(_service,&IDartSimulator::externalRequestFailed,v,&View::handleError);
    connect(v,&View::requestDeleteModel,_service,&IDartSimulator::deleteTournament);
    connect(v,&View::aboutToClose,this,&UserDomain::removeView);

    view->show();
    v->updateModel();
}

void UserDomain::notifyView(const QUuid &id)
{
    for (View* v : _views)
    {
        if(v->classId() == id)
            v->requestCompleted();
    }
}

void UserDomain::requestAllTournaments()
{
    service()->tournaments();
}

void UserDomain::showSystemTrayMessage(const QString &msg)
{
    if(!QSystemTrayIcon::isSystemTrayAvailable())
        return;

    systemTray->showMessage("Message",msg);
}

void UserDomain::removeView(const QUuid &id)
{
    for (View* v : _views)
    {
        if(v->classId() == id)
        {
            _views.removeOne(v);
        }
    }
}
