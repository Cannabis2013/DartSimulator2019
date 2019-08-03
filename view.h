#ifndef VIEW_H
#define VIEW_H

#include <abstractframeimplementable.h>
#include <qlist.h>
#include <QTreeWidgetItem>
#include <quuid.h>

class View : public AbstractFrameImplementable
{
    Q_OBJECT
public:
    View(QWidget *parent = nullptr);

    QUuid classId() const;

    static void orderModels(QStringList &stringList, QList<QTreeWidgetItem*> &models,std::initializer_list<QString> list = std::initializer_list<QString>());

public slots:
    virtual void setModels(QList<QTreeWidgetItem*> models,const QStringList &headers,const QString &msg)=0;
    virtual void handleError(const QString &error)=0;

    virtual void updateState();

    virtual void requestCompleted();
signals:
    void requestModel(const QUuid &model);
    void requestModels(const QUuid &parent = QUuid());

    void requestDeleteModel(const QUuid &model, const QUuid &caller);

    void aboutToClose(const QUuid &id);


protected:
    void resizeEvent(QSize newSize);

    void closeEvent(QCloseEvent*e);

private:
    const QUuid _classId;
};

#endif // VIEW_H
