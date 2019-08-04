#include <QApplication>
#include <mainapplication.h>
#include <userdomain.h>

#include <outputmanager.h>
#include <customjsonassembler.h>
#include <dbmanager.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    IGraphicalUserInterface<IDartSimulator>* ui = new UserDomain();
    ui->setService(new MainApplication());

    ui->setupTournamentView();

    return a.exec();
}
