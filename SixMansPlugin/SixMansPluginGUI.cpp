//https://bakkesmodwiki.github.io/bakkesmod_api/
//https://pthom.github.io/imgui_manual_online/manual/imgui_manual.html
#include "pch.h"
#include "SixMansPlugin.h"


std::string SixMansPlugin::GetPluginName() {
	return "6Mans Plugin Settings";
}

void SixMansPlugin::SetImGuiContext(uintptr_t ctx) {
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

void SixMansPlugin::RenderSettings() {
	renderModEnabledCheckbox();
	renderAutotabEnabled();
	renderAutoretryEnabled();
	renderMapCombobox("Default Map");
	renderRegionCombobox("Default Region");
}

void SixMansPlugin::renderModEnabledCheckbox() { 
	CVarWrapper cv = cvarManager->getCvar("6mModEnabled");
	if (!cv) return;
	bool enabled = cv.getBoolValue();

	if (ImGui::Checkbox("Enabled", &enabled)) cv.setValue(enabled);
}
void SixMansPlugin::renderAutotabEnabled() { 
	CVarWrapper cv = cvarManager->getCvar("6mAutotabInToggle");
	if (!cv) return;
	bool enabled = cv.getBoolValue();

	if (ImGui::Checkbox("Autotab", &enabled)) cv.setValue(enabled);
}
void SixMansPlugin::renderAutoretryEnabled() { 
	CVarWrapper cv = cvarManager->getCvar("6mAutoRetryToggle");
	if (!cv) return;
	bool enabled = cv.getBoolValue();

	if (ImGui::Checkbox("Autoretry", &enabled)) { 
		cv.setValue(enabled);
		
	}
	if (enabled) renderTimeRetry();
}
void SixMansPlugin::renderTimeRetry() {
	CVarWrapper cv = cvarManager->getCvar("6mTimeBeforeRetrying");
	if (!cv) return;
	int val = cv.getIntValue();

	if (ImGui::SliderInt("Seconds to wait before retrying", &val, 30, 120)) cv.setValue(val);
}



void SixMansPlugin::renderMapCombobox(std::string name) {
	CVarWrapper cv = cvarManager->getCvar("6mMapNameSelection");
	if (!cv) return;
	int current = cv.getIntValue();
	if (ImGui::Combo(name.c_str(), &current, map_normalnames, IM_ARRAYSIZE(map_normalnames))) { cv.setValue(current); }
	//tooltip saying this is default
}
void SixMansPlugin::renderRegionCombobox(std::string name){	
	CVarWrapper cv = cvarManager->getCvar("6mRegion");
	if (!cv) return;
	int current = cv.getIntValue();
	if (ImGui::Combo(name.c_str(), &current, region_names, IM_ARRAYSIZE(region_names))) { cv.setValue(current); }
}



//void SixMansPlugin::renderQWCreate() {
//	if (ImGui::Button("Create")) {
//		event_code = 0;
//		gameWrapper->Execute([this](GameWrapper* gw) { cvarManager->executeCommand("6mReady"); });
//	}
//		
//}
////joining is broken
//void SixMansPlugin::renderQWJoin() {
//	ImGui::SameLine();
//	if (ImGui::Button("Join")) {
//		event_code = 1;
//		gameWrapper->Execute([this](GameWrapper* gw) { cvarManager->executeCommand("6mReady"); });
//	}
//}
//
//void SixMansPlugin::renderQWNameField() {
//	char in[100] = ""; 
//	std::strcpy(in,name_field_storage);
//	ImGui::InputText("Server Name", in, IM_ARRAYSIZE(in), ImGuiInputTextFlags_AutoSelectAll);
//	if (ImGui::IsItemEdited()) {
//		std::strcpy(name_field_storage,in);
//		cvarManager->getCvar("6mServerName").setValue(std::string(in));
//	}
//}
//void SixMansPlugin::renderQWPassField() {
//	char in[100] = "";
//	std::strcpy(in, pass_field_storage);
//	ImGui::InputText("Password", in, IM_ARRAYSIZE(in), ImGuiInputTextFlags_AutoSelectAll);
//	if (ImGui::IsItemEdited()) {
//		std::strcpy(pass_field_storage, in);
//		cvarManager->getCvar("6mServerPass").setValue(std::string(in));
//	}
//}
//void SixMansPlugin::renderQWLinkGen() {
//	if (ImGui::Button("Generate Link")) {
//		link = "http://localhost:6969/match?event=" + std::to_string(event_code) + "&name=" + name + "&pass=" + pass + "&region=" + std::to_string((int)region);
//		cvarManager->getCvar("6mGeneratedLink").setValue(link);
//		ImGui::LogToClipboard();
//		ImGui::LogText(link.c_str());
//		ImGui::LogFinish();
//	}
//}
//
//
//
//// Do ImGui rendering here
//void SixMansPlugin::Render()
//{
//	if (!ImGui::Begin(menuTitle_.c_str(), &isWindowOpen_, ImGuiWindowFlags_None))
//	{
//		ImGui::End();
//		return;
//	}
//	//start here
//
//	renderQWNameField();
//	renderQWPassField();
//	renderMapCombobox("Map");
//	renderRegionCombobox("Region");
//	//renderQuickWindow();
//	renderQWCreate();
//	renderQWJoin();
//	renderQWLinkGen();
//
//
//	ImGui::End();
//
//	if (!isWindowOpen_)
//	{
//		cvarManager->executeCommand("togglemenu " + GetMenuName());
//		
//	}
//
//	
//}
//
//std::string SixMansPlugin::GetMenuName()
//{
//	return "6m";
//}
//
//std::string SixMansPlugin::GetMenuTitle()
//{
//	return menuTitle_;
//}
//
//// Should events such as mouse clicks/key inputs be blocked so they won't reach the game
//bool SixMansPlugin::ShouldBlockInput()
//{
//	return ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard;
//}
//
//// Return true if window should be interactive
//bool SixMansPlugin::IsActiveOverlay()
//{
//	return true;
//}
//
//// Called when window is opened
//void SixMansPlugin::OnOpen()
//{
//	isWindowOpen_ = true;
//}
//
//// Called when window is closed
//void SixMansPlugin::OnClose()
//{
//	isWindowOpen_ = false;
//}