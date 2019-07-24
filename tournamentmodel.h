#ifndef TOURNAMENTENTITY_H
#define TOURNAMENTENTITY_H

#include "model.h"

class TournamentModel : public Model
{
public:
    TournamentModel(const QUuid &id = QUuid());


    void toJSON();

    QString name() const;
    void setName(const QString &name);

    int numberOfRounds() const;
    void setNumberOfRounds(int numberOfRounds);

    QDateTime dateFinished() const;
    void setDateFinished(const QDateTime &dateFinished);

    int maxUsersAllowed() const;
    void setMaxUsersAllowed(int maxUsersAllowed);

    QList<QUuid> allRoundIdentities() const;
    void addRoundIdentities(const QList<QUuid> &identities);

private:
    QString _name;
    int _numberOfRounds,_maxUsersAllowed;
    QDateTime _dateFinished;
};

#endif // TOURNAMENTENTITY_H
