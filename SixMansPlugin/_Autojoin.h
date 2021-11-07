#pragma once
#include "pch.h"
#include "SettingsComponent.h"

namespace Settings {
	struct Autojoin : Component{
		Autojoin() : Component() {};
		Autojoin(CVarManagerWrapper cm) : Component(cm, "6mAutojoinToggle") {};
		virtual void Render() override;
	};
}