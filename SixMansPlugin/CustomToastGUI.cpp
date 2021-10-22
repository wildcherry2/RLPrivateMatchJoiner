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

	ImGui::SetWindowPos(ImVec2{res_ratio_x * xres, res_ratio_y * yres});
	ImGui::SetWindowSize(ImVec2{res_ratio_w * xres, res_ratio_h * yres});
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 12.0f;
	style.WindowBorderSize = 0.0f;

	ImGui::PushFont(helvetica);
	
	//ImGui::AlignTextToFramePadding();

	if (auto logoTex = logo->GetImGuiTex()) {
		auto rect = ImVec2{70.0f,70.0f};
		ImGui::Image(logoTex, {rect.x,rect.y});
	}

	ImGui::SameLine();
	ImGui::Text("Create 6Mans:\nLobby #0001");

	/*std::string w = "Width: " + std::to_string(ImGui::GetWindowWidth());
	std::string l = "Height: " + std::to_string(ImGui::GetWindowHeight());
	std::string x = "x: " + std::to_string(ImGui::GetWindowPos().x);
	std::string y = "y: " + std::to_string(ImGui::GetWindowPos().y);

	ImGui::Text(w.c_str());
	ImGui::Text(l.c_str());
	ImGui::Text(x.c_str());
	ImGui::Text(y.c_str());*/
	/*ImGui::Text(std::to_string(xres).c_str());
	ImGui::Text(std::to_string(yres).c_str());*/
	//ImGui::Text(gameWrapper->GetSettings().GetVideoSettings().Resolution.substr(7, 4).c_str());
	ImGui::PopFont();
	ImGui::End();

	if (!isWindowOpen_)
	{
		cvarManager->executeCommand("togglemenu " + GetMenuName());
	}
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