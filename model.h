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

class Model
{
public:
    enum ModelType {UserModel = 0x0020,
                    SeasonModel = 0x0040,
                    TournamentModel = 0x0060,
                    RoundModel = 0x0080,
                    PointModel = 0x0100};

    Model(ModelType type);

    virtual ~Model();

    QUuid id() const;

    QDateTime dateCreated() const;

    ModelType type() const;

    Model* parent() const;
    void setParent(Model *parent);

    const QList<const Model*> *childs() const;

protected:
    void addChild(Model* child);
    void replaceChild(const int &index, Model* child);
    QList<Model *> children() const;
    int numberOfChilds() const;
    void removeChild(Model* child);

    bool isRoot() const;

private:
    const QUuid _id;
    Model* _parent;
    const QDateTime _dateCreated;
    const ModelType _type;
    QList<Model*> _children;

    friend class CustomJsonAssembler;
    friend class ModelDB;
};

#endif // MODELENTITY_H
