//https://bakkesmodwiki.github.io/bakkesmod_api/
/*
* TODO:
* Test join once its working, separate option for disabling auto join for create,grey out things right
* Test autoretry enabled with autojoin disabled
* Clean up unnecessary vars/functions/function calls/includes
* Save exclusive logging to text file instead of printing on console for bug reports
* Documentation
* 
* c++20?
* 
* BUGS:
* Enabling autoretry while 6mans window is up, then disabling the mod via f2 causes crash- should probably grey out options on gotoprivatematch call
*/
#pragma once

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"
#include "bakkesmod/wrappers/gamewrapper.h"
#include "bakkesmod/wrappers/MatchmakingWrapper.h"
#include "bakkesmod/wrappers/PlayerControllerWrapper.h"
#include "bakkesmod/wrappers/GameEvent/GameEventWrapper.h"
#include "bakkesmod/wrappers/SettingsWrapper.h"
#include "bakkesmod/wrappers/ImageWrapper.h"
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_dx11.h"
#include <regex>
#include <algorithm>
#include "version.h"
#include "Simple-Web-Server/server_http.hpp">;
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <fstream>
#include <vector>
#include <thread>
#include <functional>
#include <iostream>
#include <utility>
#include <string>
#include <cstring>
#include "nlohmann/json.hpp"
#include "Timer.h"
//#include "CFG.h"
#include <stack>
constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);



class SixMansPlugin: public BakkesMod::Plugin::BakkesModPlugin, public BakkesMod::Plugin::PluginSettingsWindow, public BakkesMod::Plugin::PluginWindow
{
public:
	//core
	virtual void onLoad();
	virtual void onUnload();
	void gotoPrivateMatch();
	Region getRegion(int region);
	bool gpm_called = false;
	Timer timer;

	//autojoin
	bool in_game = false;
	size_t time_to_wait = 45;
	bool is_enabled_autoretry = true;
	bool can_manually_back_out = false;
	void autoRetry();

	//init
	bool mod_switch = false;
	void init();
	void initMatchCvars();
	void initGuiCvars();
	void initHooks();
	void initServerCvars();
	void initUtilityCvars();
	void initAutojoinCvars();
	void unregisterCvars();

	//custom cfg
	void initCFGMan();
	void loadConfig(const std::vector<std::string> cvars);
	void saveConfig(const std::vector<std::string> cvars);
	std::vector<std::string> cvarbuf;
	nlohmann::json set_file;
	std::ifstream is;
	std::ofstream os;
	const std::string path = gameWrapper->GetDataFolder().string() + "\\config.json";

	//f2 gui
	void RenderSettings() override;
	std::string GetPluginName() override;
	void SetImGuiContext(uintptr_t ctx) override;
	void renderModEnabledCheckbox();
	void renderAutotabEnabled();
	void renderMapCombobox(std::string name);
	void renderAutoretryEnabled();
	void renderTimeRetry();
	void renderAutojoinEnabled();
	bool is_enabled = true; //for overall mod
	bool is_autotab_enabled = true;
	bool is_autojoin_enabled = true;
	char name_field_storage[100] = "";
	char pass_field_storage[100] = "";

	//server
	void startServer();
	std::thread server_thread;
	void MoveGameToFront();

	//match info
	std::string name = "", pass = "";
	std::string gametags = "BotsNone";
	Region region = Region::USE;
	size_t event_code = 1;
	std::string selected_map = MAP_CODENAMES[17];


