//https://bakkesmodwiki.github.io/bakkesmod_api/
#include "pch.h"
#include "SixMansPlugin.h"

//https://bakkesmodwiki.github.io/bakkesmod_api/Classes/Wrappers/Modals/ModalWrapper/ for dealing with annoying popup

BAKKESMOD_PLUGIN(SixMansPlugin, "6Mans Plugin", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;


void SixMansPlugin::onLoad()
{
	_globalCvarManager = cvarManager;
	
	initCvars();
	startServer();
	
}

void SixMansPlugin::onUnload()
{
	cvarManager->executeCommand("6mDisableServer");
	cvarManager->getCvar("6mEndMonitor").setValue("1");
	cvarManager->log("6Mans Plugin unloaded.");
}

void SixMansPlugin::gotoPrivateMatch() {
	cvarManager->log("[gotoPrivateMatch] called.");
	MatchmakingWrapper mw = gameWrapper->GetMatchmakingWrapper();
		if(!in_game && mw) { 
			if (event_code == 0) {
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

				cvarManager->log("[gotoPrivateMatch] Creating with name: " + cm.ServerName + "and pass: " + cm.Password);
				mw.CreatePrivateMatch(region, cm);
			}
			else if (event_code == 1) {
				cvarManager->log("[gotoPrivateMatch] Joining with name: " + name + "and pass: " + pass);
				mw.JoinPrivateMatch(cvarManager->getCvar("6mServerName").getStringValue(), cvarManager->getCvar("6mServerPass").getStringValue());
			}
			else cvarManager->log("[gotoPrivateMatch] Invalid event code!");		
		}
		if (is_enabled_autoretry) {
			gameWrapper->SetTimeout([this](GameWrapper* gw) {
				if (!in_game && !cvarManager->getCvar("6mEndRecursiveJoin").getBoolValue()) { cvarManager->log("[gotoPrivateMatch] Checking..."); gotoPrivateMatch(); return; }
				else { cvarManager->log("[gotoPrivateMatch] Success."); return; }

				}, cvarManager->getCvar("6mTimeBeforeRetrying").getIntValue());
				
		}

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

void SixMansPlugin::monitorOnlineState() {
	monitor = std::thread([this]() {
		while (!cvarManager->getCvar("6mEndMonitor").getBoolValue()) {
			if (!gameWrapper->IsInOnlineGame()) {
				cvarManager->log("[Monitor] not in online game...");
				in_game = false;
			}
			else {
				cvarManager->log("[Monitor] detected online game!");
				cvarManager->log("[Monitor] terminating monitor...");
				//cvarManager->getCvar("6mEndMonitor").setValue("0");
				in_game = true;
				return;
			}
			std::this_thread::sleep_for(std::chrono::seconds(2));
		}
		cvarManager->getCvar("6mEndMonitor").setValue("0");
		cvarManager->log("[Monitor] terminating monitor...");
		return;
		});
	monitor.detach();
}

//// Function TAGame.GFxData_PrivateMatch_TA.StartSearch
//struct UGFxData_PrivateMatch_TA_StartSearch_Params
//{
//};
//
//// Function TAGame.GFxData_PrivateMatch_TA.StartClubSearch
//struct UGFxData_PrivateMatch_TA_StartClubSearch_Params
//{
//};
//
//// Function TAGame.GFxData_PrivateMatch_TA.CreateRandom16CharGuidString
//struct UGFxData_PrivateMatch_TA_CreateRandom16CharGuidString_Params
//{
//	struct FString                                     ReturnValue;                                               // (Parm, OutParm, ReturnParm, NeedCtorLink)
//};
//
//// Function TAGame.GFxData_PrivateMatch_TA.CancelSearch
//struct UGFxData_PrivateMatch_TA_CancelSearch_Params
//{
//};
//
//// Function TAGame.GFxData_PrivateMatch_TA.SetRegionSelection
//struct UGFxData_PrivateMatch_TA_SetRegionSelection_Params
//{
//	int                                                Row;                                                       // (Parm)
//	bool                                               bSelected;                                                 // (Parm)
//};
//
//// Function TAGame.GFxData_PrivateMatch_TA.GetPreferredRegion
//struct UGFxData_PrivateMatch_TA_GetPreferredRegion_Params
//{
//	struct FString                                     ReturnValue;                                               // (Parm, OutParm, ReturnParm, NeedCtorLink)
//};
//
//// Function TAGame.GFxData_PrivateMatch_TA.HandleRegionsSynced
//struct UGFxData_PrivateMatch_TA_HandleRegionsSynced_Params
//{
//	class UGFxData_Regions_TA* RegionsData;                                               // (Parm)
//	TArray<struct FString>                             ArrayInitializer_A6D087254D424B72E4032488012D54CC;         // (Const, OutParm, NeedCtorLink)
//	struct FGFxRegion                                  StructInitializer_F07394B84F162393EA2E36B1237F899D;        // (Const, OutParm, NeedCtorLink)
//};
//
//// Function TAGame.GFxData_PrivateMatch_TA.SetPublic
//struct UGFxData_PrivateMatch_TA_SetPublic_Params
//{
//	bool                                               bValue;                                                    // (Parm)
//};
//
//// Function TAGame.GFxData_PrivateMatch_TA.SetPassword
//struct UGFxData_PrivateMatch_TA_SetPassword_Params
//{
//	struct FString                                     InPassword;                                                // (Parm, NeedCtorLink)
//};
//
//// Function TAGame.GFxData_PrivateMatch_TA.SetServerName
//struct UGFxData_PrivateMatch_TA_SetServerName_Params
//{
//	struct FString                                     InServerName;                                              // (Parm, NeedCtorLink)
//};
//
//// Function TAGame.GFxData_PrivateMatch_TA.SetSelectedMaxPlayerCount
//struct UGFxData_PrivateMatch_TA_SetSelectedMaxPlayerCount_Params
//{
//	int                                                MaxPlayerCount;                                            // (Parm)
//};
//
//// Function TAGame.GFxData_PrivateMatch_TA.GetCustomMatchRegion
//struct UGFxData_PrivateMatch_TA_GetCustomMatchRegion_Params
//{
//	struct FString                                     ReturnValue;                                               // (Parm, OutParm, ReturnParm, NeedCtorLink)
//};
//
//// Function TAGame.GFxData_PrivateMatch_TA.SetCustomMatchSettings
//struct UGFxData_PrivateMatch_TA_SetCustomMatchSettings_Params
//{
//	struct U_Types_X_FCustomMatchSettings              InSettings;                                                // (Const, Parm, OutParm, NeedCtorLink)
//};
//
//// Function TAGame.GFxData_PrivateMatch_TA.GetCustomMatchSettings
//struct UGFxData_PrivateMatch_TA_GetCustomMatchSettings_Params
//{
//	struct U_Types_X_FCustomMatchSettings              ReturnValue;                                               // (Parm, OutParm, ReturnParm, NeedCtorLink)
//};
//
//// Function TAGame.GFxData_PrivateMatch_TA.OnShellSet
//struct UGFxData_PrivateMatch_TA_OnShellSet_Params
//{
//};