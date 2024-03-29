#include "pch.h"
#include "MatchJoiner.h"


BAKKESMOD_PLUGIN(MatchJoiner, "write a plugin description here", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void MatchJoiner::onLoad()
{
	_globalCvarManager = cvarManager;
	initCvars();
	startServer();
}

void MatchJoiner::onUnload()
{
	cvarManager->executeCommand("MJDisableServer");
	cvarManager->getCvar("MJEndMonitor").setValue("1");
	cvarManager->log("Match joiner unloaded.");
}

void MatchJoiner::gotoPrivateMatch() {
	cvarManager->log("[gotoPrivateMatch] called.");
	if (!in_game && mw) {
		if (event_code == 0) {
			CustomMatchSettings cm;
			CustomMatchTeamSettings blue;
			CustomMatchTeamSettings red;

			cm.GameTags = gametags;
			cm.MapName = cvarManager->getCvar("MJMap").getStringValue();
			cm.ServerName = cvarManager->getCvar("MJServerName").getStringValue();
			cm.Password = cvarManager->getCvar("MJServerPass").getStringValue();
			cm.BlueTeamSettings = blue;
			cm.OrangeTeamSettings = red;
			cm.bClubServer = false;

			cvarManager->log("[gotoPrivateMatch] Creating with name: " + cm.ServerName + "and pass: " + cm.Password);
			mw.CreatePrivateMatch(region, cm);
		}
		else if (event_code == 1) {
			cvarManager->log("[gotoPrivateMatch] Joining with name: " + name + "and pass: " + pass);
			mw.JoinPrivateMatch(cvarManager->getCvar("MJServerName").getStringValue(), cvarManager->getCvar("MJServerPass").getStringValue());
		}
		else cvarManager->log("[gotoPrivateMatch] Invalid event code!");
	}
	if (is_enabled_autoretry) {
		gameWrapper->SetTimeout([this](GameWrapper* gw) {
			if (!gameWrapper->IsInOnlineGame() && !cvarManager->getCvar("MJEndRecursiveJoin").getBoolValue()) { cvarManager->log("[gotoPrivateMatch] Checking..."); gotoPrivateMatch(); return; }
			else { cvarManager->log("[gotoPrivateMatch] Success."); cvarManager->getCvar("MJEndRecursiveJoin").setValue("0"); cvarManager->getCvar("MJEndMonitor").setValue("1"); return; }

			}, cvarManager->getCvar("MJTimeBeforeRetrying").getIntValue());
	}

}

Region MatchJoiner::getRegion(int region) {
	switch (region) {
	case 0: return Region::USE;
	case 1: return Region::EU;
	case 2: return Region::USW;
	case 3: return Region::ASC;
	case 4: return Region::ASM;
	case 5: return Region::JPN;
	case 6: return Region::ME;
	case 7: return Region::OCE;
	case 8: return Region::SAF;
	case 9: return Region::SAM;
	default: return Region::USE;
	}
}

void MatchJoiner::monitorOnlineState() {
	monitor = std::thread([this]() {
		while (mon_running && !cvarManager->getCvar("MJEndMonitor").getBoolValue()) {
			if (!gameWrapper->IsInOnlineGame()) {
				cvarManager->log("[Monitor] not in online game...");
				in_game = false;
			}
			else {
				cvarManager->log("[Monitor] detected online game!");
				cvarManager->log("[Monitor] terminating monitor...");
				cvarManager->getCvar("MJEndMonitor").setValue("0");
				in_game = true;
				return;
			}
			std::this_thread::sleep_for(std::chrono::seconds(2));
		}
		cvarManager->getCvar("MJEndMonitor").setValue("0");
		return;
		});
	monitor.detach();
}