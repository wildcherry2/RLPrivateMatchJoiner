#pragma once
#include "pch.h"
#include "Routine.h"

namespace Routines {
	struct Autoretry : Routine {
		Autoretry() : Routine() {};
		Autoretry(CVarManagerWrapper cm);
		virtual void Start(CVarManagerWrapper cvarManager,GameWrapper gameWrapper) override;

		//bool enabled = true;
		bool in_game = false;
		size_t time_to_wait = 45;
		bool is_enabled_autoretry = true;
		bool can_manually_back_out = false;
	};
}