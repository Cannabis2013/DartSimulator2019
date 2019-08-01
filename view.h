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

public slots:
    virtual void setModels(QList<QTreeWidgetItem*> models,const QString &msg)=0;
    virtual void handleError(const QString &error)=0;
signals:
    void requestModel(const QUuid &id);
    void requestModels(const QUuid &parent = QUuid());


protected:
    void resizeEvent(QSize newSize);
};

#endif // VIEW_H
