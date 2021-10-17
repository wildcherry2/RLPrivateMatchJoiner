//https://bakkesmodwiki.github.io/bakkesmod_api/
#include "pch.h"
#include "MJ.h"

//https://bakkesmodwiki.github.io/bakkesmod_api/Classes/Wrappers/Modals/ModalWrapper/ for dealing with annoying popup

BAKKESMOD_PLUGIN(MJ, "Takes match data from a link to a localhost webserver to join a private match", plugin_version, PLUGINTYPE_THREADED) //changed to threaded, change back to default for gui testing

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;


void MJ::onLoad()
{
	_globalCvarManager = cvarManager;
	initInternalCvars();
	initGuiCvars();
	initServer();
	startServer();
	//cvarManager->executeCommand("MJDisableServer");
}

void MJ::onUnload()
{
	/*cvarManager->executeCommand("MJDisableServer");
	server_thread.join();*/
	cvarManager->log("Match joiner unloaded.");
}

//retry on join, black screen edge case
void MJ::gotoPrivateMatch() {
	//cvarManager->log("gpm called");
	if (name == "") { cvarManager->log("Name is empty, returning"); return; }
	MatchmakingWrapper mw = gameWrapper->GetMatchmakingWrapper();
	if (event_code == 0) {
		CustomMatchSettings cm = CustomMatchSettings();
		CustomMatchTeamSettings blue = CustomMatchTeamSettings();
		CustomMatchTeamSettings red = CustomMatchTeamSettings();

		if (mw && !gameWrapper->IsInOnlineGame()) {

			cm.GameTags = gametags;
			cm.MapName = selected_map;
			cm.ServerName = name;
			cm.Password = pass;
			cm.BlueTeamSettings = blue;
			cm.OrangeTeamSettings = red;
			cm.bClubServer = false;

			cvarManager->log("Creating with\n" + cm.ServerName + "\n" + cm.Password);

			mw.CreatePrivateMatch(region, cm);
		}
		else cvarManager->log("Error creating lobby, you are in a game or mmw is invalid"); 
	}
	else if (event_code == 1) {
		if (mw && !gameWrapper->IsInOnlineGame()) {
			cvarManager->log("Joining with\n" + name + "\n" + pass);
			mw.JoinPrivateMatch(name, pass);

		}
		else cvarManager->log("Error joining lobby, you are in a game or mmw is invalid");

	}
	else cvarManager->log("Invalid event code!");
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