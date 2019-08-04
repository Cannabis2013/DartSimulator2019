#include "userdomain.h"

UserDomain::UserDomain()
{
    systemTray = new QSystemTrayIcon();
    systemTray->setIcon(QIcon(":/new/prefix1/Ressources/dart-board.png"));
    systemTray->show();
}

UserDomain::~UserDomain()
{
    systemTray->deleteLater();
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

    connect(_service,&IDartSimulator::externalNotifyResponse,lView,&LoginView::handleReply);
    connect(lView,&LoginView::success,this,&UserDomain::setupTournamentView);
    connect(lView,&View::popupMessage,this,&UserDomain::showSystemTrayMessage);
    connect(lView,&LoginView::destroyed,this,&UserDomain::close);

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
    connect(tView,&TournamentSelectorView::requestDeleteModel,_service,&IDartSimulator::removeTournament);
    connect(tView,&View::destroyed,this,&UserDomain::close);
    connect(tView,&TournamentSelectorView::new_Tournament_Request,_service,&IDartSimulator::parseTournament);
    connect(_service,&IDartSimulator::externalNotifyResponse,tView,&View::handleReply);

    view->show();
    tView->updateState();
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

void UserDomain::close()
{
    delete this;
}
