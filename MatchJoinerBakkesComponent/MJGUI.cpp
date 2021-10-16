//https://bakkesmodwiki.github.io/bakkesmod_api/
//https://pthom.github.io/imgui_manual_online/manual/imgui_manual.html
#include "pch.h"
#include "MJ.h"
#include <cstring>
#include <string>


std::string MJ::GetPluginName() {
	return "Match Joiner Settings";
}

void MJ::SetImGuiContext(uintptr_t ctx) {
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

void MJ::RenderSettings() { //put name/pass first
	renderModEnabledCheckbox();
	//add toggle menu button here
}

//broken
void MJ::renderModEnabledCheckbox() {
	CVarWrapper cv = cvarManager->getCvar("MJModEnabled");
	if (!cv) return;
	bool enabled = cv.getBoolValue();

	if (ImGui::Checkbox("Enabled", &enabled)) cv.setValue(enabled);
}
void MJ::renderMapCombobox(std::string name) {
	CVarWrapper cv = cvarManager->getCvar("MJMapNameSelection");
	if (!cv) return;
	int current = cv.getIntValue();
	if (ImGui::Combo(name.c_str(), &current, map_normalnames, IM_ARRAYSIZE(map_normalnames))) { cv.setValue(current); }
	//tooltip saying this is default
}
void MJ::renderRegionCombobox(std::string name){	
	CVarWrapper cv = cvarManager->getCvar("MJRegion");
	if (!cv) return;
	int current = cv.getIntValue();
	if (ImGui::Combo(name.c_str(), &current, region_names, IM_ARRAYSIZE(region_names))) { cv.setValue(current); }
}



void MJ::renderQWCreate() {
	if(ImGui::Button("Create"))
		gameWrapper->Execute([this](GameWrapper* gw) {event_code = 0; cvarManager->executeCommand("MJReady"); });
}
void MJ::renderQWJoin() {
	ImGui::SameLine();
	if (ImGui::Button("Join"))
		gameWrapper->Execute([this](GameWrapper* gw) {event_code = 1; cvarManager->executeCommand("MJReady"); });
}
void MJ::renderQWNameField() {
	char in[100] = ""; 
	std::strcpy(in,name_field_storage);
	if (ImGui::InputText("Server Name", in, IM_ARRAYSIZE(in),ImGuiInputTextFlags_AutoSelectAll)) {
		std::strcpy(name_field_storage,in);
		cvarManager->getCvar("MJServerName").setValue(std::string(in));
	}
}
void MJ::renderQWPassField() {
	char in[100] = "";
	std::strcpy(in, pass_field_storage);
	if (ImGui::InputText("Password", in, IM_ARRAYSIZE(in), ImGuiInputTextFlags_AutoSelectAll)) {
		std::strcpy(pass_field_storage, in);
		cvarManager->getCvar("MJServerPass").setValue(std::string(in));
	}
}


// Do ImGui rendering here
void MJ::Render()
{
	if (!ImGui::Begin(menuTitle_.c_str(), &isWindowOpen_, ImGuiWindowFlags_None))
	{
		ImGui::End();
		return;
	}
	//start here

	renderQWNameField();
	renderQWPassField();
	renderMapCombobox("Map");
	renderRegionCombobox("Region");
	//renderQuickWindow();
	renderQWCreate();
	renderQWJoin();



	ImGui::End();

	if (!isWindowOpen_)
	{
		cvarManager->executeCommand("togglemenu " + GetMenuName());
		
	}

	
}

std::string MJ::GetMenuName()
{
	return "mj";
}

std::string MJ::GetMenuTitle()
{
	return menuTitle_;
}

// Should events such as mouse clicks/key inputs be blocked so they won't reach the game
bool MJ::ShouldBlockInput()
{
	return ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard;
}

// Return true if window should be interactive
bool MJ::IsActiveOverlay()
{
	return true;
}

// Called when window is opened
void MJ::OnOpen()
{
	isWindowOpen_ = true;
}

// Called when window is closed
void MJ::OnClose()
{
	isWindowOpen_ = false;
}

