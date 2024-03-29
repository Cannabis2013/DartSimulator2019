#ifndef TOURNAMENTSELECTORVIEW_H
#define TOURNAMENTSELECTORVIEW_H

#include <QWidget>
#include <QTreeWidgetItem>
#include <qmessagebox.h>
#include <qstackedwidget.h>
#include <iostream>
#include <qpushbutton.h>
#include <QDateEdit>

#include <view.h>

#define LOCALDATEFORMAT "dd-MM-yyyy"

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
    void setModels(const QList<QTreeWidgetItem *> models, const QStringList &header, const QString &msg);

    virtual void handleError(const QString &error);
    virtual void updateState();

    virtual void requestCompleted(const bool &status,const QTreeWidgetItem* model = nullptr);

signals:
    void requestModel(const QUuid &model);
    void requestModels(const QUuid &parent = QUuid());
    void new_Tournament_Request(const QString &name,const QString &startDate, const QString &endDate);
    void requestDeleteModel(const QUuid &model, const QUuid &caller);
private slots:
    void show_Create_View();
    void show_Overview_View();
    void deleteModel();

    void send_New_Tournament();
private:

    void resetEditState();
    void disableAllButtons();
    void enableAllButtons();

    Ui::TournamentSelectorView *ui;

    QStackedWidget* sWidget;
    QTreeWidget* treeWidget;
    QPushButton* refreshButton, *deleteTournamentButton,*createTournamentButton;
    QLineEdit* titleSelector;
    QDateTimeEdit* startDateSelector, *endDateSelector;
};

#endif // TOURNAMENTSELECTORVIEW_H
