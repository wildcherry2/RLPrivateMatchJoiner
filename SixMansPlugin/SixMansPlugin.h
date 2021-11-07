//https://bakkesmodwiki.github.io/bakkesmod_api/
/*
* TODO:
* Test join once its working, separate option for disabling auto join for create,grey out things right
* handle load disabled on launch, persistent log on soft disables, note about fully unloading
* Make it persistent when going from training -> main menu
* Save exclusive logging to text file instead of printing on console for bug reports
* Documentation/wrap everything in namespaces for organization
* 
* BUG: enable broke again, logs arent working with extended args
*/
#pragma once

#include "pch.h"
#include "version.h"
#include "Constants.h"
#include "CFG.h"
#include "MatchStruct.h"
#include "SettingsIncludes.h"
constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);

class SixMansPlugin: public BakkesMod::Plugin::BakkesModPlugin, public BakkesMod::Plugin::PluginSettingsWindow, public BakkesMod::Plugin::PluginWindow
{
public:
	//core
	virtual void onLoad();
	virtual void onUnload();
	void gotoPrivateMatch();
	void logt(std::string text);
	Region getRegion(int region);
	bool gpm_called = false;
	bool loading = true;

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
	//log
	std::string logpath = gameWrapper->GetDataFolder().string() + "\\6m\\6m.log";
	std::ofstream ls;
	CFG cfg = CFG(*gameWrapper, logpath);

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
	Match match_info;
	/*std::string name = "", pass = "";
	std::string gametags = "BotsNone";
	Region region = Region::USE;
	size_t event_code = 1;
	std::string selected_map = Constants::MAP_CODENAMES[17];*/


	//interface	
	bool isWindowOpen_ = false;
	bool isMinimized_ = false;
	bool notif_enabled = true;
	bool countdown = false;
	std::string menuTitle_ = "sixmansplugininterface";
	size_t xres;
	size_t yres;
	double countdown_start = 20;
	double countdown_current;
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

	
};