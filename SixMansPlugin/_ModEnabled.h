#pragma once
#include "pch.h"
#include "SettingsComponent.h"

namespace Settings {
	struct ModEnabled : Component {
		ModEnabled() : Component(){};
		ModEnabled(CVarManagerWrapper cm) : Component(cm, "6mModEnabled"){};
		virtual void Render() override;
	};
}