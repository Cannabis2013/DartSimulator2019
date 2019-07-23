#ifndef MODELENTITY_H
#define MODELENTITY_H

#include <QUuid>
#include <qhash.h>
#include <QString>
#include <QDateTime>


using namespace std;

/*
 * ModelEntity contains the following properties:
 *  - Identification
 *  - Parent identification
 *  - Information regard its type
 *  - Information regard its time of its incarceration
 */

class ModelEntity
{
public:
    enum ModelType {UserModel = 0x0020,
                    SeasonModel = 0x0040,
                    TournamentModel = 0x0060,
                    RoundModel = 0x0080,
                    PointModel = 0x0100};

    ModelEntity(ModelType type, QUuid id = QUuid());

    virtual ~ModelEntity();


    QUuid id() const;
    void setId(const QUuid &id);

    QDateTime dateCreated() const;

    ModelType type();

    QUuid parentId() const;
    void setParentId(const QUuid &parentId);

    bool operator ==(ModelEntity *comp);


    void setDateCreated(const QDateTime &dateCreated);

protected:
    QList<QUuid> allIdentifiers() const;
    void appendIdentifier(const QUuid id);
    void appendIdentifiers(const QList<QUuid> identities);

private:

    QUuid _id;
    QUuid _parentId = QUuid();
    QDateTime _dateCreated;
    const ModelType _type;
    QList<QUuid> _subEntities;

    friend class CustomJsonAssembler;
};

typedef ModelEntity::ModelType mType;

#endif // MODELENTITY_H
