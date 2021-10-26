#include "pch.h"
#include "SixMansPlugin.h"

void SixMansPlugin::loadConfig(std::vector<std::string> cvars) {
	try {
		for (auto it = cvars.begin(); it != cvars.end(); it++) {
			cvarManager->getCvar(*it).setValue(set_file[*it].get<std::string>());
		}
	}
	catch (std::exception e) {
		LOG("[CFG Manager] Error loading vars from json!");
	}
}

void SixMansPlugin::saveConfig(std::vector<std::string> cvars) {
	try {
		for (auto it = cvars.begin(); it != cvars.end(); it++) {
			set_file[*it] = cvarManager->getCvar(*it).getStringValue();
		}
		os.open(path);
		os << set_file;
		os.close();
	}
	catch (std::exception e) {
		LOG("[CFG Manager] Error saving vars to json!");
	}
}

void SixMansPlugin::initCFGMan() {
	if (std::filesystem::exists(path)) {
		is.open(path);
		is >> set_file;
		is.close();
	}
	else LOG("[CFG Manager] json does not exist!");
}