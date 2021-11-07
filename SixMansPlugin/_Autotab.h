#pragma once
#include "pch.h"
#include "SettingsComponent.h"

namespace Settings {
	struct Autotab : Component {
		Autotab() : Component() {};
		Autotab(CVarManagerWrapper cm) : Component(cm, "6mAutotabInToggle"){};
		virtual void Render() override;
	};
}