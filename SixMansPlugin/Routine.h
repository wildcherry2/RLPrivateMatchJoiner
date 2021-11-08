#pragma once
#include "pch.h"

namespace Routines {
	struct Routine {
		Routine(){};
		virtual void Start(CVarManagerWrapper cvarManager, GameWrapper gameWrapper){};
		bool enabled = true;
	};
}