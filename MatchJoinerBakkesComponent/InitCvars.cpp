#include "pch.h"
#include "MatchJoinerBakkesComponent.h"

void MatchJoinerBakkesComponent::initInternalCvars() {
	cvarManager->registerCvar("MJEventType", "1", "Set to 0 for create mode, 1 for join mode", true, true, 0, true, 1, false); //add onvaluechanged so that they auto set to corresponding vars
	cvarManager->registerCvar("MJServerName", "", "Enter the server name", true, false, false, false);
	cvarManager->registerCvar("MJServerPass", "", "Enter the server password", true, false, false, false);
	cvarManager->registerCvar("MJMap", map_codenames[17], "Enter internal map names (see MapsStruct.h for names)", true, false, false, true); //gonna want to save this choice
	cvarManager->registerCvar("MJRegion", "0", "Enter the region code (0-9)", true, true, 0, true, 9, false);
	cvarManager->registerCvar("MJServerHasSetVars", "0", "", true, true, 0, true, 1, false);

	cvarManager->registerNotifier("MJGetMatchVars", [this](std::vector<std::string> args) {
		cvarManager->log("Event= " + cvarManager->getCvar("MJEventType").getStringValue());
		cvarManager->log("Name= " + cvarManager->getCvar("MJServerName").getStringValue());
		cvarManager->log("Pass= " + cvarManager->getCvar("MJServerPass").getStringValue());
		cvarManager->log("Region= " + cvarManager->getCvar("MJRegion").getStringValue());
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("MJReady", [this](std::vector<std::string> args) {
		gotoPrivateMatch();
		}, "", PERMISSION_ALL);

}

void MatchJoinerBakkesComponent::initGuiCvars() {
	cvarManager->registerCvar("MJModEnabled", "1", "Is mod enabled?", false, true, 0, true, 1, false).addOnValueChanged([this](std::string old, CVarWrapper cw) {
		is_enabled = cw.getBoolValue(); //just need to sleep the server thread, unload windows and options
		//is_enabled ? gameWrapper->Execute([this](GameWrapper* gw) { cvarManager->executeCommand("plugin unload matchjoinerbakkescomponent"); }) : gameWrapper->Execute([this](GameWrapper* gw) {cvarManager->executeCommand("plugin load matchjoinerbakkescomponent"); });
		});
	cvarManager->registerCvar("MJExtMapNameSelection", "18", "Enter map name", true, false, false, false);
	cvarManager->registerCvar("MJCreateBtnClicked", "0", "", false, true, 0, true, 1, false);
	cvarManager->registerCvar("MJIsQuickMatchWindowEnabled", "0", "Toggles quick private match join/create window", true, true, 0, true, 1, false); //change to notifier
}

void MatchJoinerBakkesComponent::initServerCvars() {
	cvarManager->registerNotifier("MJServerEnabledNotifier", [this](std::vector<std::string> args) { //broken, probably should rework server thread to never end
		if (args[1] == "1") {
			server_enabled = true;
			startServer();
			
		}
		else if (args[1] == "0") {
			server_enabled = false;
			stopServer();
			
		}
		else {
			cvarManager->log("Invalid args");
		}
		}, "", PERMISSION_ALL);
}