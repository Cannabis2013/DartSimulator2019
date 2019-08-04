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
}

IDartSimulator *UserDomain::service()
{
    return _service;
}

void UserDomain::setupLoginView()
{
    LoginView* lView =new LoginView;
    lView->setResizeable(false);
    QPointer<CustomDialog> view = new CustomDialog(lView);

    view->show();
}

void UserDomain::setupTournamentView()
{
    TournamentSelectorView *tView = new TournamentSelectorView();
    tView->setResizeable(false);
    QPointer<CustomDialog> view = new CustomDialog(tView);

    connect(tView,&TournamentSelectorView::requestModels,_service,&IDartSimulator::tournaments);
    connect(_service,&IDartSimulator::sendModels,tView,&TournamentSelectorView::setModels);
    connect(_service,&IDartSimulator::externalRequestFailed,tView,&View::handleError);
    connect(tView,&TournamentSelectorView::requestDeleteModel,_service,&IDartSimulator::deleteTournament);
    connect(tView,&View::aboutToClose,this,&UserDomain::removeView);
    connect(tView,&TournamentSelectorView::new_Tournament_Request,_service,&IDartSimulator::createTournament);
    connect(_service,&IDartSimulator::externalNotifyResponse,tView,&View::requestCompleted);

    view->show();
    tView->updateState();
}

void UserDomain::notifyView()
{

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
