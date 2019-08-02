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

public slots:
    virtual void setModels(QList<QTreeWidgetItem*> models,const QString &msg)=0;
    virtual void handleError(const QString &error)=0;

    virtual void updateModel();

    virtual void requestCompleted();
signals:
    void requestModel(const QUuid &model);
    void requestModels(const QUuid &parent = QUuid());

    void requestDeleteModel(const QUuid &model, const QUuid &callerId);

    void aboutToClose(const QUuid &id);


protected:
    void resizeEvent(QSize newSize);

    void closeEvent(QCloseEvent*e);

private:
    const QUuid _classId;
};

#endif // VIEW_H
