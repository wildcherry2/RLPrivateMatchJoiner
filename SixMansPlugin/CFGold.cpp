#include "pch.h"
#include "CFG.h"

Config::Config(GameWrapper gameWrapper, CVarManagerWrapper cvarManager, const size_t num_cvars) {
	this->gameWrapper = &gameWrapper;
	this->cvarManager = &cvarManager;
	this->num_cvars = num_cvars;
	path = this->gameWrapper->GetDataFolder().string() + "\\config.json";
}
//6mMapNameSelection int,6mAutotabInToggle bool
void Config::loadConfig(const std::string str_pers[]) {
	if(std::filesystem::exists(path)) is.open(path);
	is >> saved_settings_json;
	is.close();
	for (size_t it = 0; it < num_cvars; it++) {
		cvarManager->getCvar(str_pers[it]).setValue(saved_settings_json[str_pers[it]].get<std::string>());
	}
}

void Config::loadConfig(std::string& cvar) {
	if (std::filesystem::exists(path)) is.open(path); //probably wont work, need to read into separate json
	is >> saved_settings_json;
	//CVarWrapper* cw; 
	gameWrapper->Execute([this,cvar](GameWrapper* gw){
		cvarManager->getCvar(cvar);
		});
	//cw->setValue(saved_settings_json[cvar].get<std::string>());
	is.close();
	
}

void Config::saveConfig(const std::string str_pers[]) {
	//saved_settings_json["6mMapNameSelection"] = cvarManager->getCvar("6mMapNameSelection").getStringValue();
	for (size_t it = 0; it < num_cvars; it++) {
		saved_settings_json[str_pers[it]] = cvarManager->getCvar(str_pers[it]).getStringValue();
	}
	os.open(path);
	os << saved_settings_json << std::endl;
	os.close();
}

void Config::saveConfig(std::string& cvar) {
	saved_settings_json[cvar] = cvarManager->getCvar(cvar).getStringValue();
	os.open(path);
	os << saved_settings_json << std::endl;
	os.close();
}