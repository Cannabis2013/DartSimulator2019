#ifndef SEASONENTITY_H
#define SEASONENTITY_H

#include "modelentity.h"

class SeasonEntity : public ModelEntity
{
public:
    SeasonEntity();

    QString name() const;
    void setName(const QString &value);

    QDateTime dateFinished() const;
    void setDateFinished(const QDateTime &value);

    void addTournamentIdentity(const QUuid &entityIdentity);
    QList<QUuid> allTournamentIdentities() const{return allIdentifiers();}

    void toJSON();
private:
    QString _name;
    QDateTime _dateFinished;
};

#endif // SEASONENTITY_H
