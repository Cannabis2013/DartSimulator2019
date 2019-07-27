#ifndef POINTENTITY_H
#define POINTENTITY_H

#include <model.h>

class Point : public Model
{
public:
    Point(const QUuid &id,const int &point =0);

    int point() const;
    void setPoint(const int &point);
    void addPoint(const int &point);

    QUuid userId() const;
private:
    const QUuid _userId;
    int _point = 0;
};

#endif // POINTENTITY_H
