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
    virtual void setModels(QList<QTreeWidgetItem*> models,const QStringList &headers,const QString &msg);
    virtual void handleError(const QString &error)=0;

    virtual void updateState();

    virtual void requestCompleted()=0;
signals:
    void requestModel(const QUuid &model);
    void requestModels(const QUuid &parent = QUuid());

    void requestDeleteModel(const QUuid &model, const QUuid &caller);

    void aboutToClose(const QUuid &id);

    void new_Tournament_Request(const QString &name,const QString &startDate, const QString &endDate);


protected:
    void resizeEvent(QSize newSize);

    void closeEvent(QCloseEvent*e);

private:
    const QUuid _classId;
};

#endif // VIEW_H
