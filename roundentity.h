#ifndef ROUNDENTITY_H
#define ROUNDENTITY_H

#include <modelentity.h>

class RoundEntity : public ModelEntity
{
public:
    RoundEntity(int number);

    int roundNumber() const;

private:
    const int _roundNumber;
};

#endif // ROUNDENTITY_H
