#ifndef MODEL_H
#define MODEL_H

#include <quuid.h>

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
    Tournament():
        Model()
    {}

private:
    QString _name;

};

#endif // MODEL_H
