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
	LOG("Saving config...");
	saveConfig(PERSISTENT_CVARS);
	LOG("WARNING: If you manually unload the plugin, you'll have to restart the game to load it again.");
	cvarManager->log("6Mans Plugin unloaded.");
}

void SixMansPlugin::gotoPrivateMatch() {
	cvarManager->log("[GoToPrivateMatch] called.");
	gpm_called = true;
	MatchmakingWrapper mw = gameWrapper->GetMatchmakingWrapper();
		if(!in_game && mw) [[likely]] { 
			if (event_code == 0) [[unlikely]] {
				CustomMatchSettings cm;
				CustomMatchTeamSettings blue;
				CustomMatchTeamSettings red;

				cm.GameTags = gametags;
				cm.MapName = cvarManager->getCvar("6mMap").getStringValue();
				cm.ServerName = cvarManager->getCvar("6mServerName").getStringValue();
				cm.Password = cvarManager->getCvar("6mServerPass").getStringValue();
				cm.BlueTeamSettings = blue;
				cm.OrangeTeamSettings = red;
				cm.bClubServer = false;

				cvarManager->log("[GoToPrivateMatch] Creating with name: " + cm.ServerName + "and pass: " + cm.Password);
				mw.CreatePrivateMatch(region, cm);
			}
			else if (event_code == 1) [[likely]] {
				const std::string thisname = cvarManager->getCvar("6mServerName").getStringValue();
				const std::string thispass = cvarManager->getCvar("6mServerPass").getStringValue();
				cvarManager->log("[GoToPrivateMatch] Joining with name: " + thisname + "and pass: " + thispass);
				mw.JoinPrivateMatch(thisname,thispass);
			}
			else [[unlikely]] cvarManager->log("[GoToPrivateMatch] Invalid event code!");

		}
		if (is_enabled_autoretry) [[likely]] { //need to handle autoretry enabled but autojoin disabled, need to store if we've tried or not before starting
			LOG("[Autoretry] Beginning autoretry routine...");
			autoRetry();	
		}
		else {
			countdown = true;
		}

}

void SixMansPlugin::autoRetry() {
	initCountdown();
	gameWrapper->SetTimeout([this](GameWrapper* gw) {
		if (in_game || can_manually_back_out) [[unlikely]] { countdown = false; LOG("[Autoretry] In game or player backed out, unwinding recursion..."); return; } //need to reset these vars after
		else [[likely]] { 
			countdown = true;
			
			LOG("[Autoretry] Not in game, calling again..."); gotoPrivateMatch();
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
	SYSTEMTIME t = {0};
	GetLocalTime(&t);
	std::ostringstream ss;
	ss << gameWrapper->GetDataFolder().string() << "\\" << t.wMonth << "-" << t.wDay << "-" << t.wYear << "_6mLog.log";
	os.open(ss.str(), std::ios::app);
	os << text << std::endl;
	os.close();

	LOG("[Logger]" + text);
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