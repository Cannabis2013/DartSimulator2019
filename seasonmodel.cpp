#include "seasonmodel.h"

SeasonModel::SeasonModel(const QUuid &id):
    Model (ModelType::SeasonModel,id)
{

}

QString SeasonModel::name() const
{
    return _name;
}

void SeasonModel::setName(const QString &value)
{
    _name = value;
}

QDateTime SeasonModel::dateFinished() const
{
    return _dateFinished;
}

void SeasonModel::setDateFinished(const QDateTime &value)
{
    _dateFinished = value;
}
