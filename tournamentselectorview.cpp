#include "tournamentselectorview.h"
#include "ui_tournamentselectorview.h"

TournamentSelectorView::TournamentSelectorView(QWidget *parent) :
    View(parent),
    ui(new Ui::TournamentSelectorView)
{
    ui->setupUi(this);

    treeWidget = ui->treeWidget;
    stackedWidget = ui->stackedWidget;
}

TournamentSelectorView::~TournamentSelectorView()
{
    delete ui;
}

void TournamentSelectorView::setModels(QList<QTreeWidgetItem *> models, const QString &msg)
{
    Q_UNUSED(msg);
    treeWidget->clear();
    treeWidget->addTopLevelItems(models);
    ui->RefreshButton->setDisabled(false);
}

void TournamentSelectorView::updateModel()
{
    treeWidget->clear();
    ui->RefreshButton->setDisabled(true);
    emit requestModels();
}

void TournamentSelectorView::requestCompleted()
{
    updateModel();
}

void TournamentSelectorView::changeViewIndex()
{
    stackedWidget->setCurrentIndex(1);
}

void TournamentSelectorView::deleteModel()
{
    QString string = treeWidget->currentItem()->text(3);
    QUuid id = QUuid::fromString(string);

    emit requestDeleteModel(id);
}


void TournamentSelectorView::handleError(const QString &error)
{
    QMessageBox msg;
    msg.setIcon(QMessageBox::Critical);
    msg.setText(error);

    msg.exec();
    ui->RefreshButton->setDisabled(false);
}
