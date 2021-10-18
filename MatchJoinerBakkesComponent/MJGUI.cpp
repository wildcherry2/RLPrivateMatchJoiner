//https://bakkesmodwiki.github.io/bakkesmod_api/
//https://pthom.github.io/imgui_manual_online/manual/imgui_manual.html
#include "pch.h"
#include "MJ.h"


std::string MJ::GetPluginName() {
	return "Match Joiner Settings";
}

void MJ::SetImGuiContext(uintptr_t ctx) {
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

void MJ::RenderSettings() {
	renderModEnabledCheckbox();
	renderAutotabEnabled();
}

//broken
void MJ::renderModEnabledCheckbox() { //tie things to cvars, unregister cvars for options
	CVarWrapper cv = cvarManager->getCvar("MJModEnabled");
	if (!cv) return;
	bool enabled = cv.getBoolValue();

	if (ImGui::Checkbox("Enabled", &enabled)) cv.setValue(enabled);
}
void MJ::renderAutotabEnabled() { //tie things to cvars, unregister cvars for options
	CVarWrapper cv = cvarManager->getCvar("MJAutotabInToggle");
	if (!cv) return;
	bool enabled = cv.getBoolValue();

	if (ImGui::Checkbox("Autotab", &enabled)) cv.setValue(enabled);
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
	if (ImGui::Button("Create")) {
		event_code = 0;
		gameWrapper->Execute([this](GameWrapper* gw) { cvarManager->executeCommand("MJReady"); });
	}
		
}
//joining is broken
void MJ::renderQWJoin() {
	ImGui::SameLine();
	if (ImGui::Button("Join")) {
		event_code = 1;
		gameWrapper->Execute([this](GameWrapper* gw) { cvarManager->executeCommand("MJReady"); });
	}
}

void MJ::renderQWNameField() {
	char in[100] = ""; 
	std::strcpy(in,name_field_storage);
	ImGui::InputText("Server Name", in, IM_ARRAYSIZE(in), ImGuiInputTextFlags_AutoSelectAll);
	if (ImGui::IsItemEdited()) {
		std::strcpy(name_field_storage,in);
		cvarManager->getCvar("MJServerName").setValue(std::string(in));
	}
}
void MJ::renderQWPassField() {
	char in[100] = "";
	std::strcpy(in, pass_field_storage);
	ImGui::InputText("Password", in, IM_ARRAYSIZE(in), ImGuiInputTextFlags_AutoSelectAll);
	if (ImGui::IsItemEdited()) {
		std::strcpy(pass_field_storage, in);
		cvarManager->getCvar("MJServerPass").setValue(std::string(in));
	}
}
void MJ::renderQWLinkGen() {
	if (ImGui::Button("Generate Link")) {
		link = "http://localhost:6969/match?event=" + std::to_string(event_code) + "&name=" + name + "&pass=" + pass + "&region=" + std::to_string((int)region);
		cvarManager->getCvar("MJGeneratedLink").setValue(link);
		ImGui::LogToClipboard();
		ImGui::LogText(link.c_str());
		ImGui::LogFinish();
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
	renderQWLinkGen();


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