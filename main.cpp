#include <QApplication>
#include <mainapplication.h>
#include <userdomain.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    IGraphicalUserInterface<IDartSimulator>* ui = new UserDomain();
    ui->setService(new MainApplication());

    ui->setupLoginView();

    return a.exec();
}
