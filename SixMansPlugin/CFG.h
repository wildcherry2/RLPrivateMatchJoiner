#pragma once
#include "pch.h"
//#include "bakkesmod/wrappers/cvarmanagerwrapper.h"
//#include "bakkesmod/wrappers/cvarwrapper.h"

class CFG {
	public:
		CFG();
		CFG(GameWrapper& gw);
		void loadConfig(std::vector<std::string> cvars, CVarManagerWrapper& cm);
		void saveConfig(std::vector<std::string> cvars, CVarManagerWrapper& cm);
		void initCFG(CVarManagerWrapper& cm);
		//static void logt(std::string text, CVarManagerWrapper& cm, std::ofstream& ls, std::string logpath);
		//void setPath(std::string path);
		std::vector<std::string> cvarbuf;
		bool loading = true;
	private:
		
		nlohmann::json set_file;
		std::ifstream is;
		std::ofstream os;
		//const std::string lpath = gameWrapper->GetDataFolder().string() + "\\config.json";
		std::string path/* = gameWrapper->GetDataFolder().string() + "\\6m\\config.json"*/;
};