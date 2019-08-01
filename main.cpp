#include <QApplication>
#include <iostream>
#include <mainapplication.h>
#include <tournamentselectorview.h>
#include <customdialog.h>
#include <qpointer.h>
#include <userdomain.h>

using namespace std;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UserDomain* ui = new UserDomain();
    ui->setService(new MainApplication());

    ui->setupTournamentView(new TournamentSelectorView,"Tournaments");


    return a.exec();
}
