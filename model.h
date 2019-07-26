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
 *  - Information of its type
 *  - Information of its time of incarceration
 */

class Model
{
public:
    enum ModelType {UserModel = 0x0020,
                    SeasonModel = 0x0040,
                    TournamentModel = 0x0060,
                    RoundModel = 0x0080,
                    PointModel = 0x0100};

    Model(ModelType type, QUuid id = QUuid());

    virtual ~Model();


    QUuid id() const;
    void setId(const QUuid &id);

    QDateTime dateCreated() const;

    ModelType type() const;

    QUuid parentId() const;
    void setParentId(const QUuid &parentId);

    bool operator ==(Model *comp);


    void setDateCreated(const QDateTime &dateCreated);
    const QList<QUuid> *allIdentifiers() const;

    void appendIdentifier(const QUuid id);
    void appendIdentifiers(const QList<QUuid> identities);

    void removeIdentifier(const QUuid &id);

protected:

private:

    QUuid _id;
    QUuid _parentId = QUuid();
    QDateTime _dateCreated;
    const ModelType _type;
    QList<QUuid> _subModels;
};

typedef Model::ModelType mType;

#endif // MODELENTITY_H
