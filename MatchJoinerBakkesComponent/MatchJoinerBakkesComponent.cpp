//https://bakkesmodwiki.github.io/bakkesmod_api/
#include "pch.h"
#include "MatchJoinerBakkesComponent.h"


BAKKESMOD_PLUGIN(MatchJoinerBakkesComponent, "Takes match data from a pipe and creates/joins a private match", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;
MatchJoinerBakkesComponent::MAPS maps;
//for testing, comment out once pipe is implemented
//const std::string events = "0";
//const std::string name = "b12";
//const std::string pass = "b11";

void MatchJoinerBakkesComponent::onLoad()
{
	_globalCvarManager = cvarManager;
	cvarManager->log("Match joiner plugin loaded");
	cvarManager->registerCvar("MJEventType","1","Set to 0 for create mode, 1 for join mode",true,true,0,true,1,false);
	cvarManager->registerCvar("MJServerName", "", "Enter the server name", true, false, false, false);
	cvarManager->registerCvar("MJServerPass", "", "Enter the server password", true, false, false, false);
	cvarManager->registerCvar("MJMap", maps.mannfield,"Enter internal map names (see the struct in the main header for names)", true, false, false, false); //gonna want to save this choice
	cvarManager->registerCvar("MJRegion", "", "Enter the region code", true, false, false, false);//add cvar for region choice
	cvarManager->registerNotifier("MJGotoMatch", [this](std::vector<std::string> args) {
		gotoPrivateMatch();//setServerCvars(); //listen for changes before this, maybe change above notifier
		},"", PERMISSION_ALL);
	//createPrivateMatch("b1000","8xma");

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
	//GameWrapper* gw = &gameWrapper;
	ServerWrapper sw = (gameWrapper->GetCurrentGameState());
	Region reg = getRegion(region);

	cm->GameTags = "BotsNone";
	cm->MapName = map;
	cm->ServerName = name;
	cm->Password = pass;
	cm->BlueTeamSettings = *blue;
	cm->OrangeTeamSettings = *red;
	cm->bClubServer = false;

	//while (sw->IsNull()) {
		mm->CreatePrivateMatch(reg,*cm);
		//add 10-15 sec delay before trying again/check to be on menu, black screen edge case?
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

//void MatchJoinerBakkesComponent::setServerCvars() {
//	//replace with pipe functionality, placeholder for now
//	//listen for changes on each cvar? define them with no defaults if so 
//	cvarManager->getCvar("MJEventType").setValue(events);
//	cvarManager->getCvar("MJServerName").setValue(name);
//	cvarManager->getCvar("MJServerPass").setValue(pass);
//	gotoPrivateMatch();
//}

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