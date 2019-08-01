#ifndef TOURNAMENTSELECTORVIEW_H
#define TOURNAMENTSELECTORVIEW_H

#include <QWidget>
#include <QTreeWidgetItem>
#include <qmessagebox.h>

#include <view.h>

namespace Ui {
    class TournamentSelectorView;
}

class TournamentSelectorView : public View
{
    Q_OBJECT

public:
    explicit TournamentSelectorView(QWidget *parent = nullptr);
    ~TournamentSelectorView();

public slots:
    void setModels(QList<QTreeWidgetItem*> models,const QString &msg);
    void handleError(const QString &error);

private slots:
    void initiateRequest();
private:
    Ui::TournamentSelectorView *ui;

    QTreeWidget* treeWidget;
};

#endif // TOURNAMENTSELECTORVIEW_H
