#include "user.h"

User::User():
    Model(ModelType::UserModel)
{
}

QString User::forName() const
{
    return _forName;
}

void User::setForName(const QString &forName)
{
    _forName = forName;
}

QString User::getSurName() const
{
    return _surName;
}

void User::setSurName(const QString &value)
{
    _surName = value;
}

QString User::getEMail() const
{
    return _eMail;
}

void User::setEMail(const QString &value)
{
    _eMail = value;
}

User::UserRole User::getRole() const
{
    return _role;
}

void User::setRole(const UserRole &role)
{
    _role = role;
}
