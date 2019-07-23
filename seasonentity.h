#ifndef SEASONENTITY_H
#define SEASONENTITY_H

#include "modelentity.h"

class SeasonEntity : public ModelEntity
{
public:
    SeasonEntity(const QUuid &id = QUuid());

    QString name() const;
    void setName(const QString &value);

    QDateTime dateFinished() const;
    void setDateFinished(const QDateTime &value);

    void addTournamentIdentity(const QUuid &entityIdentity);
    void addTournamentIdentities(const QList<QUuid> identities);
    QList<QUuid> allTournamentIdentities() const{return allIdentifiers();}

private:
    QString _name;
    QDateTime _dateFinished;
};

#endif // SEASONENTITY_H
