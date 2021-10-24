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

	renderActionNotif();

	ImGui::End();

	if (!isWindowOpen_)
	{
		gameWrapper->Execute([this](GameWrapper* gw) {cvarManager->executeCommand("togglemenu " + GetMenuName()); });
	}
}

void SixMansPlugin::renderActionNotif() {
	renderBlankNotif();
	renderLogo();
	ImGui::SameLine();
	if (cvarManager->getCvar("6mEventType").getIntValue() == 1) {
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

void SixMansPlugin::renderStatusNotif(size_t type, size_t code) {

}

void SixMansPlugin::renderBlankNotif() {
	ImGui::SetWindowPos(ImVec2{ action_notif_x, action_notif_y }); //all notifs have the same origin, generify
	ImGui::SetWindowSize(ImVec2{ action_notif_width,/* action_notif_height*/0 }); //setting height to 0 lets it autoresize
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 12.0f;
	style.WindowBorderSize = 0.0f;
	//style.ItemSpacing = ImVec2{ 10.0f,10.0f };
	//style.FramePadding = ImVec2{ 20.0f,20.0f };
	//ImGui::Dummy(ImVec2(10.0f, 10.0f));
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

void SixMansPlugin::renderButton(std::string text) {
	ImGui::PushFont(roboto_bold);
	ImColor color;
	
	//disable num lock, shift + 0 or shift + insert gives error from a crash
	//probably should change height to be a function of yres instead of xres

	//ImGui::NewLine();
	ImGui::SameLine(10.0f);
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)color.HSV(138.0f, 255.0f, 0.0f, 255.0f)); //change to textured buttons
	if (ImGui::Button(text.c_str(), ImVec2{(330.0f/1920.f)*xres,(100.0f/1920.0f)*xres})) gameWrapper->Execute([this](GameWrapper* gw) {cvarManager->executeCommand("6mReady"); });

	ImGui::PopStyleColor();
	ImGui::PopFont();
}

void SixMansPlugin::renderNote(std::string text) {
	ImGui::PushFont(roboto_reg);
	//ImGui::NewLine(); //use padding instead, quick method for now
	//ImGui::NewLine();
	/*ImGui::NewLine();
	ImGui::NewLine();
	ImGui::NewLine();*/

	ImGui::Text(text.c_str());
	ImGui::PopFont();
}

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
	isWindowOpen_ = false;
}