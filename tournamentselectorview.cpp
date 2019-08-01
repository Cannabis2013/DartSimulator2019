#include "tournamentselectorview.h"
#include "ui_tournamentselectorview.h"

TournamentSelectorView::TournamentSelectorView(QWidget *parent) :
    AbstractFrameImplementable(parent),
    ui(new Ui::TournamentSelectorView)
{
    ui->setupUi(this);

    treeWidget = ui->treeWidget;
}

TournamentSelectorView::~TournamentSelectorView()
{
    delete ui;
}

void TournamentSelectorView::handleReply(const QList<QTreeWidgetItem *> &items, const QString &logMessage)
{
    Q_UNUSED(logMessage);
    treeWidget->clear();
    treeWidget->addTopLevelItems(items);
    ui->RefreshButton->setDisabled(false);
}


void TournamentSelectorView::resizeEvent(QSize newSize)
{
}

void TournamentSelectorView::initiateRequest()
{
    ui->RefreshButton->setDisabled(true);
    emit requestTournaments();
}
