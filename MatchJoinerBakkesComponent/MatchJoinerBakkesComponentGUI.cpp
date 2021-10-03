//https://bakkesmodwiki.github.io/bakkesmod_api/
#include "pch.h"
#include "MatchJoinerBakkesComponent.h"


std::string MatchJoinerBakkesComponent::GetPluginName() {
	return "Match Joiner";
}

void MatchJoinerBakkesComponent::SetImGuiContext(uintptr_t ctx) {
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}

// Render the plugin settings here
// This will show up in bakkesmod when the plugin is loaded at
//  f2 -> plugins -> MatchJoinerBakkesComponent
void MatchJoinerBakkesComponent::RenderSettings() {
	ImGui::TextUnformatted("Match Joiner plugin settings");
}

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
