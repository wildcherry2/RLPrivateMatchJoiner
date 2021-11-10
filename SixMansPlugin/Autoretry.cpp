#include "pch.h"
#include "Autoretry.h"

using namespace Routines;

Autoretry::Autoretry(CVarManagerWrapper cm){
	enabled = cm.getCvar("6mAutoRetryToggle").getBoolValue();
	in_game = cm.getCvar("6mInGame").getBoolValue(); 
	time_to_wait = cm.getCvar("6mTimeBeforeRetrying").getIntValue();
	can_manually_back_out = cm.getCvar("6mCanBackOut").getBoolValue();
}

void Autoretry::Start(CVarManagerWrapper cvarManager,GameWrapper gameWrapper) {
	gameWrapper.SetTimeout([this](GameWrapper* gw) {
		if (in_game || can_manually_back_out) [[unlikely]] { /*countdown = false; logt("[Autoretry] In game or player backed out, unwinding recursion...");*/ return;} //need to reset these vars after
		else [[likely]] {
			//countdown = true;

			//logt("[Autoretry] Not in game, calling again..."); gotoPrivateMatch();
		} //CHANGED THIS 10/24 NEEDS BUILDING AND TESTING

		}, cvarManager.getCvar("6mTimeBeforeRetrying").getIntValue());
}