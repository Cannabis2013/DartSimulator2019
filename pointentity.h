#ifndef POINTENTITY_H
#define POINTENTITY_H

#include <modelentity.h>

class PointEntity : public ModelEntity
{
public:
    PointEntity(QUuid uId);

    int point() const;
    void setPoint(const int &point);
    void addPoint(const int &point);

    QUuid userId() const;
private:
    const QUuid _userId;
    int _point;
};

#endif // POINTENTITY_H
