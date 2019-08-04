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
    void requestCompleted(const bool &status, const QString &msg = QString(), const QTreeWidgetItem*model = nullptr);

    void updateState();

signals:
    void verify(const QString &username, const QString &password);

private slots:
    void sendCredentials();

private:
    void clearCredentials();

    Ui::LoginView *ui;

};

#endif // LOGINVIEW_H
