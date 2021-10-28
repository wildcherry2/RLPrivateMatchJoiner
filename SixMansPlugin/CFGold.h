#pragma once
#include "pch.h"
#include "bakkesmod/plugin/bakkesmodsdk.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"
#include "bakkesmod/wrappers/cvarwrapper.h"
#include "nlohmann/json.hpp"
#include <fstream>

class Config {
	public:
		Config(GameWrapper gameWrapper, CVarManagerWrapper cvarManager, const size_t num_cvars);
		void loadConfig(const std::string str_pers[]);
		void loadConfig(std::string& cvar);
		void saveConfig(const std::string str_pers[]);
		void saveConfig(std::string& cvar);
	private: 
		nlohmann::json saved_settings_json;
		GameWrapper* gameWrapper;
		CVarManagerWrapper* cvarManager;
		std::ofstream os;
		std::ifstream is;
		std::string path;
		size_t num_cvars;
};
