#pragma once
#include "pch.h"
#include "bakkesmod/plugin/bakkesmodsdk.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"
#include "nlohmann/json.hpp"
#include <fstream>

class Config {
	public:
		Config(GameWrapper gameWrapper, CVarManagerWrapper cvarManager);
		void loadConfig();
		void saveConfig();
	private: 
		nlohmann::json saved_settings_json;
		GameWrapper* gameWrapper;
		CVarManagerWrapper* cvarManager;
		//std::ofstream os;
		//std::ifstream is;
};
