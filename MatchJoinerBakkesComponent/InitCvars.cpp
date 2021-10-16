#include "pch.h"
#include "MJ.h"

void MJ::initInternalCvars() {
	cvarManager->registerCvar("MJEventType", "1", "Set to 0 for create mode, 1 for join mode", true, true, 0, true, 1, false).addOnValueChanged([this](std::string old, CVarWrapper cw) {
		event_code = cw.getIntValue();
		});
	cvarManager->registerCvar("MJServerName", "", "Enter the server name", true, false, false, false).addOnValueChanged([this](std::string old, CVarWrapper cw) {
		name = cw.getStringValue();
		});
	cvarManager->registerCvar("MJServerPass", "", "Enter the server password", true, false, false, false).addOnValueChanged([this](std::string old, CVarWrapper cw) {
		pass = cw.getStringValue();
		});
	cvarManager->registerCvar("MJMap", map_codenames[17], "Enter internal map names (see MapsStruct.h for names)", true, false, false, true).addOnValueChanged([this](std::string old, CVarWrapper cw) {
		selected_map = cw.getStringValue();
		}); //gonna want to save this choice
	cvarManager->registerCvar("MJRegion", "0", "Enter the region code (0-9)", true, true, 0, true, 9, false).addOnValueChanged([this](std::string old, CVarWrapper cw) {
		region = getRegion(cw.getIntValue());
		});

	cvarManager->registerNotifier("MJGetMatchVars", [this](std::vector<std::string> args) {
		cvarManager->log("Event= " + cvarManager->getCvar("MJEventType").getStringValue());
		cvarManager->log("Name= " + cvarManager->getCvar("MJServerName").getStringValue());
		cvarManager->log("Pass= " + cvarManager->getCvar("MJServerPass").getStringValue());
		cvarManager->log("Region= " + cvarManager->getCvar("MJRegion").getStringValue());
		cvarManager->log("Map= " + cvarManager->getCvar("MJMap").getStringValue());
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("MJReady", [this](std::vector<std::string> args) {
		gotoPrivateMatch();
		}, "", PERMISSION_ALL);

	//works, but activates mjready, could cause issues, need to fix
	cvarManager->registerNotifier("MJDisableServer", [this](std::vector<std::string> args) {
		//this->server_disabled_activated_flag = true;
		server->stop();
		//this->server_disabled_activated_flag = false;
		}, "", PERMISSION_ALL);

	cvarManager->setBind("F3","togglemenu mj");

}

void MJ::initGuiCvars() {
	cvarManager->registerCvar("MJModEnabled", "1", "Is mod enabled?", false, true, 0, true, 1, false).addOnValueChanged([this](std::string old, CVarWrapper cw) {
		is_enabled = cw.getBoolValue(); //just need to sleep the server thread, unload windows and options
		//is_enabled ? gameWrapper->Execute([this](GameWrapper* gw) { cvarManager->executeCommand("plugin unload MJ"); }) : gameWrapper->Execute([this](GameWrapper* gw) {cvarManager->executeCommand("plugin load MJ"); });
		});
	cvarManager->registerCvar("MJMapNameSelection", "18", "Enter map name", true, false, false, false).addOnValueChanged([this](std::string old, CVarWrapper cw) {
		cvarManager->getCvar("MJMap").setValue(map_codenames[cw.getIntValue()]);
		selected_map = map_codenames[cw.getIntValue()];
		});
	/*cvarManager->registerNotifier("MJCreateBtnClicked", [this](std::vector<std::string> args) {
		gotoPrivateMatch();
		},"",PERMISSION_ALL);*/
	//cvarManager->registerCvar("MJCreateBtnClicked", "0", "", false, true, 0, true, 1, false).addOnValueChanged([this](std::string old, CVarWrapper cw) {gotoPrivateMatch();}); //needs testing
	cvarManager->registerCvar("MJIsQuickMatchWindowEnabled", "0", "Toggles quick private match join/create window", true, true, 0, true, 1, false); //change to notifier
}