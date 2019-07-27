#ifndef ROUNDENTITY_H
#define ROUNDENTITY_H

#include <model.h>
#include <point.h>

class Round : public Model
{
public:
    Round(int number);

    int roundNumber() const;

    void addPoint(Point* point);
    void removePoint(Point* point);

private:
    const int _roundNumber;
};

#endif // ROUNDENTITY_H
