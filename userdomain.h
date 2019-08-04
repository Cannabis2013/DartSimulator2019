#ifndef GRAPHICALUSERDOMAIN_H
#define GRAPHICALUSERDOMAIN_H

#include <igraphicaluserinterface.h>
#include <idartsimulator.h>
#include <tournamentselectorview.h>
#include <customdialog.h>
#include <QSystemTrayIcon>
#include <loginview.h>

class UserDomain : public QObject,public IGraphicalUserInterface<IDartSimulator,View*>
{
    Q_OBJECT
public:
    UserDomain();

    virtual ~UserDomain();
    void setService(IDartSimulator *service);
    IDartSimulator *service();

public slots:
    void setupLoginView(View *v, const QString &frameTitle);
    void setupTournamentView(View *v, const QString &frameTitle);

private slots:
    void notifyView();
    void requestAllTournaments();
    void showSystemTrayMessage(const QString &msg);

    void removeView(const QUuid &id);
private:
    QSystemTrayIcon*systemTray;
    IDartSimulator* _service;

    QList<View*> _views;
};

#endif // GRAPHICALUSERDOMAIN_H
