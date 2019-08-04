#include "mainapplication.h"

MainApplication::MainApplication()
{
    _dataModelMng = new DataModelManager();
    _remoteMng = new RemoteModelManager(HOSTURL,USERCODE);
    _remoteUserMng = new RemoteUserManager(HOSTURL,USERCODE);
    _gameMng = new GameManager();

    _remoteMng->setTimeoutThreshold(-1);

    // Verify credentials

    connect(this,&IDartSimulator::parseCredentials,_remoteUserMng,&RemoteUserManager::verifyCredentials);

    // Return and process reply from remote user database

    connect(_remoteUserMng,&RemoteUserManager::notifyCallers,_dataModelMng,&DataModelManager::ConvertreplyFromRemote);
    connect(_dataModelMng,&DataModelManager::parseReplyFromRemote,this,&IDartSimulator::externalNotifyResponse);

    // Create/delete tournament
    connect(this,&IDartSimulator::parseTournament,_dataModelMng ,&DataModelManager::createTournament);
    connect(this,&IDartSimulator::removeTournament,_remoteMng,&RemoteModelManager::removeTournament);

    // Request models from remote
    connect(this,&IDartSimulator::tournament,_remoteMng,&RemoteModelManager::tournament);
    connect(this,&IDartSimulator::tournaments,_remoteMng,&RemoteModelManager::tournaments);

    connect(this,&IDartSimulator::round,_remoteMng,&RemoteModelManager::round);
    connect(this,&IDartSimulator::rounds,_remoteMng,&RemoteModelManager::rounds);

    // GameManager
    connect(this,&IDartSimulator::appendNewRound,_gameMng,&GameManager::initiateNewRound);
    connect(this,&IDartSimulator::submitPoint,_gameMng,&GameManager::submitPoint);
    connect(_gameMng,&GameManager::newRound,_dataModelMng ,&DataModelManager::remoteAppendRound);
    connect(_gameMng,&GameManager::sendPointSubmit,_dataModelMng ,&DataModelManager::remoteAppendPoint);

    // Parse data from local context to remote context
    connect(_dataModelMng ,&DataModelManager::parseTournamentToRemote,_remoteMng,&RemoteModelManager::addTournament);
    connect(_dataModelMng ,&DataModelManager::parseRoundToRemote,_remoteMng,&RemoteModelManager::addRound);
    connect(_dataModelMng ,&DataModelManager::parsePointToRemote,_remoteMng,&RemoteModelManager::addPoint);

    // Parse data from remote context to local context for processing
    connect(_remoteMng,&RemoteModelManager::sendTournament,_dataModelMng ,&DataModelManager::tournamentFromJson);
    connect(_remoteMng,&RemoteModelManager::sendTournaments,_dataModelMng ,&DataModelManager::tournamentsFromJson);

    // Return models to user domain
    connect(_dataModelMng ,&DataModelManager::parseTournamentToExternal,this,&IDartSimulator::sendModel);
    connect(_dataModelMng ,&DataModelManager::parseTournamentsToExternal,this,&IDartSimulator::sendModels);

    // Reply/update calling objects
    connect(_remoteMng,&RemoteModelManager::notifyCallers,_dataModelMng,&DataModelManager::ConvertreplyFromRemote);
    connect(_dataModelMng,&DataModelManager::parseReplyFromRemote,this,&IDartSimulator::externalNotifyResponse);
}

