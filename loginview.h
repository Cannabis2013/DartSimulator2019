#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QWidget>
#include <view.h>

namespace Ui {
    class LoginView;
}

class LoginView : public View
{
    Q_OBJECT

public:
    explicit LoginView(QWidget *parent = nullptr);
    ~LoginView();

public slots:
    void handleError(const QString &error);
    void requestCompleted(const bool &status, const QTreeWidgetItem*model = nullptr);

    void updateState();

private:
    Ui::LoginView *ui;

};

#endif // LOGINVIEW_H
