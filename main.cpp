#include <QApplication>
#include <mainapplication.h>
#include <userdomain.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    IGraphicalUserInterface<IDartSimulator,View*>* ui = new UserDomain();
    ui->setService(new MainApplication());

    ui->setupLoginView(new LoginView,"Login");


    return a.exec();
}
