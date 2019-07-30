#ifndef USERENTITY_H
#define USERENTITY_H

#include "model.h"

class User : public Model
{
public:
    User();

    enum UserRole{Super, regular};

    QString forName() const;
    void setForName(const QString &forName);

    QString getSurName() const;
    void setSurName(const QString &value);

    QString getEMail() const;
    void setEMail(const QString &value);

    UserRole getRole() const;
    void setRole(const UserRole &role);

private:
    QString _forName, _surName, _eMail;
    UserRole _role;

};

#endif // USERENTITY_H