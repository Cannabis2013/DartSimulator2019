#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QWidget>
#include <view.h>

namespace Ui {
    class LoginView;
}

#define TEST_MODE

class LoginView : public View
{
    Q_OBJECT

public:
    explicit LoginView(QWidget *parent = nullptr);
    ~LoginView();

public slots:
    void handleError(const QString &error);
    void handleReply(const bool &status, const QString &msg = QString(), const QTreeWidgetItem*model = nullptr);

    void updateState();

signals:
    void verify(const QString &username, const QString &password);
    void success();

private slots:
    void sendCredentials();

private:
    void clearCredentials();

    Ui::LoginView *ui;

};

#endif // LOGINVIEW_H
