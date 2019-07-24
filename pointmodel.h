#ifndef POINTENTITY_H
#define POINTENTITY_H

#include <model.h>

class PointModel : public Model
{
public:
    PointModel(const QUuid &userId, const QUuid &id);

    int point() const;
    void setPoint(const int &point);
    void addPoint(const int &point);

    QUuid userId() const;
private:
    const QUuid _userId;
    int _point;
};

#endif // POINTENTITY_H
