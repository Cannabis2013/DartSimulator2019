#ifndef TOURNAMENTSELECTORVIEW_H
#define TOURNAMENTSELECTORVIEW_H

#include <QWidget>
#include <QTreeWidgetItem>
#include <qmessagebox.h>
#include <qstackedwidget.h>
#include <iostream>


#include <view.h>

using namespace std;

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
    virtual void setModels(const QList<QTreeWidgetItem *> models, const QStringList &header, const QString &msg);
    virtual void handleError(const QString &error);
    virtual void updateState();
    virtual void requestCompleted();

private slots:
    void changeViewIndex();
    void deleteModel();
private:
    Ui::TournamentSelectorView *ui;

    QStackedWidget* stackedWidget;
    QTreeWidget* treeWidget;
};

#endif // TOURNAMENTSELECTORVIEW_H
