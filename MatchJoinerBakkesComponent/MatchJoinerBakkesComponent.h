#pragma once

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"

#include "version.h"
constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);

class MatchJoinerBakkesComponent: public BakkesMod::Plugin::BakkesModPlugin/*, public BakkesMod::Plugin::PluginSettingsWindow*//*, public BakkesMod::Plugin::PluginWindow*/
{

	//std::shared_ptr<bool> enabled;

	//Boilerplate
	virtual void onLoad();
	virtual void onUnload();
	void createPrivateMatch(std::string name, std::string pass);
	void joinPrivateMatch(std::string name, std::string pass);
	void gotoPrivateMatch();
	/*void setServerCvars();*/

	//https://github.com/Stanbroek/RocketPlugin/blob/main/source/RocketPlugin/RLConstants.inc
	const struct MAPS {
		std::string arctagon = "ARC_P";
		std::string forbidden_temple_day = "CHN_Stadium_Day_P";
		std::string forbidden_temple = "CHN_Stadium_P";
		std::string mannfield_night = "EuroStadium_Night_P";
		std::string mannfield = "EuroStadium_P";
		std::string mannfield_stormy = "EuroStadium_Rainy_P";
		std::string farmstead_night = "Farm_Night_P";
		std::string urban_central_haunted = "Haunted_TrainStation_P";
		std::string dunk_house = "HoopsStadium_P";
		std::string basin = "Labs_Basin_P";
		std::string pillars = "Labs_CirclePillars_P";
		std::string corridor = "Labs_Corridor_P";
		std::string cosmic_old = "Labs_Cosmic_P";
		std::string cosmic_new = "Labs_Cosmic_V4_P";
		std::string double_goal_old = "Labs_DoubleGoal_P";
		std::string double_goal_new = "Labs_DoubleGoal_V2_P";
		std::string galleon_retro = "Labs_Galleon_Mast_P";
		std::string galleon = "Labs_Galleon_P";
		std::string loophole = "Labs_Holyfield_P";
		std::string octagon_new = "Labs_Octagon_02_P";
		std::string octagon_old = "Labs_Octagon_P";
		std::string underpass = "Labs_Underpass_P";
		std::string utopia_retro = "Labs_Utopia_P";
		std::string tokyo_underpass = "NeoTokyo_P";
		std::string neo_tokyo = "NeoTokyo_Standard_P";
		std::string beckwith_park_midnight = "Park_Night_P";
		std::string beckwith_park = "Park_P";
		std::string beckwith_park_stormy = "Park_Rainy_P";
		std::string core_707 = "ShatterShot_P";
		std::string dfh_stadium_stormy = "Stadium_Foggy_P";
		std::string dfh_stadium = "Stadium_P";
		std::string dfh_stadium_circuit = "Stadium_Race_Day_p";
		std::string dfh_stadium_snowy = "Stadium_Winter_P";
		std::string urban_central_dawn = "TrainStation_Dawn_P";
		std::string urban_central_night = "TrainStation_Night_P";
		std::string urban_central = "TrainStation_P";
		std::string aquadome = "Underwater_P";
		std::string utopia_coliseum_dusk = "UtopiaStadium_Dusk_P";
		std::string utopia_coliseum = "UtopiaStadium_P";
		std::string utopia_coliseum_snowy = "UtopiaStadium_Snow_P";
		std::string badlands_night = "Wasteland_Night_P";
		std::string badlands = "Wasteland_P";
		std::string starbase_arc = "arc_standard_p";
		std::string champions_field_nfl = "bb_p";
		std::string salty_shores = "beach_P";
		std::string salty_shores_night = "beach_night_p";
		std::string champions_field_day = "cs_day_p";
		std::string rivals_arena = "cs_hw_p";
		std::string champions_field = "cs_p";
		std::string mannfield_snowy = "eurostadium_snownight_p";
		std::string farmstead = "farm_p";
		std::string neon_fields = "music_p";
		std::string deadeye_canyon = "outlaw_p";
		std::string dfh_stadium_day = "stadium_day_p";
		std::string throwback_stadium_snowy = "throwbackhockey_p";
		std::string throwback_stadium = "throwbackstadium_P";
		std::string wasteland_night = "wasteland_Night_S_P";
		std::string wasteland = "wasteland_s_p";
	};



























































	// Inherited via PluginSettingsWindow
	
	/*void RenderSettings() override;
	std::string GetPluginName() override;
	void SetImGuiContext(uintptr_t ctx) override;*/
	

	// Inherited via PluginWindow
	/*

	bool isWindowOpen_ = false;
	bool isMinimized_ = false;
	std::string menuTitle_ = "MatchJoinerBakkesComponent";

	virtual void Render() override;
	virtual std::string GetMenuName() override;
	virtual std::string GetMenuTitle() override;
	virtual void SetImGuiContext(uintptr_t ctx) override;
	virtual bool ShouldBlockInput() override;
	virtual bool IsActiveOverlay() override;
	virtual void OnOpen() override;
	virtual void OnClose() override;
	
	*/
};

