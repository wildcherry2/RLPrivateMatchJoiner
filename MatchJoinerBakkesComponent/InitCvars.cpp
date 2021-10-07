#include "pch.h"
#include "MatchJoinerBakkesComponent.h"

void MatchJoinerBakkesComponent::initInternalCvars() {
	cvarManager->registerCvar("MJEventType", "join", "Set to 0 for create mode, 1 for join mode", true, true, 0, true, 1, false);
	cvarManager->registerCvar("MJServerName", "", "Enter the server name", true, false, false, false);
	cvarManager->registerCvar("MJServerPass", "", "Enter the server password", true, false, false, false);
	cvarManager->registerCvar("MJMap", map_codenames[17], "Enter internal map names (see MapsStruct.h for names)", true, false, false, true); //gonna want to save this choice
	cvarManager->registerCvar("MJRegion", "0", "Enter the region code (0-9)", true, true, 0, true, 9, false);
	cvarManager->registerNotifier("MJGotoMatch", [this](std::vector<std::string> args) {
		//first arg is cvar name, so skip
		if (args.size() == 4) {
			cvarManager->getCvar("MJEventType").setValue(args[1]);
			cvarManager->getCvar("MJServerName").setValue(args[2]);
			cvarManager->getCvar("MJServerPass").setValue(args[3]);
			gotoPrivateMatch();
		}
		else if (args.size() == 3) {
			cvarManager->getCvar("MJEventType").setValue(args[1]);
			std::string* str = new std::string(args[2]);

			//only works for rank b
			std::regex* namereg = new std::regex("(?!Username:\\s)(?:[b]\\d{1,})", std::regex_constants::ECMAScript);
			std::regex* passreg = new std::regex("(?:(\\b[a-z0-9]{4}\\b)(?!\\bUsername:\\s[b]\\d{1,}Password:\\s\\b))", std::regex_constants::ECMAScript);
			std::smatch* namematch = new std::smatch();
			std::smatch* passmatch = new std::smatch();

			regex_search(*str, *namematch, *namereg);
			regex_search(*str, *passmatch, *passreg);

			cvarManager->getCvar("MJServerName").setValue(namematch[0].str());
			cvarManager->getCvar("MJServerPass").setValue(passmatch[0].str());

			delete str, namereg, passreg, namematch, passmatch;
		}
		else gotoPrivateMatch();
		}, "", PERMISSION_ALL);
}

void MatchJoinerBakkesComponent::initGuiCvars() {
	cvarManager->registerCvar("MJModEnabled", "1", "Is mod enabled?", false, true, 0, true, 1, false);
	cvarManager->registerCvar("MJExtMapNameSelection", "18", "Enter map name", true, false, false, false);
	cvarManager->registerCvar("MJCreateBtnClicked", "0", "", false, true, 0, true, 1, false);
	cvarManager->registerCvar("MJIsQuickMatchWindowEnabled", "0", "Toggles quick private match join/create window", true, true, 0, true, 1, false); //change to notifier
}

void MatchJoinerBakkesComponent::initServerCvars() {
	cvarManager->registerNotifier("MJServerEnabled", [this](std::vector<std::string> args) {
		
		}, "", PERMISSION_ALL);
}