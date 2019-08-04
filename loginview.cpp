#include "loginview.h"
#include "ui_loginview.h"

LoginView::LoginView(QWidget *parent) :
    View(parent),
    ui(new Ui::LoginView)
{
    ui->setupUi(this);

    setWidgetTitle("Login");
}

LoginView::~LoginView()
{
    delete ui;
}

void LoginView::handleError(const QString &error)
{
    Q_UNUSED(error);
}


void LoginView::requestCompleted(const bool &status, const QString &msg, const QTreeWidgetItem *model)
{
    if(!status)
    {
        clearCredentials();
        handleError("Username or password incorrect. Grap another beer and try again.");
    }
    else
    {
        // TODO: Do something for a succesfull login

    }
    Q_UNUSED(model);
}


void LoginView::updateState()
{
}

void LoginView::sendCredentials()
{
    QString userName = ui->userNameSelector->text(),
            password = ui->passwordSelector->text();

    emit verify(userName,password);
}

void LoginView::clearCredentials()
{
    ui->userNameSelector->clear();
    ui->passwordSelector->clear();
}
