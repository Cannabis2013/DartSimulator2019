#ifndef TOURNAMENTSELECTORVIEW_H
#define TOURNAMENTSELECTORVIEW_H

#include <QWidget>
#include <QTreeWidgetItem>

#include <abstractframeimplementable.h>

namespace Ui {
    class TournamentSelectorView;
}

class TournamentSelectorView : public AbstractFrameImplementable
{
    Q_OBJECT

public:
    explicit TournamentSelectorView(QWidget *parent = nullptr);
    ~TournamentSelectorView();

public slots:
    void handleReply(const QList<QTreeWidgetItem*> &items,const QString &logMessage);
signals:
    void requestTournaments();

protected:
    void resizeEvent(QSize newSize);
private slots:
    void initiateRequest();
private:
    Ui::TournamentSelectorView *ui;

    QTreeWidget* treeWidget;

};

#endif // TOURNAMENTSELECTORVIEW_H
