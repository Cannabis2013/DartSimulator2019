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

    int maxUsersAllowed() const;
    void setMaxUsersAllowed(int maxUsersAllowed);

    int numberOfUsersAssigned() const;

    QList<QUuid> users() const;
    void setUsers(const QList<QUuid> &users);

private:
    QString _name;
    int _numberOfRounds,_maxUsersAllowed;

    QList<QUuid> _users;
};

#endif // TOURNAMENTENTITY_H
