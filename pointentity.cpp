#include "pointentity.h"

PointEntity::PointEntity(QUuid uId):
    ModelEntity (ModelType::PointModel),
    _userId(uId)
{
}

int PointEntity::point() const
{
    return _point;
}

void PointEntity::setPoint(const int &point)
{
    _point = point;
}

void PointEntity::addPoint(const int &point)
{
    _point += point;
}

QUuid PointEntity::userId() const
{
    return _userId;
}
