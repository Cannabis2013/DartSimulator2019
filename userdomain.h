#ifndef GRAPHICALUSERDOMAIN_H
#define GRAPHICALUSERDOMAIN_H

#include <igraphicaluserinterface.h>
#include <idartsimulator.h>
#include <view.h>
#include <customdialog.h>
#include <QSystemTrayIcon>

class UserDomain : public QObject,
        public IGraphicalUserInterface<IDartSimulator>
{
    Q_OBJECT
public:
    UserDomain();

    virtual ~UserDomain();
    void setService(IDartSimulator *service);
    IDartSimulator *service();

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
