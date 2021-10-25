#include "pch.h"
#include "CFG.h"

Config::Config(GameWrapper gameWrapper, CVarManagerWrapper cvarManager) {
	this->gameWrapper = &gameWrapper;
	this->cvarManager = &cvarManager;
	//os = std::ofstream("config.json");
	//is = std::ifstream("config.json");
}
//6mMapNameSelection int,6mAutotabInToggle bool
void Config::loadConfig() {
	std::ifstream is;
	std::string path = gameWrapper->GetDataFolder().string() + "\\config.json";
	is.open(path);
	//if(!is.is_open()) is.open("config.json");
	is >> saved_settings_json;
	LOG("JSON 6mMapNameSelection = " + saved_settings_json["6mMapNameSelection"].get<std::string>());
	cvarManager->getCvar("6mMapNameSelection").setValue(saved_settings_json["6mMapNameSelection"].get<std::string>());
	LOG("CVAR 6mMapNameSelection = " + cvarManager->getCvar("6mMapNameSelection").getStringValue());
	is.close();
	
}

void Config::saveConfig() {
	saved_settings_json["6mMapNameSelection"] = cvarManager->getCvar("6mMapNameSelection").getStringValue();
	LOG("JSON 6mMapNameSelection = " + saved_settings_json["6mMapNameSelection"].get<std::string>());

	std::ofstream o;
	std::string path = gameWrapper->GetDataFolder().string() + "\\config.json";
	o.open(path);
	if (o.is_open()) LOG("opened");
	//if(!o.is_open()) o.open("config.json");
	o << saved_settings_json << std::endl;
	LOG("CVAR 6mMapNameSelection = " + cvarManager->getCvar("6mMapNameSelection").getStringValue());
	o.close();
}