//https://bakkesmodwiki.github.io/bakkesmod_api/
#include "pch.h"
#include "MJ.h"

//https://bakkesmodwiki.github.io/bakkesmod_api/Classes/Wrappers/Modals/ModalWrapper/ for dealing with annoying popup

BAKKESMOD_PLUGIN(MJ, "Match Joiner", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;


void MJ::onLoad()
{
	_globalCvarManager = cvarManager;
	initCvars();
	startServer();
}

void MJ::onUnload()
{
	cvarManager->executeCommand("MJDisableServer");
	cvarManager->log("Match joiner unloaded.");
}

//need to poll isinonlinegame more
void MJ::gotoPrivateMatch() {
	cvarManager->log("[gotoPrivateMatch] called.");
	
		if(!gameWrapper->IsInOnlineGame() && mw) { 

			if (event_code == 0) {
				CustomMatchSettings cm;
				CustomMatchTeamSettings blue;
				CustomMatchTeamSettings red;

				cm.GameTags = gametags;
				cm.MapName = selected_map; //this will need to be bound to map cvar/array
				cm.ServerName = name;
				cm.Password = pass;
				cm.BlueTeamSettings = blue;
				cm.OrangeTeamSettings = red;
				cm.bClubServer = false;

				cvarManager->log("[gotoPrivateMatch] Creating with\n" + cm.ServerName + "\n" + cm.Password);
				mw.CreatePrivateMatch(region, cm);
			}			
			else if (event_code == 1) {
				std::string lname = name;
				std::string lpass = pass;
				cvarManager->log("Joining with\n" + lname + "\n" + lpass);
				mw.JoinPrivateMatch(lname, lpass);
			}
			else cvarManager->log("[gotoPrivateMatch] Invalid event code!");		
		}
		gameWrapper->SetTimeout([this](GameWrapper* gw) {
			if (!gameWrapper->IsInOnlineGame() && !cvarManager->getCvar("MJEndRecursiveJoin").getBoolValue()) { cvarManager->log("[gotoPrivateMatch] Checking..."); gotoPrivateMatch(); return; }
			else { cvarManager->log("[gotoPrivateMatch] Success."); cvarManager->getCvar("MJEndRecursiveJoin").setValue("0"); return; }
			
			},10.0);

}


Region MJ::getRegion(int region) {
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