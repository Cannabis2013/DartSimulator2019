#include "view.h"

View::View(QWidget* parent):
    AbstractFrameImplementable(parent),_classId(QUuid::createUuid())
{

}


void View::resizeEvent(QSize newSize)
{
    Q_UNUSED(newSize)};

void View::closeEvent(QCloseEvent *e)
{
    if(e->type() == QEvent::Close)
    {
        emit aboutToClose(_classId);
        deleteLater();
    }
}

QUuid View::classId() const
{
    return _classId;
}

void View::orderModels(QStringList &unorderedList, QList<QTreeWidgetItem *> &models, std::initializer_list<QString> list)
{
    if(list.size() == 0)
        throw "No order set!";

    QStringList orderedList = list;
    for (QString s : orderedList)
    {
        if(!unorderedList.contains(s))
            throw "Ordered list is not consistent with unordered list!";
    }

    for (int i = 0; i < orderedList.count(); ++i) {
        QString firstItem = orderedList.at(i);
        int index = unorderedList.indexOf(firstItem);

        if(index == i)
            continue;

        unorderedList.swapItemsAt(i,index);
        for (QTreeWidgetItem* item : models)
        {
            QString itemAtOrderedIndex = item->text(i);
            QString itemAtUnorderedIndex = item->text(index);
            item->setText(i,itemAtUnorderedIndex);
            item->setText(index,itemAtOrderedIndex);
        }
    }
}

void View::formatDate(const QStringList &header,QList<QTreeWidgetItem *> &models, const std::initializer_list<QString> &keys, const QString &dateFormat)
{
    const QStringList allKeys = keys;
    for (int i = 0; i < header.count(); ++i)
    {
        auto key = header.at(i);
        if(allKeys.contains(key))
        {
            for (auto model : models)
            {
                QString columnText = model->text(i);
                if(columnText == "Not defined")
                    continue;
                QDateTime dt = QDateTime::fromString(columnText,Qt::DateFormat::ISODate);
                QString newColumnText = dt.toString(dateFormat);
                model->setText(i,newColumnText);
            }
        }
    }
}

