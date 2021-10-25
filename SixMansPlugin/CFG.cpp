#include "pch.h"
#include "SixMansPlugin.h"

void SixMansPlugin::cfgRead(){
	try { //std::filesystem::exists
		std::ifstream cfg_file;
		cfg_file.open(gameWrapper->GetDataFolder() / "smp.cfg");
		std::stack<std::string> cvar_stack;
	}
	catch (std::ios_base::failure e) {
		LOG("[CFG Manager] Error reading from cfg!");
	}
}

void SixMansPlugin::cfgWrite() {

}