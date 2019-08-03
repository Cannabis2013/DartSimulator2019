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

void TournamentSelectorView::setModels(const QList<QTreeWidgetItem *> models, const QStringList &header, const QString &msg)
{
    Q_UNUSED(msg);

    QStringList headerLabels = header;
    QList<QTreeWidgetItem*> items = models;
    try {
        View::orderModels(headerLabels,items,{"Name","StartDateTime","EndDateTime","Created","Updated","Id"});
    } catch (const char* msg) {

    }

    treeWidget->clear();
    int columns = header.count();
    treeWidget->setColumnCount(columns);
    treeWidget->setHeaderLabels(headerLabels);
    treeWidget->addTopLevelItems(items);
    ui->RefreshButton->setDisabled(false);
}

void TournamentSelectorView::updateState()
{
    ui->RefreshButton->setDisabled(true);
    emit requestModels();
}

void TournamentSelectorView::requestCompleted()
{
    ui->DeleteButton->setDisabled(false);
    updateState();
}

void TournamentSelectorView::changeViewIndex()
{
    stackedWidget->setCurrentIndex(1);
}

void TournamentSelectorView::deleteModel()
{
    if(treeWidget->currentItem() == nullptr)
        return;
    QString string = treeWidget->currentItem()->text(5);
    QUuid id = QUuid::fromString(string), caller = this->classId();
    ui->DeleteButton->setDisabled(true);
    emit requestDeleteModel(id,caller);
}


void TournamentSelectorView::handleError(const QString &error)
{
    QMessageBox msg;
    msg.setIcon(QMessageBox::Critical);
    msg.setText(error);

    msg.exec();
    ui->RefreshButton->setDisabled(false);
}
