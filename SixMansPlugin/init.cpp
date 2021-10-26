#include "pch.h"
#include "SixMansPlugin.h"

void SixMansPlugin::init() {
	if (!mod_switch) {
		cvarManager->registerNotifier("6mEnableMod", [this](std::vector<std::string> args) {
			init();
			cvarManager->executeCommand("6mEnableServer");
			}, "", PERMISSION_ALL);
		cvarManager->registerNotifier("6mDisableMod", [this](std::vector<std::string> args) {
			unregisterCvars();
			}, "", PERMISSION_ALL);
		cvarManager->registerCvar("6mModEnabled", "1", "", true, true, 0, true, 1, false).addOnValueChanged([this](std::string old, CVarWrapper cw) { //make this a notifier
			is_enabled = cw.getBoolValue();
			if (is_enabled) {


				cvarManager->executeCommand("6mEnableMod");
			}
			else cvarManager->executeCommand("6mDisableMod");
			});

		initNotifVars();
		mod_switch = true;
	}
	
	initHooks();
	initMatchCvars();
	initGuiCvars();
	initServerCvars();
	initUtilityCvars();
	initAutojoinCvars();
	initCFGMan();
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
	cvarManager->registerCvar("6mMap", MAP_CODENAMES[17], "Enter internal map names (see MapsStruct.h for names)", true, false, false, false,false,false).addOnValueChanged([this](std::string old, CVarWrapper cw) {
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
	cvarManager->registerCvar("6mMapNameSelection", "18", "Enter map name", true, false, false, false,false,false).addOnValueChanged([this](std::string old, CVarWrapper cw) {
		cvarManager->getCvar("6mMap").setValue(MAP_CODENAMES[cw.getIntValue()]);
		selected_map = MAP_CODENAMES[cw.getIntValue()];
		});
	cvarManager->registerCvar("6mAutotabInToggle", "1", "Toggles autotab back in on server request", true, true, 0, true, 1, false).addOnValueChanged([this](std::string old, CVarWrapper cw) {
		is_autotab_enabled = cw.getBoolValue();
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
		gotoPrivateMatch();
		}, "", PERMISSION_ALL);
	
	//cvarManager->setBind("F3", "6mLoadCvar");
	cvarManager->registerNotifier("6mSaveCvar", [this](std::vector<std::string> args) {
		args.erase(args.begin()); //dont care about the notifier name
		saveConfig(args);
		}, "", PERMISSION_ALL);
	cvarManager->registerNotifier("6mLoadCvar", [this](std::vector<std::string> args) {
		args.erase(args.begin());
		loadConfig(args);
		}, "", PERMISSION_ALL);
}

void SixMansPlugin::unregisterCvars() {
	cvarManager->executeCommand("6mDisableServer");
	//cvarManager->getCvar("6mEndMonitor").setValue("1");
	//cvarManager->executeCommand("6mDisableServer");
	cvarManager->removeCvar("6mEventType");
	cvarManager->removeCvar("6mServerName");
	cvarManager->removeCvar("6mServerPass");
	cvarManager->removeCvar("6mMap");
	cvarManager->removeCvar("6mRegion");
	//cvarManager->removeCvar("6mIsQuickMatchWindowEnabled");
	cvarManager->removeCvar("6mMapNameSelection");
	//cvarManager->removeCvar("6mGeneratedLink");
	//cvarManager->removeCvar("6mEndRecursiveJoin");
	cvarManager->removeCvar("6mAutotabInToggle");
	cvarManager->removeCvar("6mAutoRetryToggle");
	//cvarManager->removeCvar("6mEndRecursiveJoin");
	//cvarManager->removeCvar("6mEndMonitor");
	cvarManager->removeCvar("6mTimeBeforeRetrying");
	cvarManager->removeNotifier("6mGetMatchVars");
	cvarManager->removeNotifier("6mReady");
	cvarManager->removeNotifier("6mDisableServer");
	cvarManager->removeNotifier("6mEnableServer");
	cvarManager->removeNotifier("6mSaveCvar");
	cvarManager->removeNotifier("6mLoadCvar");
	//cvarManager->removeNotifier("6mEnableMod");
	//cvarManager->removeNotifier("6mDisableMod");
	//cvarManager->removeBind("F3"); //need to store what this is set to initially
	gameWrapper->UnhookEvent("Function OnlineGamePrivateMatch_X.Joining.HandleJoinGameComplete");
	gameWrapper->UnhookEvent("Function TAGame.GameEvent_Soccar_TA.Destroyed");
	cvarManager->log("cvars unregistered,mod disabled!");
}

void SixMansPlugin::initAutojoinCvars() {
	/*cvarManager->registerCvar("6mEndRecursiveJoin", "0", "", true, true, 0, true, 1, false);
	cvarManager->registerCvar("6mEndMonitor", "0", "", true, true, 0, true, 1, false);*/
	cvarManager->registerCvar("6mTimeBeforeRetrying", std::to_string(time_to_wait), "", true, true, 30, true, 120, false).addOnValueChanged([this](std::string old, CVarWrapper cw) {
		time_to_wait = cw.getIntValue();
		});;
	cvarManager->registerCvar("6mAutoRetryToggle", "1", "", true, true, 0, true, 1, false).addOnValueChanged([this](std::string old, CVarWrapper cw) {
		is_enabled_autoretry = cw.getBoolValue();
		});
	cvarManager->registerCvar("6mInGame", "0", "", true, true, 0, true, 1, false).addOnValueChanged([this](std::string old, CVarWrapper cw) {
		in_game = cw.getBoolValue();
		});;
}

//also inits logo
void SixMansPlugin::initNotifVars() {
	logo = std::make_shared<ImageWrapper>(gameWrapper->GetDataFolder() / "sixmanlogo.png", false, true);
	setRes(xres, yres);

	action_notif_width = res_ratio_w * xres;
	action_notif_height = res_ratio_h * yres;
	action_notif_x = res_ratio_x * xres;
	action_notif_y = res_ratio_y * yres;

	ImGuiIO& io = ImGui::GetIO();
	ImFontConfig config;
	config.OversampleH = 2;
	config.OversampleV = 2;

	std::string font_path = gameWrapper->GetDataFolder().string() + "\\Roboto-Regular.ttf";
	roboto_reg = io.Fonts->AddFontFromFileTTF(font_path.c_str(), (14.0f/1080.0f)*yres, &config);

	font_path = gameWrapper->GetDataFolder().string() + "\\Roboto-Bold.ttf";
	roboto_bold = io.Fonts->AddFontFromFileTTF(font_path.c_str(), (23.0f/1080.0f)*yres, &config);

	font_path = gameWrapper->GetDataFolder().string() + "\\Roboto-Black.ttf";
	roboto_black = io.Fonts->AddFontFromFileTTF(font_path.c_str(), (40.0f/1080.0f)*yres, &config);

	io.Fonts->Build();

	
}

void SixMansPlugin::setRes(size_t& x, size_t& y) {
	std::string res_str = gameWrapper->GetSettings().GetVideoSettings().Resolution;
	size_t pos = res_str.find("x");
	x = std::stoi(res_str.substr(0, pos));
	y = std::stoi(res_str.substr(pos + 1, res_str.length() - pos + 1));
}

void SixMansPlugin::initHooks() {
	gameWrapper->HookEventPost("Function OnlineGamePrivateMatch_X.Joining.HandleJoinGameComplete", [this](std::string eventName) {
		cvarManager->getCvar("6mInGame").setValue("1");
		});
	gameWrapper->HookEventPost("Function TAGame.GameEvent_Soccar_TA.Destroyed", [this](std::string eventName) {
		cvarManager->getCvar("6mInGame").setValue("0");
		});
}