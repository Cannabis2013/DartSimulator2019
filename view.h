#ifndef VIEW_H
#define VIEW_H

#include <abstractframeimplementable.h>
#include <qlist.h>
#include <QTreeWidgetItem>
#include <quuid.h>
#include <qdatetime.h>

class View : public AbstractFrameImplementable
{
    Q_OBJECT
public:
    View(QWidget *parent = nullptr);

    QUuid classId() const;

    static void orderModels(QStringList &stringList, QList<QTreeWidgetItem*> &models,std::initializer_list<QString> list = std::initializer_list<QString>());
    static void formatDate(const QStringList &header,QList<QTreeWidgetItem*> &models, const std::initializer_list<QString> &keys, const QString &dateFormat);
public slots:

    // Pure virtual methods
    virtual void handleError(const QString &error)=0;
    virtual void updateState()=0;
    virtual void handleReply(const bool &status, const QString &msg = QString(),const QTreeWidgetItem*model = nullptr)=0;
signals:
    void popupMessage(const QString &msg);
    void aboutToClose(const QUuid &id);

protected:
    void resizeEvent(QSize newSize);
    void closeEvent(QCloseEvent*e);

private:
    const QUuid _classId;
};

#endif // VIEW_H
