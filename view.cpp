#include "view.h"

View::View(QWidget* parent):
    AbstractFrameImplementable(parent),_classId(QUuid::createUuid())
{

}

void View::updateModel()
{

}

void View::requestCompleted()
{

}


void View::resizeEvent(QSize newSize)
{
}

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
