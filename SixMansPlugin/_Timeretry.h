#pragma once
#include "pch.h"
#include "SettingsComponent.h"

namespace Settings {
	struct Timeretry : Component {
		Timeretry()/* : Component()*/ { val = 30; }
		Timeretry(CVarManagerWrapper cm) /*: Component(cm, "6mTimeBeforeRetrying")*/ {
			this->cm = &cm;
			name = "6mTimeBeforeRetrying";
			val = this->cm->getCvar(name).getIntValue();
			//this->cm->log(std::to_string(val));
		}
		virtual void Render() override;
		int val;
	};
}
