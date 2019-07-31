#include <QApplication>
#include <iostream>
#include <mainapplication.h>

#include "remotedatabasecontext.h"
#include <qtcpsocket.h>

using namespace std;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainApplication* m = new MainApplication();

    return a.exec();
}
