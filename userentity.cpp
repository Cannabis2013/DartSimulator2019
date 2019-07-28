#include "userentity.h"

UserEntity::UserEntity():
    Model(ModelType::UserModel)
{
}

QString UserEntity::forName() const
{
    return _forName;
}

void UserEntity::setForName(const QString &forName)
{
    _forName = forName;
}

QString UserEntity::getSurName() const
{
    return _surName;
}

void UserEntity::setSurName(const QString &value)
{
    _surName = value;
}

QString UserEntity::getEMail() const
{
    return _eMail;
}

void UserEntity::setEMail(const QString &value)
{
    _eMail = value;
}

UserEntity::UserRole UserEntity::getRole() const
{
    return _role;
}

void UserEntity::setRole(const UserRole &role)
{
    _role = role;
}
