#ifndef GRAPHICALUSERDOMAIN_H
#define GRAPHICALUSERDOMAIN_H

#include <igraphicaluserinterface.h>
#include <idartsimulator.h>
#include <view.h>
#include <customdialog.h>

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
    void requestAllTournaments();
private:

    IDartSimulator* _service;
};

#endif // GRAPHICALUSERDOMAIN_H
