//https://bakkesmodwiki.github.io/bakkesmod_api/
#pragma once

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"

#include "version.h"
constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);

class MatchJoinerBakkesComponent: public BakkesMod::Plugin::BakkesModPlugin/*, public BakkesMod::Plugin::PluginSettingsWindow*//*, public BakkesMod::Plugin::PluginWindow*/
{
public:
	//std::shared_ptr<bool> enabled;

	//Boilerplate
	virtual void onLoad();
	virtual void onUnload();
	void createPrivateMatch(std::string name, std::string pass, std::string map, int region);
	void joinPrivateMatch(std::string name, std::string pass);
	void gotoPrivateMatch();
	Region getRegion(int region);
	/*void setServerCvars();*/

	//https://github.com/Stanbroek/RocketPlugin/blob/main/source/RocketPlugin/RLConstants.inc
	const struct MAPS {
		const std::string arctagon = "ARC_P";
		const std::string forbidden_temple_day = "CHN_Stadium_Day_P";
		const std::string forbidden_temple = "CHN_Stadium_P";
		const std::string mannfield_night = "EuroStadium_Night_P";
		const std::string mannfield = "EuroStadium_P";
		const std::string mannfield_stormy = "EuroStadium_Rainy_P";
		const std::string farmstead_night = "Farm_Night_P";
		const std::string urban_central_haunted = "Haunted_TrainStation_P";
		const std::string dunk_house = "HoopsStadium_P";
		const std::string basin = "Labs_Basin_P";
		const std::string pillars = "Labs_CirclePillars_P";
		const std::string corridor = "Labs_Corridor_P";
		const std::string cosmic_old = "Labs_Cosmic_P";
		const std::string cosmic_new = "Labs_Cosmic_V4_P";
		const std::string double_goal_old = "Labs_DoubleGoal_P";
		const std::string double_goal_new = "Labs_DoubleGoal_V2_P";
		const std::string galleon_retro = "Labs_Galleon_Mast_P";
		const std::string galleon = "Labs_Galleon_P";
		const std::string loophole = "Labs_Holyfield_P";
		const std::string octagon_new = "Labs_Octagon_02_P";
		const std::string octagon_old = "Labs_Octagon_P";
		const std::string underpass = "Labs_Underpass_P";
		const std::string utopia_retro = "Labs_Utopia_P";
		const std::string tokyo_underpass = "NeoTokyo_P";
		const std::string neo_tokyo = "NeoTokyo_Standard_P";
		const std::string beckwith_park_midnight = "Park_Night_P";
		const std::string beckwith_park = "Park_P";
		const std::string beckwith_park_stormy = "Park_Rainy_P";
		const std::string core_707 = "ShatterShot_P";
		const std::string dfh_stadium_stormy = "Stadium_Foggy_P";
		const std::string dfh_stadium = "Stadium_P";
		const std::string dfh_stadium_circuit = "Stadium_Race_Day_p";
		const std::string dfh_stadium_snowy = "Stadium_Winter_P";
		const std::string urban_central_dawn = "TrainStation_Dawn_P";
		const std::string urban_central_night = "TrainStation_Night_P";
		const std::string urban_central = "TrainStation_P";
		const std::string aquadome = "Underwater_P";
		const std::string utopia_coliseum_dusk = "UtopiaStadium_Dusk_P";
		const std::string utopia_coliseum = "UtopiaStadium_P";
		const std::string utopia_coliseum_snowy = "UtopiaStadium_Snow_P";
		const std::string badlands_night = "Wasteland_Night_P";
		const std::string badlands = "Wasteland_P";
		const std::string starbase_arc = "arc_standard_p";
		const std::string champions_field_nfl = "bb_p";
		const std::string salty_shores = "beach_P";
		const std::string salty_shores_night = "beach_night_p";
		const std::string champions_field_day = "cs_day_p";
		const std::string rivals_arena = "cs_hw_p";
		const std::string champions_field = "cs_p";
		const std::string mannfield_snowy = "eurostadium_snownight_p";
		const std::string farmstead = "farm_p";
		const std::string neon_fields = "music_p";
		const std::string deadeye_canyon = "outlaw_p";
		const std::string dfh_stadium_day = "stadium_day_p";
		const std::string throwback_stadium_snowy = "throwbackhockey_p";
		const std::string throwback_stadium = "throwbackstadium_P";
		const std::string wasteland_night = "wasteland_Night_S_P";
		const std::string wasteland = "wasteland_s_p";
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

