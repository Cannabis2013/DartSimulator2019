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


void LoginView::requestCompleted(const bool &status, const QTreeWidgetItem *model)
{
    Q_UNUSED(status);
    Q_UNUSED(model);
}


void LoginView::updateState()
{
}
