#include "pointmodel.h"

PointModel::PointModel(const QUuid &userId, const QUuid &id):
    Model (ModelType::PointModel,id),
    _userId(userId)
{
}

int PointModel::point() const
{
    return _point;
}

void PointModel::setPoint(const int &point)
{
    _point = point;
}

void PointModel::addPoint(const int &point)
{
    _point += point;
}

QUuid PointModel::userId() const
{
    return _userId;
}
