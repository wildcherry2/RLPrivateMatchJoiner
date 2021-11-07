#pragma once
#include "pch.h"
#include "SettingsComponent.h"

namespace Settings {
	struct Autoretry : Component {
		Autoretry() : Component() {};
		Autoretry(CVarManagerWrapper cm) : Component(cm, "6mAutoRetryToggle"){};
		virtual void Render() override;
	};
}