	//interface	
	bool isWindowOpen_ = false;
	bool isMinimized_ = false;
	bool doAction = false;
	bool notif_enabled = true;
	bool countdown = false;
	bool hastried = false;
	std::string menuTitle_ = "sixmansplugininterface";
	size_t xres;
	size_t yres;
	double countdown_c;
	double countdown_start = 20;
	double countdown_current;
	int countdown_index = -1;
	float res_ratio_x = 1550 / 1920.0; //multiply these by res to get scaled toast
	float res_ratio_y = 20 / 1080.0;
	float res_ratio_w = 350 / 1920.0;
	float res_ratio_h = 400 / 1080.0;
	float action_notif_width, action_notif_height, action_notif_x, action_notif_y;
	std::shared_ptr<ImageWrapper> logo;
	ImFont* roboto_reg;
	ImFont* roboto_black;
	ImFont* roboto_bold;
	void setRes(size_t& x, size_t& y);
	void initNotifVars();
	void renderBlankNotif();
	void renderLogo();
	void renderHeader(std::string header);
	void renderText(std::string text);
	void renderButton(std::string text);
	void renderNote(std::string text);
	void renderCountdown();
	void initCountdown();
	void renderActionNotif();
	virtual void Render() override;
	virtual std::string GetMenuName() override;
	virtual std::string GetMenuTitle() override;
	virtual bool ShouldBlockInput() override;
	virtual bool IsActiveOverlay() override;
	virtual void OnOpen() override;
	virtual void OnClose() override;

	const std::string STAT_ERROR[3] = {
		"Joining match...",
		"Creating match...",
		"Error!"
	};
	//name arrays
	const std::string MAP_CODENAMES[35] = {
		"Underwater_P",
		"Park_P",
		"Park_Night_P",
		"Park_Rainy_P",
		"cs_p",
		"cs_day_p",
		"bb_p",
		"outlaw_p",
		"Stadium_P",
		"Stadium_Race_Day_p",
		"stadium_day_p",
		"Stadium_Winter_P",
		"Stadium_Foggy_P",
		"farm_p",
		"Farm_Night_P",
		"CHN_Stadium_P",
		"CHN_Stadium_Day_P",
		"EuroStadium_P",
		"EuroStadium_Night_P",
		"eurostadium_snownight_p",
		"EuroStadium_Rainy_P",
		"NeoTokyo_Standard_P",
		"music_p",
		"cs_hw_p",
		"beach_P",
		"beach_night_p",
		"arc_standard_p",
		"TrainStation_P",
		"TrainStation_Dawn_P",
		"TrainStation_Night_P",
		"UtopiaStadium_P",
		"UtopiaStadium_Dusk_P",
		"UtopiaStadium_Snow_P",
		"wasteland_s_p",
		"wasteland_Night_S_P"
	};
	const char* MAP_NORMALNAMES[35] = {
		"Aquadome",
		"Beckwith Park",
		"Beckwith Park (Midnight)",
		"Beckwith Park (Stormy)",
		"Champions Field",
		"Champions Field (Day)",
		"Champions Field (NFL)",
		"Deadeye Canyon",
		"DFH Stadium",
		"DFH Stadium (Circuit)",
		"DFH Stadium (Day)",
		"DFH Stadium (Snowy)",
		"DFH Stadium (Stormy)",
		"Farmstead",
		"Farmstead (Night)",
		"Forbidden Temple",
		"Forbidden Temple (Day)",
		"Mannfield",
		"Mannfield (Night)",
		"Mannfield (Snowy)",
		"Mannfield (Stormy)",
		"Neo Tokyo",
		"Neon Fields",
		"Rivals Arena",
		"Salty Shores",
		"Salty Shores (Night)",
		"Starbase ARC",
		"Urban Central",
		"Urban Central (Dawn)",
		"Urban Central (Night)",
		"Utopia Coliseum",
		"Utopia Coliseum (Dusk)",
		"Utopia Coliseum (Snowy)",
		"Wasteland",
		"Wasteland (Night)"
	};

	const char* REGION_NAMES[10] = {
		"US-East (USE)",
		"Europe (EU)",
		"US-West (USW)",
		"Asia SE-Mainland (ASC)",
		"Asia SE-Maritime (ASM)",
		"Asia East (JPN)",
		"Middle East (ME)",
		"Oceania (OCE)",
		"South Africa (SAF)",
		"South America (SAM)"
	};

	const std::vector<std::string> PERSISTENT_CVARS = {
		"6mMapNameSelection",
		"6mAutotabInToggle",
		"6mModEnabled",
		"6mTimeBeforeRetrying",
		"6mAutoRetryToggle"
	};

	const size_t NUM_PER_CVARS = 5;

	
};