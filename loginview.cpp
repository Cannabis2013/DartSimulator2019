#include "loginview.h"
#include "ui_loginview.h"

LoginView::LoginView(QWidget *parent) :
    View(parent),
    ui(new Ui::LoginView)
{
    ui->setupUi(this);
}

LoginView::~LoginView()
{
    delete ui;
}

void LoginView::handleError(const QString &error)
{

}


void LoginView::requestCompleted()
{
}
