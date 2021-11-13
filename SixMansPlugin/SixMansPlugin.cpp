//https://bakkesmodwiki.github.io/bakkesmod_api/
#include "pch.h"
#include "SixMansPlugin.h"

//https://bakkesmodwiki.github.io/bakkesmod_api/Classes/Wrappers/Modals/ModalWrapper/ for dealing with annoying popup

BAKKESMOD_PLUGIN(SixMansPlugin, "6Mans Plugin", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;


void SixMansPlugin::onLoad()
{
	_globalCvarManager = cvarManager;
	
	init();
	startServer();
}

void SixMansPlugin::onUnload()
{
	cvarManager->executeCommand("6mDisableServer");
	logt("Saving config...");
	cfg.saveConfig(Constants::PERSISTENT_CVARS, *cvarManager);
	logt("WARNING: If you manually unload the plugin, you'll have to restart the game to load it again.");
	logt("6Mans Plugin unloaded.");
	logt("\nEND OF LOG");
}

void SixMansPlugin::gotoPrivateMatch() {
	logt("[GoToPrivateMatch] Function called!");
	gpm_called = true;
	MatchmakingWrapper mw = gameWrapper->GetMatchmakingWrapper();
	if (!in_game && mw) [[likely]] {
		logt("[GoToPrivateMatch] Player ready!");
		if (match_info.event == 0) {
			logt("[GoToPrivateMatch] Event = create...");
			CustomMatchSettings cm;
			CustomMatchTeamSettings blue;
			CustomMatchTeamSettings red;

			cm.GameTags = match_info.gametags;
			cm.MapName = match_info.selected_map/*cvarManager->getCvar("6mMap").getStringValue()*/;
			cm.ServerName = match_info.name/*cvarManager->getCvar("6mServerName").getStringValue()*/;
			cm.Password = match_info.pass/*cvarManager->getCvar("6mServerPass").getStringValue()*/;
			cm.BlueTeamSettings = blue;
			cm.OrangeTeamSettings = red;
			cm.bClubServer = false;

			logt("[GoToPrivateMatch] Creating with name: " + cm.ServerName + ", pass: " + cm.Password + ", region: " + std::to_string((int)match_info.region));
			mw.CreatePrivateMatch(match_info.region, cm);
		}
		else if (match_info.event == 1) {
			logt("[GoToPrivateMatch] Event = join...");
			const std::string& thisname = match_info.name/*cvarManager->getCvar("6mServerName").getStringValue()*/;
			const std::string& thispass = /*"blah"*/match_info.pass/*cvarManager->getCvar("6mServerPass").getStringValue()*/;
			logt("[GoToPrivateMatch] Joining with name: " + match_info.name + " and pass: " + match_info.pass);
			mw.JoinPrivateMatch(thisname,thispass);
		}
		else [[unlikely]] logt("[GoToPrivateMatch] Invalid event code!");

	}
	else logt("[GoToPrivateMatch] Player not ready, is in game or mm is null!");

	if (is_enabled_autoretry) { //need to handle autoretry enabled but autojoin disabled, need to store if we've tried or not before starting
		logt("[Autoretry] Calling autoretry routine...");
		autoRetry();	
	}
	else {
		logt("[GoToPrivateMatch] Autoretry not enabled, showing retry toast if unsucessful...");
		//countdown = true;
	}

}

void SixMansPlugin::autoRetry() {
	//initCountdown();
	gameWrapper->SetTimeout([this](GameWrapper* gw) { //added fp/ct checks
		if ((in_game || can_manually_back_out) && !gameWrapper->IsInFreeplay() && !gameWrapper->IsInCustomTraining()) [[unlikely]] { /*countdown = false;*/ logt("[Autoretry] In game or player backed out, unwinding recursion..."); return; } //need to reset these vars after
		else  { 
			//countdown = true;
			
			logt("[Autoretry] Not in game, calling again..."); gotoPrivateMatch();
		} //CHANGED THIS 10/24 NEEDS BUILDING AND TESTING

		}, cvarManager->getCvar("6mTimeBeforeRetrying").getIntValue());
}

Region SixMansPlugin::getRegion(int region) {
	switch (region) {
		case 0: return Region::USE;
		case 1: return Region::EU;
		case 2: return Region::USW;
		case 3: return Region::ASC;
		case 4: return Region::ASM;
		case 5: return Region::JPN;
		case 6: return Region::ME;
		case 7: return Region::OCE;
		case 8: return Region::SAF;
		case 9: return Region::SAM;
		default: return Region::USE;
	}
}


void SixMansPlugin::logt(std::string text) {
	ls.open(logpath, std::ios::app);
	ls << text << std::endl;
	ls.close();

	cvarManager->log(text);
}

//FinishEvent() server wrapper,GetGameEvent() or NoReservationKick() player controller for leaving black screens?
//FIND FUNCTION FOR JOIN FAIL ERROR MODAL/INDICATOR, USEFUL FOR COUNTDOWN START
// 
//called once game is joined after creation
//"Function OnlineGamePrivateMatch_X.Joining.HandleJoinGameComplete"; //gets called on black screen/join failure as well, call isinonline game after to confirm
// "Function ProjectX.OnlineGameJoinGame_X.EventJoinGameComplete"; //doesnt get called on join failure, but gets called on black screen
// "Function TAGame.GFxData_SeasonReward_TA.HandleRewardUpdateOnGameJoin";
// 
// called on leave match
//"Function TAGame.GameEvent_Soccar_TA.Destroyed"
//"Function TAGame.GameEvent_Soccar_TA.CommitPlayerMatchData";
//
//called after error modal closed [create fail modal]
//Function TAGame.LocalPlayer_TA.CheckForRankedReconnect
//- Function TAGame.RankedReconnectSave_TA.RankedReconnectAvailable
//- Function TAGame.RankedReconnectSave_TA.RankedReconnectAvailable
//
//called on black screen
//Function ProjectX.OnlineGamePrivateMatch_X.OnPrivateMatchError
//-Function ProjectX.OnlineGameMatchmakingBase_X.EventFindGameError
//- Function TAGame.GFxData_OnlineMatchStatus_TA.SetError
//--Function TAGame.GFxData_OnlineMatchStatus_TA.OnSearchError
//Function TAGame.GFxData_ConnectionStats_TA.HandleGRISpawned
//Function ProjectX.GameInfo_X.DisconnectExistingPlayer
//Function TAGame.GFxData_ConnectionStats_TA.HandleControllerReceived
//Function TAGame.GFxShell_TA.ShowErrorMessage
//
// called on join error
// Function ProjectX.FindServerTask_X.HandleJoinMatchError
//-Function Core.AsyncTask.SetError
//Function ProjectX.OnlineGameServerBrowser_X.OnSearchError
//- Function ProjectX.OnlineGameServerBrowser_X.EventSearchError
//- Function TAGame.GFxData_ServerBrowser_TA.HandleSearchError
//