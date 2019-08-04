#ifndef GRAPHICALUSERDOMAIN_H
#define GRAPHICALUSERDOMAIN_H

#include <igraphicaluserinterface.h>
#include <idartsimulator.h>
#include <tournamentselectorview.h>
#include <customdialog.h>
#include <QSystemTrayIcon>
#include <loginview.h>


class UserDomain : public QObject,public IGraphicalUserInterface<IDartSimulator>
{
    Q_OBJECT
public:
    UserDomain();

    virtual ~UserDomain();
    void setService(IDartSimulator *service);
    IDartSimulator *service();

public slots:
    void setupLoginView();
    void setupTournamentView();

private slots:
    void requestAllTournaments();
    void showSystemTrayMessage(const QString &msg);
    void close();

private:
    QSystemTrayIcon* systemTray;
    IDartSimulator* _service;

    QList<View*> _views;
};

#endif // GRAPHICALUSERDOMAIN_H
