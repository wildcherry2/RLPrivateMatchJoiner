#include "pch.h"
#include "SettingsComponent.h"

using namespace Settings;

Component::Component() { enabled = true; }
Component::Component(CVarManagerWrapper cm, std::string name) {
	this->cm = &cm;
	enabled = this->cm->getCvar(name).getBoolValue();
	this->name = name;
}
void Component::Render() {} 