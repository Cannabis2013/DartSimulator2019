#include "mainapplication.h"

MainApplication::MainApplication()
{
    _dataModelMng = new DataModelManager();
    _remoteMng = new RemoteModelManager(HOSTURL,USERCODE);
    _gameMng = new GameManager();

    _remoteMng->setTimeoutThreshold(10000);
    // Create/delete tournament
    connect(this,&IDartSimulator::createTournament,_dataModelMng ,&DataModelManager::createTournament);
    connect(this,&IDartSimulator::deleteTournament,_remoteMng,&RemoteModelManager::remoteRemoveTournament);

    // Request models from remote
    connect(this,&IDartSimulator::tournament,_remoteMng,&RemoteModelManager::remoteTournament);
    connect(this,&IDartSimulator::tournaments,_remoteMng,&RemoteModelManager::remoteTournaments);

    connect(this,&IDartSimulator::round,_remoteMng,&RemoteModelManager::remoteRound);
    connect(this,&IDartSimulator::rounds,_remoteMng,&RemoteModelManager::remoteRounds);

    // GameManager
    connect(this,&IDartSimulator::appendNewRound,_gameMng,&GameManager::initiateNewRound);
    connect(this,&IDartSimulator::submitPoint,_gameMng,&GameManager::submitPoint);
    connect(_gameMng,&GameManager::newRound,_dataModelMng ,&DataModelManager::remoteAppendRound);
    connect(_gameMng,&GameManager::sendPointSubmit,_dataModelMng ,&DataModelManager::remoteAppendPoint);

    // Parse data from local context to remote context
    connect(_dataModelMng ,&DataModelManager::parseTournamentToRemote,_remoteMng,&RemoteModelManager::createRemoteTournament);
    connect(_dataModelMng ,&DataModelManager::parseRoundToRemote,_remoteMng,&RemoteModelManager::createRemoteRound);
    connect(_dataModelMng ,&DataModelManager::parsePointToRemote,_remoteMng,&RemoteModelManager::submitRemotePoint);

    // Parse data from remote context to local context for processing
    connect(_remoteMng,&RemoteModelManager::sendTournamentData,_dataModelMng ,&DataModelManager::tournamentFromJson);
    connect(_remoteMng,&RemoteModelManager::sendAllTournamentsData,_dataModelMng ,&DataModelManager::tournamentsFromJson);

    // Return models to user domain
    connect(_dataModelMng ,&DataModelManager::parseTournamentToExternal,this,&IDartSimulator::sendModel);
    connect(_dataModelMng ,&DataModelManager::parseTournamentsToExternal,this,&IDartSimulator::sendModels);

    // Reply/update calling objects
    connect(_remoteMng,&RemoteModelManager::sendStatusMsg,this,&IDartSimulator::externalPopupMessage);
    connect(_remoteMng,&RemoteModelManager::sendNotification,_dataModelMng,&DataModelManager::ConvertreplyFromRemote);
    connect(_dataModelMng,&DataModelManager::parseReplyFromRemote,this,&IDartSimulator::externalNotifyResponse);

    // Connection/request failed
    connect(_remoteMng,&RemoteModelManager::sendErrorString,this,&IDartSimulator::externalRequestFailed);
}

