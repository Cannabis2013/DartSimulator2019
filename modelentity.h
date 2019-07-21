#ifndef MODELENTITY_H
#define MODELENTITY_H

#include <QUuid>
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

    ModelEntity(ModelType type);

    virtual ~ModelEntity();


    QUuid id() const;

    QDateTime dateCreated() const;

    ModelType type();

    QUuid parentId() const;
    QList<QUuid> allIdentifiers() const;
    void appendIdentifier(const QUuid id);

private:
    void setParentId(const QUuid &parentId);

    const QUuid _id;
    QUuid _parentId;
    const QDateTime _dateCreated;
    const ModelType _type;
    QList<QUuid> _subEntities;

    friend class CustomJsonAssembler;
};

#endif // MODELENTITY_H
