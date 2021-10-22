#include "pch.h"
#include "SixMansPlugin.h"

void SixMansPlugin::init() {
	initMatchCvars();
	initGuiCvars();
	initServerCvars();
	initUtilityCvars();
	initAutojoinCvars();
}

void SixMansPlugin::initMatchCvars() {
	cvarManager->registerCvar("6mEventType", "1", "Set to 0 for create mode, 1 for join mode", true, true, 0, true, 1, false).addOnValueChanged([this](std::string old, CVarWrapper cw) {
		event_code = cw.getIntValue();
		});
	cvarManager->registerCvar("6mServerName", "", "Enter the server name", true, false, false, false,false,false).addOnValueChanged([this](std::string old, CVarWrapper cw) {
		name = cw.getStringValue();
		});
	cvarManager->registerCvar("6mServerPass", "", "Enter the server password", true, false, false, false,false,false).addOnValueChanged([this](std::string old, CVarWrapper cw) {
		pass = cw.getStringValue();
		});
	cvarManager->registerCvar("6mMap", MAP_CODENAMES[17], "Enter internal map names (see MapsStruct.h for names)", true, false, false, true).addOnValueChanged([this](std::string old, CVarWrapper cw) {
		selected_map = cw.getStringValue();
		}); //gonna want to save this choice
	cvarManager->registerCvar("6mRegion", "0", "Enter the region code (0-9)", true, true, 0, true, 9, false).addOnValueChanged([this](std::string old, CVarWrapper cw) {
		region = getRegion(cw.getIntValue());
		});
	cvarManager->registerNotifier("6mGetMatchVars", [this](std::vector<std::string> args) {
		cvarManager->log("Event= " + cvarManager->getCvar("6mEventType").getStringValue());
		cvarManager->log("Name= " + cvarManager->getCvar("6mServerName").getStringValue());
		cvarManager->log("Pass= " + cvarManager->getCvar("6mServerPass").getStringValue());
		cvarManager->log("Region= " + cvarManager->getCvar("6mRegion").getStringValue());
		cvarManager->log("Map= " + cvarManager->getCvar("6mMap").getStringValue());
		}, "", PERMISSION_ALL);
}

void SixMansPlugin::initGuiCvars() {

	cvarManager->registerCvar("6mMapNameSelection", "18", "Enter map name", true, false, false, false).addOnValueChanged([this](std::string old, CVarWrapper cw) {
		cvarManager->getCvar("6mMap").setValue(MAP_CODENAMES[cw.getIntValue()]);
		selected_map = MAP_CODENAMES[cw.getIntValue()];
		});
	cvarManager->registerCvar("6mIsQuickMatchWindowEnabled", "0", "Toggles quick private match join/create window", true, true, 0, true, 1, false); //change to notifier
	cvarManager->registerCvar("6mGeneratedLink", "", "Generated link", true, false, false, false,false,false);
	cvarManager->registerCvar("6mAutotabInToggle", "1", "Toggles autotab back in on server request", true, true, 0, true, 1, true).addOnValueChanged([this](std::string old, CVarWrapper cw) {
		is_autotab_enabled = cw.getBoolValue();
		});;
	cvarManager->registerCvar("6mModEnabled", "1", "", true, true, 0, true, 1, true).addOnValueChanged([this](std::string old, CVarWrapper cw) {
		is_enabled = cw.getBoolValue();
		if (is_enabled) cvarManager->executeCommand("6mEnableMod");
		else cvarManager->executeCommand("6mDisableMod");
		});;
}

void SixMansPlugin::initServerCvars() {
	cvarManager->registerNotifier("6mEnableServer", [this](std::vector<std::string> args) {
		startServer();
		}, "", PERMISSION_ALL);
	cvarManager->registerNotifier("6mDisableServer", [this](std::vector<std::string> args) {
		CurlRequest req;
		req.url = "http://localhost:6969/halt";
		req.body = "";
		HttpWrapper::SendCurlRequest(req, [this](int code, std::string result) {
			cvarManager->log("[cvarManager] sent request to shut down...");
			});
		}, "", PERMISSION_ALL);
}

void SixMansPlugin::initUtilityCvars() {
	cvarManager->registerNotifier("6mReady", [this](std::vector<std::string> args) {
		in_game = false; //insurance
		if (is_enabled_autoretry) { monitorOnlineState(); }
		gotoPrivateMatch();
		in_game = false;
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("6mDisableMod", [this](std::vector<std::string> args) {
		unregisterCvars();
		}, "", PERMISSION_ALL);
	cvarManager->registerNotifier("6mEnableMod", [this](std::vector<std::string> args) {
		init();
		cvarManager->executeCommand("6mEnableServer");
		}, "", PERMISSION_ALL);

	/*cvarManager->registerNotifier("toasttest",[this](std::vector<std::string> args) {
		renderCreateToast();
		},"",PERMISSION_ALL);*/
	cvarManager->setBind("F3", "togglemenu SixMansPluginInterface");
}

void SixMansPlugin::unregisterCvars() {
	cvarManager->executeCommand("6mDisableServer");
	cvarManager->getCvar("6mEndMonitor").setValue("1");
	cvarManager->executeCommand("6mDisableServer");
	cvarManager->removeCvar("6mEventType");
	cvarManager->removeCvar("6mServerName");
	cvarManager->removeCvar("6mServerPass");
	cvarManager->removeCvar("6mMap");
	cvarManager->removeCvar("6mRegion");
	cvarManager->removeCvar("6mIsQuickMatchWindowEnabled");
	cvarManager->removeCvar("6mMapNameSelection");
	cvarManager->removeCvar("6mGeneratedLink");
	cvarManager->removeCvar("6mEndRecursiveJoin");
	cvarManager->removeCvar("6mAutotabInToggle");
	cvarManager->removeCvar("6mAutoRetryToggle");
	cvarManager->removeCvar("6mEndRecursiveJoin");
	cvarManager->removeCvar("6mEndMonitor");
	cvarManager->removeCvar("6mTimeBeforeRetrying");
	cvarManager->removeNotifier("6mGetMatchVars");
	cvarManager->removeNotifier("6mReady");
	cvarManager->removeNotifier("6mDisableServer");
	cvarManager->removeNotifier("6mEnableServer");
	//cvarManager->removeBind("F3"); //need to store what this is set to initially
	cvarManager->log("cvars unregistered,mod disabled!");
}

void SixMansPlugin::initAutojoinCvars() {
	cvarManager->registerCvar("6mEndRecursiveJoin", "0", "", true, true, 0, true, 1, false);
	cvarManager->registerCvar("6mEndMonitor", "0", "", true, true, 0, true, 1, false);
	cvarManager->registerCvar("6mTimeBeforeRetrying", std::to_string(time_to_wait), "", true, true, 30, true, 120, true).addOnValueChanged([this](std::string old, CVarWrapper cw) {
		time_to_wait = cw.getIntValue();
		});;
	cvarManager->registerCvar("6mAutoRetryToggle", "1", "", true, true, 0, true, 1, true).addOnValueChanged([this](std::string old, CVarWrapper cw) {
		is_enabled_autoretry = cw.getBoolValue();
		});
}

void SixMansPlugin::initFonts() {
	logo = std::make_shared<ImageWrapper>(gameWrapper->GetDataFolder() / "sixmanlogo.png", false, true);
	ImGuiIO& io = ImGui::GetIO();
	std::string font_path = gameWrapper->GetDataFolder().string() + "\\Roboto-Regular.ttf";
	roboto = io.Fonts->AddFontFromFileTTF(font_path.c_str(), 34.0f);
	io.Fonts->Build();
}