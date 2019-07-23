#ifndef TOURNAMENTENTITY_H
#define TOURNAMENTENTITY_H

#include "modelentity.h"

class TournamentEntity : public ModelEntity
{
public:
    TournamentEntity();


    void toJSON();

    QString name() const;
    void setName(const QString &name);

    int numberOfRounds() const;
    void setNumberOfRounds(int numberOfRounds);

    QDateTime dateFinished() const;
    void setDateFinished(const QDateTime &dateFinished);

    int maxUsersAllowed() const;
    void setMaxUsersAllowed(int maxUsersAllowed);

    QList<QUuid> allRoundIdentities();

private:
    QString _name;
    int _numberOfRounds,_maxUsersAllowed;
    QDateTime _dateFinished;
};

#endif // TOURNAMENTENTITY_H
