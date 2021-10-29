#include "pch.h"
#include "SixMansPlugin.h"


// Do ImGui rendering here
void SixMansPlugin::Render()
{
	if (!notif_enabled) return;
	int flags = ImGuiWindowFlags_NoCollapse + ImGuiWindowFlags_NoMove + ImGuiWindowFlags_NoResize + ImGuiWindowFlags_NoScrollbar + ImGuiWindowFlags_NoTitleBar;
	if (!ImGui::Begin(menuTitle_.c_str(), &isWindowOpen_, flags))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}
	if (!countdown)
		renderActionNotif();
	else
		renderCountdown();

	ImGui::End();

	if (!isWindowOpen_)
	{
		gameWrapper->Execute([this](GameWrapper* gw) {cvarManager->executeCommand("togglemenu " + GetMenuName()); });
	}
}

void SixMansPlugin::renderCountdown() {
	renderBlankNotif();
	renderLogo();

	ImGui::SameLine();
	renderHeader("Looks like you\ncouldn't join...");
	ImGui::Dummy(ImVec2(3.0f, 3.0f));
	renderText("Autoretry is enabled!"); //branch here if autoretry is disabled to click a button
	ImGui::Dummy(ImVec2(3.0f, 3.0f));
	ImGui::NewLine();
	renderText("Retrying in " + std::to_string(countdown_start) + " seconds...");
	/*while (countdown_start > 0) {
		gameWrapper->SetTimeout([this](GameWrapper* gw) {
			countdown_start--;
			}, 1.0f);
	}*/
}

void SixMansPlugin::renderActionNotif() {
	renderBlankNotif();
	renderLogo();
	ImGui::SameLine();
	if (cvarManager->getCvar("6mEventType").getIntValue() == 1) { //cvarmanager out of scope, need execute
		renderHeader("Join 6Mans:\nLobby #0001");
		ImGui::Dummy(ImVec2(3.0f, 3.0f));
		renderText("The match info is loaded in the game!\nPress the button below to join:");
		ImGui::Dummy(ImVec2(3.0f, 3.0f));
		ImGui::NewLine();
		renderButton("Join");
		ImGui::Dummy(ImVec2(3.0f, 3.0f));
		renderNote("NOTE: For options, press F2->Plugins->6Mans Plugin Settings");
	}
	else {
		renderHeader("Create 6Mans:\nLobby #0001");
		ImGui::Dummy(ImVec2(3.0f, 3.0f));
		renderText("The match info is loaded in the game!\nPress the button below to create:");
		ImGui::Dummy(ImVec2(3.0f, 3.0f));
		ImGui::NewLine();
		renderButton("Create");
		ImGui::Dummy(ImVec2(3.0f, 3.0f));
		renderNote("NOTE: For options, press F2->Plugins->6Mans Plugin Settings");
	}
}

//void SixMansPlugin::renderStatusNotif(size_t type, size_t code) {
//
//}

void SixMansPlugin::renderBlankNotif() {
	ImGui::SetWindowPos(ImVec2{ action_notif_x, action_notif_y }); //all notifs have the same origin, generify
	ImGui::SetWindowSize(ImVec2{ action_notif_width,/* action_notif_height*/0 }); //setting height to 0 lets it autoresize
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 12.0f;
	style.WindowBorderSize = 0.0f;
}

void SixMansPlugin::renderLogo() {
	if (auto logoTex = logo->GetImGuiTex()) {
		auto logo_rect = ImVec2{ (80.0f / 1920.0f) * xres, (80.0f / 1920.0f) * xres };
		ImGui::Image(logoTex, { logo_rect.x,logo_rect.y });
	}
}

void SixMansPlugin::renderHeader(std::string header) {
	ImGui::PushFont(roboto_black);
	ImGui::SameLine();
	
	ImGui::Text(header.c_str());
	ImGui::PopFont();
}

void SixMansPlugin::renderText(std::string text) {
	ImGui::PushFont(roboto_bold);
	ImGui::Text(text.c_str());
	ImGui::PopFont();
}

//gamewrapper timeout for countdown?
void SixMansPlugin::renderButton(std::string text) {
	ImGui::PushFont(roboto_bold);
	ImColor color;
	
	//disable num lock, shift + 0 or shift + insert gives error from a crash
	//probably should change height to be a function of yres instead of xres

	//ImGui::NewLine();
	ImGui::SameLine(10.0f);
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)color.HSV(138.0f, 255.0f, 0.0f, 255.0f));

	/*if (attempting_action) { 
		text = "Attempting..."; 
		ImGui::Button(text.c_str(), ImVec2{ (330.0f / 1920.f) * xres,(100.0f / 1920.0f) * xres });
	}*/
	//else {
	if (ImGui::Button(text.c_str(), ImVec2{ (330.0f / 1920.f) * xres,(100.0f / 1920.0f) * xres })) gameWrapper->Execute([this](GameWrapper* gw) {cvarManager->executeCommand("6mReady"); });
	//}

	ImGui::PopStyleColor();
	ImGui::PopFont();
}

void SixMansPlugin::renderNote(std::string text) {
	ImGui::PushFont(roboto_reg);
	ImGui::Text(text.c_str());
	ImGui::PopFont();
}

//void SixMansPlugin::countdown(size_t time) {
//	//std::chrono::time_point<std::chrono::system_clock> start_time = std::chrono::system_clock::now();
//	std::chrono::time_point<std::chrono::system_clock> marked_time = std::chrono::system_clock::now();
//	size_t seconds_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(marked_time - start_time).count()/1000;
//}

// Name of the menu that is used to toggle the window.
std::string SixMansPlugin::GetMenuName()
{
	return "SixMansPluginInterface";
}

// Title to give the menu
std::string SixMansPlugin::GetMenuTitle()
{
	return menuTitle_;
}

// Should events such as mouse clicks/key inputs be blocked so they won't reach the game
bool SixMansPlugin::ShouldBlockInput()
{
	return ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard;
}

// Return true if window should be inSixMansPluginractive
bool SixMansPlugin::IsActiveOverlay()
{
	return true;
}

// Called when window is opened
void SixMansPlugin::OnOpen()
{
	isWindowOpen_ = true;
}

// Called when window is closed
void SixMansPlugin::OnClose()
{
	//add reset everything, close button
	isWindowOpen_ = false;
}