#ifndef MODEL_H
#define MODEL_H

#include <quuid.h>
#include <qdatetime.h>

/*
 * This file holds all the temporary models that holds property values from user creation to json conversion
 */

class Model
{
public:
    Model():
        _id(QUuid::createUuid())
    {}

    QUuid id() const
    {
        return _id;
    }

private:
    const QUuid _id;
};

class Tournament : public Model
{
public:
    Tournament():
        Model(){}

    QString name() const
    {
        return _name;
    }

    void setName(const QString &name)
    {
        _name = name;
    }

    QDateTime startDate() const
    {
        return _startDate;
    }
    void setStartDate(const QDateTime &startDate)
    {
        _startDate = startDate;
    }

    QDateTime endDate() const
    {
        return _endDate;
    }
    void setEndDate(const QDateTime &endDate)
    {
        _endDate = endDate;
    }

private:
    QString _name;
    QDateTime _startDate,_endDate;
};

class Round : public Model
{
public:
    Round():Model() {}

    QUuid parent() const
    {
        return _parent;
    }

    void setParent(const QUuid &parent)
    {
        _parent = parent;
    }

    int roundIndex() const
    {
        return _roundIndex;
    }

    void setRoundIndex(int roundIndex)
    {
        _roundIndex = roundIndex;
    }

private:
    QUuid _parent;
    int _roundIndex;
};

class Point : public Model
{
public:

    QUuid userId() const
    {
        return _userId;
    }
    void setUserId(const QUuid &userId)
    {
        _userId = userId;
    }

    quint32 point() const
    {
        return _point;
    }
    void setPoint(const quint32 &point)
    {
        _point = point;
    }

    QUuid parent() const
    {
        return _parent;
    }
    void setParent(const QUuid &parent)
    {
        _parent = parent;
    }

private:
    QUuid _parent;
    QUuid _userId;
    quint32 _point;
};

#endif // MODEL_H
