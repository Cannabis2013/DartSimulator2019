#ifndef ROUNDENTITY_H
#define ROUNDENTITY_H

#include <model.h>

class RoundModel : public Model
{
public:
    RoundModel(int roundNumber, const QUuid &id = QUuid());

    QList<QUuid> allPointIdentities() const;
    void addPointIdentity(const QUuid &point);
    void addPointIdentities(const QList<QUuid> &pointIdentities);

    int roundNumber() const;

private:
    const int _roundNumber;
};

#endif // ROUNDENTITY_H
