#ifndef SEASONENTITY_H
#define SEASONENTITY_H

#include "model.h"
#include "tournament.h"

class Season : public Model
{
public:
    Season();

    QString name() const;
    void setName(const QString &value);

    QDateTime dateFinished() const;
    void setDateFinished(const QDateTime &value);

    void addTournament(Tournament* tournament);
    const QList<const Tournament*> *tournaments();
    void removeTournament(Tournament* tournament);

private:
    QString _name;
    QDateTime _dateFinished;
};

#endif // SEASONENTITY_H
