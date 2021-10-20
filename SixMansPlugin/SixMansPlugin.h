//https://bakkesmodwiki.github.io/bakkesmod_api/
/*
* TODO:
* Toasts
* Saving settings to cfg-last bool in cvar declaration sets this,fix crashing related issue?
* Test join once its working, separate option for disabling auto join for create
* Clean up unnecessary vars/functions/function calls/includes
* Documentation
*/
#pragma once

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"
#include "bakkesmod/wrappers/gamewrapper.h"
#include "bakkesmod/wrappers/MatchmakingWrapper.h"
#include "bakkesmod/wrappers/PlayerControllerWrapper.h"
#include "bakkesmod/wrappers/GameEvent/GameEventWrapper.h"
//#include "Toast.h"
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
constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);



class SixMansPlugin: public BakkesMod::Plugin::BakkesModPlugin, public BakkesMod::Plugin::PluginSettingsWindow/*, public BakkesMod::Plugin::PluginWindow*/
{
public:
	//std::shared_ptr<bool> createbtn = std::make_shared<bool>(false);

	//core
	virtual void onLoad();
	virtual void onUnload();
	void gotoPrivateMatch();
	Region getRegion(int region);

	//autojoin
	std::thread monitor;
	bool in_game = false;
	bool mon_running = true;
	size_t time_to_wait = 45;
	bool is_enabled_autoretry = true;
	void monitorOnlineState();

	//cvar
	void initCvars();
	void initMatchCvars();
	void initGuiCvars();
	void initServerCvars();
	void initUtilityCvars();
	void initAutojoinCvars();
	void unregisterCvars();

	//f2 gui
	void RenderSettings() override;
	std::string GetPluginName() override;
	void SetImGuiContext(uintptr_t ctx) override;
	void renderModEnabledCheckbox();
	void renderAutotabEnabled();
	void renderMapCombobox(std::string name);
	void renderAutoretryEnabled();
	void renderTimeRetry();
	bool is_enabled = true; //for overall mod
	bool is_autotab_enabled = true;
	char name_field_storage[100] = "";
	char pass_field_storage[100] = "";
	std::string link = "";

	//server
	void startServer();
	std::thread server_thread;
	void MoveGameToFront();

	//match info
	std::string name = "", pass = "";
	std::string gametags = "BotsNone";
	Region region = Region::USE;
	int event_code = 1;
	std::string selected_map = MAP_CODENAMES[17];

	//toasts
	const std::string TOAST_LOGO_PATH = "default";
	const float TOAST_TIME, TOAST_WIDTH, TOAST_HEIGHT;
	const uint8_t TOAST_TYPE;
	void renderJoinToast();
	void renderCreateToast();
	void renderErrorToast();

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
};