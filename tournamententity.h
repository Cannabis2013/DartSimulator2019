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

    QDate dateFinished() const;
    void setDateFinished(const QDate &dateFinished);

    int maxUsersAllowed() const;
    void setMaxUsersAllowed(int maxUsersAllowed);

private:
    QString _name;
    int _numberOfRounds,_maxUsersAllowed;
    QDate _dateFinished;
};

#endif // TOURNAMENTENTITY_H
