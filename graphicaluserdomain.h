#ifndef GRAPHICALUSERDOMAIN_H
#define GRAPHICALUSERDOMAIN_H

#include <igraphicaluserinterface.h>
#include <idartsimulator.h>
#include <abstractframeimplementable.h>
#include <customdialog.h>

class GraphicalUserDomain : public QObject,
        public IGraphicalUserInterface<IDartSimulator>
{
    Q_OBJECT
public:
    GraphicalUserDomain();

    virtual ~GraphicalUserDomain();
    void setService(IDartSimulator *service);
    IDartSimulator *service();
    void setupTournamentView(AbstractFrameImplementable* v, const QString &frameTitle);

private slots:
    void requestAllTournaments();
private:

    IDartSimulator* _service;
};

#endif // GRAPHICALUSERDOMAIN_H
