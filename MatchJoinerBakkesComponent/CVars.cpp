#include "pch.h"
#include "MJ.h"

void MJ::initCvars() {
	initMatchCvars();
	initGuiCvars();
	initServerCvars();
	initUtilityCvars();
}

void MJ::initMatchCvars() {
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
}

void MJ::initGuiCvars() {

	cvarManager->registerCvar("MJMapNameSelection", "18", "Enter map name", true, false, false, false).addOnValueChanged([this](std::string old, CVarWrapper cw) {
		cvarManager->getCvar("MJMap").setValue(map_codenames[cw.getIntValue()]);
		selected_map = map_codenames[cw.getIntValue()];
		});
	cvarManager->registerCvar("MJIsQuickMatchWindowEnabled", "0", "Toggles quick private match join/create window", true, true, 0, true, 1, false); //change to notifier
	cvarManager->registerCvar("MJGeneratedLink", "", "Generated link", true, false, false, false);
	cvarManager->registerCvar("MJAutotabInToggle", "1", "Toggles autotab back in on server request", true, true, 0, true, 1, false).addOnValueChanged([this](std::string old, CVarWrapper cw) {
		is_autotab_enabled = cw.getBoolValue();
		});;
}

void MJ::initServerCvars() {
	cvarManager->registerNotifier("MJEnableServer", [this](std::vector<std::string> args) {
		startServer();
		}, "", PERMISSION_ALL);
	cvarManager->registerNotifier("MJDisableServer", [this](std::vector<std::string> args) {
		CurlRequest req;
		req.url = "http://localhost:6969/halt";
		req.body = "";
		HttpWrapper::SendCurlRequest(req, [this](int code, std::string result) {
			cvarManager->log("[cvarManager] sent request to shut down...");
			});
		}, "", PERMISSION_ALL);
}

void MJ::initUtilityCvars() {
	cvarManager->registerNotifier("MJReady", [this](std::vector<std::string> args) {
		monitorOnlineState();
		gotoPrivateMatch();
		}, "", PERMISSION_ALL);
	cvarManager->registerCvar("MJEndRecursiveJoin", "0", "", true, true, 0, true, 1, false);
	cvarManager->registerCvar("MJEndMonitor", "0", "", true, true, 0, true, 1, false);
	cvarManager->registerCvar("MJTimeBeforeRetrying", std::to_string(time_to_wait), "", true, true, 10, true, 60, false);
	cvarManager->registerNotifier("MJDisableMod", [this](std::vector<std::string> args) {
		unregisterCvars();
		}, "", PERMISSION_ALL);
	cvarManager->registerNotifier("MJEnableMod", [this](std::vector<std::string> args) {
		cvarManager->executeCommand("MJEnableServer");
		initCvars();
		}, "", PERMISSION_ALL);
	cvarManager->setBind("F3", "togglemenu mj");
}

void MJ::unregisterCvars() {
	cvarManager->executeCommand("MJDisableServer");
	cvarManager->removeCvar("MJEventType");
	cvarManager->removeCvar("MJServerName");
	cvarManager->removeCvar("MJServerPass");
	cvarManager->removeCvar("MJMap");
	cvarManager->removeCvar("MJRegion");
	cvarManager->removeCvar("MJIsQuickMatchWindowEnabled");
	cvarManager->removeCvar("MJMapNameSelection");
	cvarManager->removeCvar("MJGeneratedLink");
	cvarManager->removeCvar("MJEndRecursiveJoin");
	cvarManager->removeCvar("MJAutotabInToggle");
	cvarManager->removeNotifier("MJGetMatchVars");
	cvarManager->removeNotifier("MJReady");
	cvarManager->removeNotifier("MJDisableServer");
	cvarManager->removeNotifier("MJEnableServer");
	cvarManager->removeBind("F3"); //need to store what this is set to initially
	cvarManager->log("cvars unregistered!");
}