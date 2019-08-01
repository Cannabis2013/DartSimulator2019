#include <QApplication>
#include <iostream>
#include <mainapplication.h>
#include <tournamentselectorview.h>
#include <customdialog.h>
#include <qpointer.h>
#include <graphicaluserdomain.h>

using namespace std;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GraphicalUserDomain* ui = new GraphicalUserDomain();
    ui->setService(new MainApplication());

    ui->setupTournamentView(new TournamentSelectorView,"Tournaments");


    return a.exec();
}
