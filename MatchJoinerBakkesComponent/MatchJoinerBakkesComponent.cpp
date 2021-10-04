//https://bakkesmodwiki.github.io/bakkesmod_api/
#include "pch.h"
#include "MatchJoinerBakkesComponent.h"


BAKKESMOD_PLUGIN(MatchJoinerBakkesComponent, "Takes match data from a pipe and creates/joins a private match", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;
//MAPS maps;


void MatchJoinerBakkesComponent::onLoad()
{
	_globalCvarManager = cvarManager;
	cvarManager->registerCvar("MJEventType","1","Set to 0 for create mode, 1 for join mode",true,true,0,true,1,false);
	cvarManager->registerCvar("MJServerName", "", "Enter the server name", true, false, false, false);
	cvarManager->registerCvar("MJServerPass", "", "Enter the server password", true, false, false, false);
	cvarManager->registerCvar("MJModEnabled", "1", "Is mod enabled?", false, true, 0, true, 1, false);
	cvarManager->registerCvar("MJMap", map_codenames[17],"Enter internal map names (see MapsStruct.h for names)", true, false, false, true); //gonna want to save this choice
	cvarManager->registerCvar("MJRegion", "0", "Enter the region code (0-9)", true, true, 0, true, 9, false);
	cvarManager->registerCvar("MJExtMapNameSelection", "18", "Enter map name", true, false, false, false);
	cvarManager->registerCvar("MJIsQuickMatchWindowEnabled", "0", "Toggles quick private match join/create window", true, true, 0, true, 1, false); //change to notifier
	cvarManager->registerNotifier("MJGotoMatch", [this](std::vector<std::string> args) {
		gotoPrivateMatch(); //listen for changes before this, maybe change/add above notifier
		},"", PERMISSION_ALL);

}

void MatchJoinerBakkesComponent::onUnload()
{
	cvarManager->log("Match joiner unloaded.");
}

//check that user is in freeplay or main menu (gamewrapper getonlinegame)
void MatchJoinerBakkesComponent::createPrivateMatch(std::string name, std::string pass, std::string map, int region) {
	MatchmakingWrapper* mm = new MatchmakingWrapper(true);
	CustomMatchTeamSettings* blue = new CustomMatchTeamSettings();
	CustomMatchTeamSettings* red = new CustomMatchTeamSettings();
	CustomMatchSettings* cm = new CustomMatchSettings();
	ServerWrapper sw = (gameWrapper->GetCurrentGameState());
	Region reg = getRegion(region); //needs testing

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
	if (cvarManager->getCvar("MJEventType").getBoolValue() == true) joinPrivateMatch(cvarManager->getCvar("MJServerName").getStringValue(), cvarManager->getCvar("MJServerPass").getStringValue());
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