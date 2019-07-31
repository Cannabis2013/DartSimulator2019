#ifndef TOURNAMENTENTITY_H
#define TOURNAMENTENTITY_H

#include "model.h"

class Tournament : public Model
{
public:
    Tournament();

    QString name() const;
    void setName(const QString &name);

    int numberOfRounds() const;
    void setNumberOfRounds(int numberOfRounds);

    int numberOfUsersAssigned() const;

    QList<QUuid> users() const;
    void setUsers(const QList<QUuid> &users);

private:
    QString _name;
    int _numberOfRounds;

    QList<QUuid> _users;
};

#endif // TOURNAMENTENTITY_H
