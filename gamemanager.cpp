#include "gamemanager.h"

GameManager::GameManager(IDatabaseManager<Model, Model::ModelType> *database):
    db(database)
{
}

QUuid GameManager::currentTournament() const
{
    return _currentTournament;
}

void GameManager::setCurrentTournament(const QUuid &value)
{
    _currentTournament = value;
}

QUuid GameManager::currentRound() const
{
    return db->all_Children_Of(currentTournament(),Model::RoundModel).at(_HEAD)->id();
}

int GameManager::totalPoints(const QUuid &user)
{
    int result = 0;
    QList<const Point*> allPoints = points();
    for (const Point* point : allPoints)
    {
        if(point->userId() == user || user == QUuid())
            result += point->point();
    }

    return result;
}

const QList<const Point *> GameManager::points()
{
    QList<const Model*> list = db->all_Children_Of(currentTournament(),Model::PointModel);
    QList<const Point*> result;

    for (const Model* m : list)
        result << dynamic_cast<const Point*>(m);

    return result;
}

bool GameManager::isDetached() const
{
    const Model* m = db->model(currentTournament());
    int indexOfLastElement = m->childs().count() -1;

    return _HEAD != indexOfLastElement;
}

void GameManager::initiateNext()
{
    const QUuid round = appendNextRound();
    Q_UNUSED(round);
}

void GameManager::addPoint(const int point, const QUuid &user)
{
    db->addSubModel(new Point(user,point),currentRound());
}

QUuid GameManager::appendNextRound()
{
    int roundNumber = db->all_Children_Of(currentTournament(),Model::RoundModel).count();
    Round* r = new Round(roundNumber);
    db->addSubModel(r,currentTournament());
    _HEAD = db->all_Children_Of(currentTournament(),Model::RoundModel).count() - 1;
    return r->id();
}
