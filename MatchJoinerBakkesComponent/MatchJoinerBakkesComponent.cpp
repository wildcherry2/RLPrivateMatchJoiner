//https://bakkesmodwiki.github.io/bakkesmod_api/
#include "pch.h"
#include "MatchJoinerBakkesComponent.h"

//https://bakkesmodwiki.github.io/bakkesmod_api/Classes/Wrappers/Modals/ModalWrapper/ for dealing with annoying popup

BAKKESMOD_PLUGIN(MatchJoinerBakkesComponent, "Takes match data from a link to a localhost webserver to join a private match", plugin_version, PLUGINTYPE_THREADED) //changed to threaded

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;
//MAPS maps;


void MatchJoinerBakkesComponent::onLoad()
{
	_globalCvarManager = cvarManager;
	initInternalCvars();
	initGuiCvars();
	initServerCvars();
	initServer();
	startServer();
}

void MatchJoinerBakkesComponent::onUnload()
{
	stopServer();
	cvarManager->log("Match joiner unloaded.");
}

//check that user is in freeplay or main menu (gamewrapper getonlinegame), also retry on join, black screen edge case
void MatchJoinerBakkesComponent::createPrivateMatch() {
	if (event_code == 0) {
		MatchmakingWrapper mw = gameWrapper->GetMatchmakingWrapper();
		CustomMatchSettings cm = CustomMatchSettings();
		CustomMatchTeamSettings blue = CustomMatchTeamSettings();
		CustomMatchTeamSettings red = CustomMatchTeamSettings();

		if (mw && !gameWrapper->IsInOnlineGame()) {

			cm.GameTags = gametags;
			cm.MapName = map_codenames[2];
			cm.ServerName = name;
			cm.Password = pass;
			cm.BlueTeamSettings = blue;
			cm.OrangeTeamSettings = red;
			cm.bClubServer = false;

			mw.CreatePrivateMatch(region, cm);
		}
	}
}


Region MatchJoinerBakkesComponent::getRegion(int region) {
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