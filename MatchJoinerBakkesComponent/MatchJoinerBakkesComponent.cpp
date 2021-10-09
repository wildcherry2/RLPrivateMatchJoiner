//https://bakkesmodwiki.github.io/bakkesmod_api/
#include "pch.h"
#include "MatchJoinerBakkesComponent.h"

//https://bakkesmodwiki.github.io/bakkesmod_api/Classes/Wrappers/Modals/ModalWrapper/ for dealing with annoying popup

BAKKESMOD_PLUGIN(MatchJoinerBakkesComponent, "Takes match data from a link to a localhost webserver to join a private match", plugin_version, PLUGINTYPE_FREEPLAY)

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
	stopServer(); //no thread unloaded message??
	cvarManager->log("Match joiner unloaded.");
}

//check that user is in freeplay or main menu (gamewrapper getonlinegame)
void MatchJoinerBakkesComponent::createPrivateMatch(std::string name, std::string pass, std::string map, int region) {
	MatchmakingWrapper* mm = new MatchmakingWrapper(false);
	CustomMatchTeamSettings* blue = new CustomMatchTeamSettings();
	CustomMatchTeamSettings* red = new CustomMatchTeamSettings();
	CustomMatchSettings* cm = new CustomMatchSettings();
	//ServerWrapper sw = (gameWrapper->GetCurrentGameState());
	Region reg = getRegion(region);

	//mm->

	cm->GameTags = "BotsNone";
	cm->MapName = map;
	cm->ServerName = name;
	cm->Password = pass;
	cm->BlueTeamSettings = *blue;
	cm->OrangeTeamSettings = *red;
	cm->bClubServer = false;

	//while (sw->IsNull()) {
	mm->CreatePrivateMatch(reg,*cm);
		//add 10-15 sec delay before trying again/check to be on menu, black screen edge case (for testing, invalid server settings force black screens)
	//}
	

	delete mm;
	delete blue;
	delete red;
	delete cm;
}

//needs testing, try joining every 20? seconds
//hot key to manually retry joining/creating?
void MatchJoinerBakkesComponent::joinPrivateMatch(std::string name, std::string pass) {
	MatchmakingWrapper* mm = new MatchmakingWrapper(true);
	mm->JoinPrivateMatch(name, pass);

	delete mm;
}

//remember to add tab into rl functionality
void MatchJoinerBakkesComponent::gotoPrivateMatch() {
	if (cvarManager->getCvar("MJEventType").getStringValue() == "join") joinPrivateMatch(cvarManager->getCvar("MJServerName").getStringValue(), cvarManager->getCvar("MJServerPass").getStringValue());
	else createPrivateMatch(cvarManager->getCvar("MJServerName").getStringValue(), cvarManager->getCvar("MJServerPass").getStringValue(), cvarManager->getCvar("MJMap").getStringValue(), cvarManager->getCvar("MJRegion").getIntValue());
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