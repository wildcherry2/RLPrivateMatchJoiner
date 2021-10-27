#include "pch.h"
#include "SixMansPlugin.h"

void SixMansPlugin::loadConfig(std::vector<std::string> cvars) {
	/*try {*/
	for (auto it = cvars.begin(); it != cvars.end(); it++) [[unlikely]] {

		cvarManager->getCvar(*it).setValue(set_file[*it].get<std::string>());
		LOG("[CFG Manager] Loaded " + *it + " = " + cvarManager->getCvar(*it).getStringValue());

	}
	//}
	/*catch (std::exception e) {
		LOG("[CFG Manager] Error loading vars from json!");
	}*/
}

void SixMansPlugin::saveConfig( std::vector<std::string> cvars) {
	try {
		for (auto it = cvars.begin(); it != cvars.end(); it++) [[likely]] {
			set_file[*it] = cvarManager->getCvar(*it).getStringValue();
			LOG("[CFG Manager] Saved " + *it + " = " + cvarManager->getCvar(*it).getStringValue());
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
	if (std::filesystem::exists(path)) [[likely]] {
		is.open(path);
		is >> set_file;
		is.close();
	}
	else [[unlikely]] LOG("[CFG Manager] json does not exist!");

	cvarManager->executeCommand("6mLoadCvar \"6mMapNameSelection\"");
	cvarManager->executeCommand("6mLoadCvar \"6mAutotabInToggle\"");
	//cvarManager->executeCommand("6mLoadCvar \"6mModEnabled\"");
	cvarManager->executeCommand("6mLoadCvar \"6mTimeBeforeRetrying\"");
	cvarManager->executeCommand("6mLoadCvar \"6mAutoRetryToggle\"");
}