#include "mainapplication.h"

MainApplication::MainApplication()
{
    _dataModel = new DataModelManager();
    _remote = new RemoteModelManager(HOSTURL,USERCODE);
    _game = new GameManager();

    _remote->setTimeoutThreshold(10000);
    // Create/delete tournament
    connect(this,&IDartSimulator::createTournament,_dataModel ,&DataModelManager::createTournament);
    connect(this,&IDartSimulator::deleteTournament,_remote,&RemoteModelManager::remoteRemoveTournament);
    // Request models from remote

    connect(this,&IDartSimulator::tournament,_remote,&RemoteModelManager::remoteTournament);
    connect(this,&IDartSimulator::tournaments,_remote,&RemoteModelManager::remoteTournaments);

    connect(this,&IDartSimulator::round,_remote,&RemoteModelManager::remoteRound);
    connect(this,&IDartSimulator::rounds,_remote,&RemoteModelManager::remoteRounds);

    // GameManager
    connect(this,&IDartSimulator::appendNewRound,_game,&GameManager::initiateNewRound);
    connect(this,&IDartSimulator::submitPoint,_game,&GameManager::submitPoint);
    connect(_game,&GameManager::newRound,_dataModel ,&DataModelManager::remoteAppendRound);
    connect(_game,&GameManager::sendPointSubmit,_dataModel ,&DataModelManager::remoteAppendPoint);

    // Parse data from local context to remote context
    connect(_dataModel ,&DataModelManager::parseTournamentToRemote,_remote,&RemoteModelManager::createRemoteTournament);
    connect(_dataModel ,&DataModelManager::parseRoundToRemote,_remote,&RemoteModelManager::createRemoteRound);
    connect(_dataModel ,&DataModelManager::parsePointToRemote,_remote,&RemoteModelManager::submitRemotePoint);

    // Parse data from remote context to local context for processing
    connect(_remote,&RemoteModelManager::sendTournamentData,_dataModel ,&DataModelManager::tournamentFromJson);
    connect(_remote,&RemoteModelManager::sendAllTournamentsData,_dataModel ,&DataModelManager::tournamentsFromJson);

    // Return models to user domain
    connect(_dataModel ,&DataModelManager::parseTournamentToExternal,this,&IDartSimulator::sendModel);
    connect(_dataModel ,&DataModelManager::parseTournamentsToExternal,this,&IDartSimulator::sendModels);

    connect(_remote,&RemoteModelManager::sendStatusMsg,this,&IDartSimulator::externalPopupMessage);
    connect(_remote,&RemoteModelManager::sendNotification,this,&IDartSimulator::externalNotifyResponse);

    // Connection/request failed
    connect(_remote,&RemoteModelManager::sendErrorString,this,&IDartSimulator::externalRequestFailed);
}

