#include "userdomain.h"

UserDomain::UserDomain()
{
    systemTray = new QSystemTrayIcon();
}

UserDomain::~UserDomain()
{

}


void UserDomain::setService(IDartSimulator *service)
{
    _service = service;

    connect(_service,&IDartSimulator::externalPopupMessage,this,&UserDomain::showSystemTrayMessage);
    connect(_service,&IDartSimulator::externalNotifyResponse,this,&UserDomain::notifyView);
}

IDartSimulator *UserDomain::service()
{
    return _service;
}

void UserDomain::setupLoginView(View *v,const QString &frameTitle)
{
    _views.append(v);
    v->setResizeable(false);
    QPointer<CustomDialog> view = new CustomDialog(v);
    view->setFrameTitle(frameTitle);

    view->show();
}

void UserDomain::setupTournamentView(View *v,const QString &frameTitle)
{
    _views.append(v);
    v->setResizeable(false);
    QPointer<CustomDialog> view = new CustomDialog(v);
    view->setFrameTitle(frameTitle);

    connect(v,&View::requestModels,_service,&IDartSimulator::tournaments);
    connect(_service,&IDartSimulator::sendModels,v,&View::setModels);
    connect(_service,&IDartSimulator::externalRequestFailed,v,&View::handleError);
    connect(v,&View::requestDeleteModel,_service,&IDartSimulator::deleteTournament);
    connect(v,&View::aboutToClose,this,&UserDomain::removeView);
    connect(v,&View::new_Tournament_Request,_service,&IDartSimulator::createTournament);

    view->show();
    v->updateState();
}

void UserDomain::notifyView()
{
    for (View* v : _views)
    {
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
        if(v != nullptr && v->classId() == id)
        {
            _views.removeOne(v);
        }
    }
}
