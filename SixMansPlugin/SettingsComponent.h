#pragma once
#include "pch.h"

namespace Settings {
	struct Component {
		Component();
		Component(CVarManagerWrapper cm, std::string name);
		virtual void Render();
		CVarManagerWrapper* cm = nullptr;
		std::string name;
		bool enabled;
	};
}