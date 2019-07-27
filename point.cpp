#include "point.h"

Point::Point(const QUuid &id, const int &point):
    Model (ModelType::PointModel),
    _userId(id),_point(point)
{}

int Point::point() const
{
    return _point;
}

void Point::setPoint(const int &point)
{
    _point = point;
}

void Point::addPoint(const int &point)
{
    _point += point;
}

QUuid Point::userId() const
{
    return _userId;
}
