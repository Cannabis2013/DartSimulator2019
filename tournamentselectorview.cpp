#include "tournamentselectorview.h"
#include "ui_tournamentselectorview.h"

TournamentSelectorView::TournamentSelectorView(QWidget *parent) :
    View(parent),
    ui(new Ui::TournamentSelectorView)
{
    ui->setupUi(this);

    treeWidget = ui->treeWidget;
    sWidget = ui->stackedWidget;

    titleSelector = ui->titleSelector;
    startDateSelector = ui->startDateSelector;
    endDateSelector = ui->endDateSelector;

    refreshButton = ui->RefreshButton;
    createTournamentButton = ui->CreateButton;
    deleteTournamentButton = ui->DeleteButton;
    resetEditState();
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
        Q_UNUSED(msg);
    }
    View::formatDate(headerLabels,items,{"StartDateTime","EndDateTime"},"dd-MM-yyyy");

    treeWidget->clear();
    int columns = header.count();
    treeWidget->setColumnCount(columns);
    treeWidget->setHeaderLabels(headerLabels);
    treeWidget->addTopLevelItems(items);

    enableAllButtons();
}

void TournamentSelectorView::updateState()
{
    disableAllButtons();
    emit requestModels();
}

void TournamentSelectorView::requestCompleted()
{
    enableAllButtons();
    updateState();
}

void TournamentSelectorView::show_Create_View()
{
    sWidget->setCurrentIndex(1);
}

void TournamentSelectorView::show_Overview_View()
{
    sWidget->setCurrentIndex(0);
    resetEditState();
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

void TournamentSelectorView::send_New_Tournament()
{
    QString name = titleSelector->text();
    QString startDate = startDateSelector->dateTime().toString();
    QString endDate = endDateSelector->dateTime().toString();

    if(!name.isEmpty())
        emit new_Tournament_Request(name,startDate,endDate);

    show_Overview_View();
}

void TournamentSelectorView::resetEditState()
{
    titleSelector->clear();
    startDateSelector->setDateTime(QDateTime::currentDateTime());
    endDateSelector->setDateTime(QDateTime::currentDateTime());
}

void TournamentSelectorView::disableAllButtons()
{
    refreshButton->setDisabled(true);
    createTournamentButton->setDisabled(true);
    deleteTournamentButton->setDisabled(true);
}

void TournamentSelectorView::enableAllButtons()
{
    refreshButton->setDisabled(false);
    createTournamentButton->setDisabled(false);
    deleteTournamentButton->setDisabled(false);
}


void TournamentSelectorView::handleError(const QString &error)
{
    QMessageBox msg;
    msg.setIcon(QMessageBox::Critical);
    msg.setText(error);

    msg.exec();
    ui->RefreshButton->setDisabled(false);
}
