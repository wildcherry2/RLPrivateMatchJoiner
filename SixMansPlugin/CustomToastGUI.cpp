#include "pch.h"
#include "SixMansPlugin.h"


// Do ImGui rendering here
void SixMansPlugin::Render()
{
	int flags = ImGuiWindowFlags_NoCollapse + ImGuiWindowFlags_NoMove + ImGuiWindowFlags_NoResize + ImGuiWindowFlags_NoScrollbar + ImGuiWindowFlags_NoTitleBar;
	if (!ImGui::Begin(menuTitle_.c_str(), &isWindowOpen_, flags))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}
	//renderCreateMatch();


	ImGui::End();

	if (!isWindowOpen_)
	{
		cvarManager->executeCommand("togglemenu " + GetMenuName());
	}
}

void SixMansPlugin::renderCreateMatch() {
	renderBlankNotif();
	renderLogo();
	ImGui::SameLine();
	renderHeader("Create 6Mans:\nLobby #0001");
	renderText("\nThe match info is loaded in the game!\nPress the button below to create:");
	ImGui::NewLine();
	renderButton("Create");
	renderNote("NOTE: For options, press F2->Plugins->6Mans Plugin Settings");
}

void SixMansPlugin::renderBlankNotif() {
	ImGui::SetWindowPos(ImVec2{ action_notif_x, action_notif_y });
	ImGui::SetWindowSize(ImVec2{ action_notif_width, action_notif_height });
	ImGuiStyle& style = ImGui::GetStyle(); //put in header
	style.WindowRounding = 12.0f;
	style.WindowBorderSize = 0.0f;
}

void SixMansPlugin::renderLogo() {
	if (auto logoTex = logo->GetImGuiTex()) {
		auto rect = ImVec2{ (80.0f/1920.0f)*xres, (80.0f/1920.0f)*xres }; //put in header
		ImGui::Image(logoTex, { rect.x,rect.y });
	}
}

void SixMansPlugin::renderHeader(std::string header) {
	ImGui::PushFont(roboto_black);
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
	ImColor color; //put in header
	
	CVarWrapper cv = cvarManager->getCvar("6mDoAction");
	if (!cv) return;
	bool enabled = cv.getBoolValue(); //unnecessary?
	
	ImGui::NewLine();
	ImGui::SameLine(10.0f);
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)color.HSV(138.0f, 255.0f, 0.0f, 255.0f)); //change to textured buttons
	if (ImGui::Button(text.c_str(), ImVec2{330.0f,100.0f})) gameWrapper->Execute([this](GameWrapper* gw) {cvarManager->executeCommand("6mReady"); });

	ImGui::PopStyleColor();
	ImGui::PopFont();
}

void SixMansPlugin::renderNote(std::string text) {
	ImGui::PushFont(roboto_reg);
	ImGui::NewLine(); //use padding instead, quick method for now
	ImGui::NewLine();
	ImGui::NewLine();
	ImGui::NewLine();
	ImGui::NewLine();

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

//void SixMansPlugin::setResVars() {
//	SettingsWrapper sw = gameWrapper->GetSettings();
//	xres = std::stof(sw.GetVideoSettings().Resolution.substr(0, 4));
//	yres = std::stof(sw.GetVideoSettings().Resolution.substr(7, 4));
//}

/*
*	1920x1080
*   012345678
*	
*	pos = 4
*	length = 9
*	sub 0->pos = 1920
*	pos + 1 = begin of yres = length of xres + delimiter
*	sub pos + 1-> length - pos + 1
* 
*	1280x720
*	01234567
* 
*	pos = 4
*	length = 8
*	sub 0->pos = 1280
*	sub pos + 1->length
*	
*/