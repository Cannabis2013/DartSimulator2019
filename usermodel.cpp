#include "usermodel.h"

UserModel::UserModel():
    Model(ModelType::UserModel)
{
}

QString UserModel::forName() const
{
    return _forName;
}

void UserModel::setForName(const QString &forName)
{
    _forName = forName;
}

QString UserModel::getSurName() const
{
    return _surName;
}

void UserModel::setSurName(const QString &value)
{
    _surName = value;
}

QString UserModel::getEMail() const
{
    return _eMail;
}

void UserModel::setEMail(const QString &value)
{
    _eMail = value;
}

UserModel::UserRole UserModel::getRole() const
{
    return _role;
}

void UserModel::setRole(const UserRole &role)
{
    _role = role;
}


void UserModel::toJSON()
{
}
