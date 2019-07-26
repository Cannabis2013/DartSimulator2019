#ifndef SEASONENTITY_H
#define SEASONENTITY_H

#include "model.h"

class SeasonModel : public Model
{
public:
    SeasonModel(const QUuid &id = QUuid());

    QString name() const;
    void setName(const QString &value);

    QDateTime dateFinished() const;
    void setDateFinished(const QDateTime &value);

private:
    QString _name;
    QDateTime _dateFinished;
};

#endif // SEASONENTITY_H
