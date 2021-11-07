#include "pch.h"
#include "CFG.h"

CFG::CFG() {
	path = "";
}

CFG::CFG(GameWrapper& gw) {
	path = gw.GetDataFolder().string() + "\\6m\\config.json";
}

void CFG::loadConfig(std::vector<std::string> cvars, CVarManagerWrapper& cm) {
	/*try {*/
	[[unlikely]] for (auto it = cvars.begin(); it != cvars.end(); it++) {

		cm.getCvar(*it).setValue(set_file[*it].get<std::string>());
		cm.log("[CFG Manager] Loaded " + *it + " = " + cm.getCvar(*it).getStringValue());

	}
	//}
	/*catch (std::exception e) {
		cm.log("[CFG Manager] Error loading vars from json!");
	}*/
}

void CFG::saveConfig( std::vector<std::string> cvars, CVarManagerWrapper& cm) {
	try {
		[[likely]] for (auto it = cvars.begin(); it != cvars.end(); it++) {
			set_file[*it] = cm.getCvar(*it).getStringValue();
			cm.log("[CFG Manager] Saved " + *it + " = " + cm.getCvar(*it).getStringValue());
		}
		os.open(path);
		os << set_file;
		os.close();
	}
	catch (std::exception e) {
		cm.log("[CFG Manager] Error saving vars to json!");
	}
}

void CFG::initCFG(CVarManagerWrapper& cm) {
	if (std::filesystem::exists(path)) {
		is.open(path);
		is >> set_file;
		is.close();
	}
	else cm.log("[CFG Manager] Json does not exist!");

	
	cm.log("[CFG Manager] Loading persistent cvars from cfg...");
	cm.executeCommand("6mLoadCvar \"6mMapNameSelection\"");
	cm.executeCommand("6mLoadCvar \"6mAutotabInToggle\"");
	//cvarManager->executeCommand("6mLoadCvar \"6mModEnabled\"");
	cm.executeCommand("6mLoadCvar \"6mTimeBeforeRetrying\"");
	cm.executeCommand("6mLoadCvar \"6mAutoRetryToggle\"");
	cm.executeCommand("6mLoadCvar \"6mAutojoinToggle\"");

	loading = false;
}

//void CFG::cm.log(std::string text, CVarManagerWrapper& cm, std::ofstream& ls, std::string logpath) {
//	ls.open(logpath, std::ios::app);
//	ls << text << std::endl;
//	ls.close();
//
//	cm.log(text);
//}

