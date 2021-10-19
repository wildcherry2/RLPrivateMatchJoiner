#include "pch.h"
#include "MatchJoiner.h"

std::string MatchJoiner::GetPluginName() {
	return "Match Joiner Settings";
}

void MatchJoiner::SetImGuiContext(uintptr_t ctx) {
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

void MatchJoiner::RenderSettings() {
	renderModEnabledCheckbox();
	renderAutotabEnabled();
	renderAutoretryEnabled();
	renderMapCombobox("Default Map");
	renderRegionCombobox("Default Region");
}

void MatchJoiner::renderModEnabledCheckbox() {
	CVarWrapper cv = cvarManager->getCvar("MJModEnabled");
	if (!cv) return;
	bool enabled = cv.getBoolValue();

	if (ImGui::Checkbox("Enabled", &enabled)) cv.setValue(enabled);
}
void MatchJoiner::renderAutotabEnabled() {
	CVarWrapper cv = cvarManager->getCvar("MJAutotabInToggle");
	if (!cv) return;
	bool enabled = cv.getBoolValue();

	if (ImGui::Checkbox("Autotab", &enabled)) cv.setValue(enabled);
}
void MatchJoiner::renderAutoretryEnabled() {
	CVarWrapper cv = cvarManager->getCvar("MJAutoRetryToggle");
	if (!cv) return;
	bool enabled = cv.getBoolValue();

	if (ImGui::Checkbox("Autoretry", &enabled)) {
		cv.setValue(enabled);

	}
	if (enabled) renderTimeRetry();
}
void MatchJoiner::renderTimeRetry() {
	CVarWrapper cv = cvarManager->getCvar("MJTimeBeforeRetrying");
	if (!cv) return;
	int val = cv.getIntValue();

	if (ImGui::SliderInt("Seconds to wait before retrying", &val, 10, 60)) cv.setValue(val);
}



void MatchJoiner::renderMapCombobox(std::string name) {
	CVarWrapper cv = cvarManager->getCvar("MJMapNameSelection");
	if (!cv) return;
	int current = cv.getIntValue();
	if (ImGui::Combo(name.c_str(), &current, map_normalnames, IM_ARRAYSIZE(map_normalnames))) { cv.setValue(current); }
	//tooltip saying this is default
}
void MatchJoiner::renderRegionCombobox(std::string name) {
	CVarWrapper cv = cvarManager->getCvar("MJRegion");
	if (!cv) return;
	int current = cv.getIntValue();
	if (ImGui::Combo(name.c_str(), &current, region_names, IM_ARRAYSIZE(region_names))) { cv.setValue(current); }
}



void MatchJoiner::renderQWCreate() {
	if (ImGui::Button("Create")) {
		event_code = 0;
		gameWrapper->Execute([this](GameWrapper* gw) { cvarManager->executeCommand("MJReady"); });
	}

}
//joining is broken
void MatchJoiner::renderQWJoin() {
	ImGui::SameLine();
	if (ImGui::Button("Join")) {
		event_code = 1;
		gameWrapper->Execute([this](GameWrapper* gw) { cvarManager->executeCommand("MJReady"); });
	}
}

void MatchJoiner::renderQWNameField() {
	char in[100] = "";
	std::strcpy(in, name_field_storage);
	ImGui::InputText("Server Name", in, IM_ARRAYSIZE(in), ImGuiInputTextFlags_AutoSelectAll);
	if (ImGui::IsItemEdited()) {
		std::strcpy(name_field_storage, in);
		cvarManager->getCvar("MJServerName").setValue(std::string(in));
	}
}
void MatchJoiner::renderQWPassField() {
	char in[100] = "";
	std::strcpy(in, pass_field_storage);
	ImGui::InputText("Password", in, IM_ARRAYSIZE(in), ImGuiInputTextFlags_AutoSelectAll);
	if (ImGui::IsItemEdited()) {
		std::strcpy(pass_field_storage, in);
		cvarManager->getCvar("MJServerPass").setValue(std::string(in));
	}
}
void MatchJoiner::renderQWLinkGen() {
	if (ImGui::Button("Generate Link")) {
		link = "http://localhost:6969/match?event=" + std::to_string(event_code) + "&name=" + name + "&pass=" + pass + "&region=" + std::to_string((int)region);
		cvarManager->getCvar("MJGeneratedLink").setValue(link);
		ImGui::LogToClipboard();
		ImGui::LogText(link.c_str());
		ImGui::LogFinish();
	}
}



// Do ImGui rendering here
void MatchJoiner::Render()
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

std::string MatchJoiner::GetMenuName()
{
	return "MJ";
}

std::string MatchJoiner::GetMenuTitle()
{
	return menuTitle_;
}

// Should events such as mouse clicks/key inputs be blocked so they won't reach the game
bool MatchJoiner::ShouldBlockInput()
{
	return ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard;
}

// Return true if window should be interactive
bool MatchJoiner::IsActiveOverlay()
{
	return true;
}

// Called when window is opened
void MatchJoiner::OnOpen()
{
	isWindowOpen_ = true;
}

// Called when window is closed
void MatchJoiner::OnClose()
{
	isWindowOpen_ = false;
}
/* Plugin Settings Window code here
std::string MatchJoiner::GetPluginName() {
	return "MatchJoiner";
}

void MatchJoiner::SetImGuiContext(uintptr_t ctx) {
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

// Render the plugin settings here
// This will show up in bakkesmod when the plugin is loaded at
//  f2 -> plugins -> MatchJoiner
void MatchJoiner::RenderSettings() {
	ImGui::TextUnformatted("MatchJoiner plugin settings");
}
*/

/*
// Do ImGui rendering here
void MatchJoiner::Render()
{
	if (!ImGui::Begin(menuTitle_.c_str(), &isWindowOpen_, ImGuiWindowFlags_None))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

	ImGui::End();

	if (!isWindowOpen_)
	{
		cvarManager->executeCommand("togglemenu " + GetMenuName());
	}
}

// Name of the menu that is used to toggle the window.
std::string MatchJoiner::GetMenuName()
{
	return "MatchJoiner";
}

// Title to give the menu
std::string MatchJoiner::GetMenuTitle()
{
	return menuTitle_;
}

// Don't call this yourself, BM will call this function with a pointer to the current ImGui context
void MatchJoiner::SetImGuiContext(uintptr_t ctx)
{
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

// Should events such as mouse clicks/key inputs be blocked so they won't reach the game
bool MatchJoiner::ShouldBlockInput()
{
	return ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard;
}

// Return true if window should be interactive
bool MatchJoiner::IsActiveOverlay()
{
	return true;
}

// Called when window is opened
void MatchJoiner::OnOpen()
{
	isWindowOpen_ = true;
}

// Called when window is closed
void MatchJoiner::OnClose()
{
	isWindowOpen_ = false;
}
*/
