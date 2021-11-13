#include "pch.h"
#include "SixMansPlugin.h"


// Do ImGui rendering here
void SixMansPlugin::Render()
{
	//if (!notif_enabled) return;
	int flags = ImGuiWindowFlags_NoCollapse + ImGuiWindowFlags_NoMove + ImGuiWindowFlags_NoResize + ImGuiWindowFlags_NoScrollbar + ImGuiWindowFlags_NoTitleBar;
	if (!ImGui::Begin(menuTitle_.c_str(), &isWindowOpen_, flags))
	{
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}
	//if (!bind_block_enabled) {
	//	//cvarManager->setBind("Esc","openmenu SixMansPluginInterface");
	//
	//	bind_block_enabled = true;
	//}
	/*if (!countdown)
		renderActionNotif();
	else
	{	
		renderCountdown();
	}*/

	

	ImGui::End();

	/*ImGui::SetNextWindowSize(ImVec2{ 500,500 });
	if (!ImGui::Begin("test"),&isWindowOpen_) {
		ImGui::End();
		return;
	}

	ImGui::Text("test text");

	ImGui::End();*/

	if (!isWindowOpen_)
	{
		gameWrapper->Execute([this](GameWrapper* gw) {cvarManager->executeCommand("togglemenu " + GetMenuName()); });
	}
}

//void SixMansPlugin::renderCountdown() {
//	renderBlankNotif();
//	renderLogo();
//
//	ImGui::SameLine();
//	renderHeader("Looks like you\ncouldn't join...");
//	ImGui::Dummy(ImVec2(3.0f, 3.0f));
//	
//	if (is_enabled_autoretry) {
//		renderText("Autoretry is enabled!"); //branch here if autoretry is disabled to click a button
//		ImGui::Dummy(ImVec2(3.0f, 3.0f));
//		ImGui::NewLine();
//
//		countdown_current = ImGui::GetTime();
//		double val = (double)time_to_wait - (countdown_current - countdown_start);
//		std::string t_string = val <= 0 ? "Retrying in 0 seconds..." : "Retrying in " + std::to_string((int)val) + " seconds...";
//		//countdown_current = ImGui::GetTime(); 
//
//		//logt(std::to_string(countdown_start));
//		renderText(t_string);
//	}
//
//	else {
//		renderText("Try again?");
//		ImGui::Dummy(ImVec2(3.0f, 3.0f));
//		ImGui::NewLine();
//		if (cvarManager->getCvar("6mEventType").getIntValue() == 1)
//			renderButton("Join");
//		else
//			renderButton("Create");
//		
//	}
//}
//
//void SixMansPlugin::initCountdown() {
//	countdown_start = ImGui::GetTime(); //THIS IS NOT BEING SET, START ALWAYS IS 0
//	countdown_current = countdown_start;
//}
//
//void SixMansPlugin::renderActionNotif() {
//	renderBlankNotif();
//	renderLogo();
//	ImGui::SameLine();
//	if (cvarManager->getCvar("6mEventType").getIntValue() == 1) {
//		renderHeader("Join 6Mans:\nLobby #" + match_info.name.substr(1, match_info.name.npos));
//		ImGui::Dummy(ImVec2(3.0f, 3.0f));
//		renderText("The match info is loaded in the game!\nPress the button below to join:");
//		ImGui::Dummy(ImVec2(3.0f, 3.0f));
//		ImGui::NewLine();
//		renderButton("Join");
//		ImGui::Dummy(ImVec2(3.0f, 3.0f));
//		renderNote("NOTE: For options, press F2->Plugins->6Mans Plugin Settings");
//	}
//	else {
//		renderHeader("Create 6Mans:\nLobby #" + match_info.name.substr(1, match_info.name.npos));
//		ImGui::Dummy(ImVec2(3.0f, 3.0f));
//		renderText("The match info is loaded in the game!\nPress the button below to create:");
//		ImGui::Dummy(ImVec2(3.0f, 3.0f));
//		ImGui::NewLine();
//		renderButton("Create");
//		ImGui::Dummy(ImVec2(3.0f, 3.0f));
//		renderNote("NOTE: For options, press F2->Plugins->6Mans Plugin Settings");
//	}
//}
//
//void SixMansPlugin::renderBlankNotif() {
//	ImGui::SetWindowPos(ImVec2{ action_notif_x, action_notif_y });
//	ImGui::SetWindowSize(ImVec2{ action_notif_width, 0 }); //setting height to 0 lets it autoresize
//	ImGuiStyle& style = ImGui::GetStyle();
//	style.WindowRounding = 12.0f;
//	style.WindowBorderSize = 0.0f;
//}
//
//void SixMansPlugin::renderLogo() {
//	if (auto logoTex = logo->GetImGuiTex()) {
//		auto logo_rect = ImVec2{ (80.0f / 1920.0f) * xres, (80.0f / 1920.0f) * xres };
//		ImGui::Image(logoTex, { logo_rect.x,logo_rect.y });
//	}
//}
//
//void SixMansPlugin::renderHeader(std::string header) {
//	ImGui::PushFont(roboto_black);
//	ImGui::SameLine();
//	
//	ImGui::Text(header.c_str());
//	ImGui::PopFont();
//}
//
//void SixMansPlugin::renderText(std::string text) {
//	ImGui::PushFont(roboto_bold);
//	ImGui::Text(text.c_str());
//	ImGui::PopFont();
//}
//
//void SixMansPlugin::renderButton(std::string text) {
//	ImGui::PushFont(roboto_bold);
//	ImColor color;
//	
//	//probably should change height to be a function of yres instead of xres
//
//	ImGui::SameLine(10.0f);
//	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)color.HSV(138.0f, 255.0f, 0.0f, 255.0f));
//
//	if (ImGui::Button(text.c_str(), ImVec2{ (330.0f / 1920.f) * xres,(100.0f / 1920.0f) * xres })) gameWrapper->Execute([this](GameWrapper* gw) {cvarManager->executeCommand("6mReady"); });
//
//	ImGui::PopStyleColor();
//	ImGui::PopFont();
//}
//
//void SixMansPlugin::renderNote(std::string text) {
//	ImGui::PushFont(roboto_reg);
//	ImGui::Text(text.c_str());
//	ImGui::PopFont();
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
	/*if (bind_block_enabled) {
		cvarManager->removeBind("Escape");
		bind_block_enabled = false;
	}*/
	isWindowOpen_ = false;
	//gameWrapper->Execute([this](GameWrapper* gw) {cvarManager->executeCommand("openmenu " + GetMenuName()); });
	//cvarManager->executeCommand("openmenu SixMansPluginInterface");
}