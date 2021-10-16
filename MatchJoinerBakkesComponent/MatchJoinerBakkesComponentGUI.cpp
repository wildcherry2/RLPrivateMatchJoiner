//https://bakkesmodwiki.github.io/bakkesmod_api/
//https://pthom.github.io/imgui_manual_online/manual/imgui_manual.html
#include "pch.h"
#include "MatchJoinerBakkesComponent.h"
#include <cstring>
#include <string>


std::string MatchJoinerBakkesComponent::GetPluginName() {
	return "Match Joiner Settings";
}

void MatchJoinerBakkesComponent::SetImGuiContext(uintptr_t ctx) {
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

void MatchJoinerBakkesComponent::RenderSettings() {
	renderModEnabledCheckbox();
	renderMapCombobox("Default map");
	renderRegionCombobox("Default region");
	//renderQuickWindow();
	
	renderQWNameField();
	renderQWPassField();
	renderQWCreate();
	renderQWJoin();

	//line 3267 in the demo can set the text on the left 
	//this block will compose the window, in f2 menu for now
	/*cvarManager->getCvar("MJIsQuickMatchWindowEnabled").addOnValueChanged([this]{
		
		}));*/

	
}

//broken
void MatchJoinerBakkesComponent::renderModEnabledCheckbox() {
	CVarWrapper cv = cvarManager->getCvar("MJModEnabled");
	if (!cv) return;
	bool enabled = cv.getBoolValue();

	if (ImGui::Checkbox("Enabled", &enabled)) cv.setValue(enabled);
}

void MatchJoinerBakkesComponent::renderMapCombobox(std::string name) {
	
	CVarWrapper cv = cvarManager->getCvar("MJMapNameSelection");
	if (!cv) return;
	int current = cv.getIntValue();
	if(ImGui::Combo(name.c_str(),&current,map_normalnames,IM_ARRAYSIZE(map_normalnames))) cv.setValue(current);
	//tooltip saying this is default
}

void MatchJoinerBakkesComponent::renderRegionCombobox(std::string name){
	CVarWrapper cv = cvarManager->getCvar("MJRegion");
	if (!cv) return;
	int current = cv.getIntValue();
	if (ImGui::Combo(name.c_str(), &current, region_names, IM_ARRAYSIZE(region_names))) cv.setValue(current);
}

//doesnt work atm
void MatchJoinerBakkesComponent::renderQWCreate() {
	//CVarWrapper cv = cvarManager->getCvar("MJCreateBtnClicked");
	
	ImGui::Button("Create");
	if(ImGui::IsItemActive())
		gameWrapper->Execute([this](GameWrapper* gw) {event_code = 0; cvarManager->executeCommand("MJReady"); });
	//ImGui::set
};
void MatchJoinerBakkesComponent::renderQWJoin() {

};



void MatchJoinerBakkesComponent::renderQWNameField() { //put a flag for auto selecting all when clicked
	char in[100] = ""; 
	std::strcpy(in,name_field_storage);
	if (ImGui::InputText("Name: ", in, IM_ARRAYSIZE(in)/*,ImGuiInputTextFlags_CallbackAlways,setVars*/)) {
		std::strcpy(name_field_storage,in);
		cvarManager->getCvar("MJServerName").setValue(std::string(in));
	}
}

void MatchJoinerBakkesComponent::renderQWPassField() {
	char in[100] = "";
	std::strcpy(in, pass_field_storage);
	if (ImGui::InputText("Pass: ", in, IM_ARRAYSIZE(in))) {
		std::strcpy(pass_field_storage, in);
		cvarManager->getCvar("MJServerPass").setValue(std::string(in));
	}
}

//void MatchJoinerBakkesComponent::getMapArray(char** maps) {
//	char* test1[4] = "test";
//	std::string test2 = "test2";
//	maps[0] = test1;
//}
/*
// Do ImGui rendering here
void MatchJoinerBakkesComponent::Render()
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
std::string MatchJoinerBakkesComponent::GetMenuName()
{
	return "MatchJoinerBakkesComponent";
}

// Title to give the menu
std::string MatchJoinerBakkesComponent::GetMenuTitle()
{
	return menuTitle_;
}

// Don't call this yourself, BM will call this function with a pointer to the current ImGui context
void MatchJoinerBakkesComponent::SetImGuiContext(uintptr_t ctx)
{
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

// Should events such as mouse clicks/key inputs be blocked so they won't reach the game
bool MatchJoinerBakkesComponent::ShouldBlockInput()
{
	return ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard;
}

// Return true if window should be interactive
bool MatchJoinerBakkesComponent::IsActiveOverlay()
{
	return true;
}

// Called when window is opened
void MatchJoinerBakkesComponent::OnOpen()
{
	isWindowOpen_ = true;
}

// Called when window is closed
void MatchJoinerBakkesComponent::OnClose()
{
	isWindowOpen_ = false;
}
*/
