#pragma once
#include "pch.h"

using namespace std;

namespace ToastBase {
	static size_t xres = 1;
	static size_t yres = 1;
	static ImFontConfig config; //changed values in imgui header
	
	//ImageWrapper logo = ImageWrapper("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\sixmanlogo.png", false, true);
	//static std::shared_ptr<ImageWrapper> logo = std::make_shared<ImageWrapper>("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\sixmanlogo.png", false, true);
	static ImFont* roboto_reg = ImGui::GetIO().Fonts->AddFontFromFileTTF("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\Roboto-Regular.tff", (14.0f / 1080.0f) * yres, &config);
	static ImFont* roboto_black = ImGui::GetIO().Fonts->AddFontFromFileTTF("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\Roboto-Black.tff", (14.0f / 1080.0f) * yres, &config);
	static ImFont* roboto_bold = ImGui::GetIO().Fonts->AddFontFromFileTTF("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\Roboto-Bold.tff", (14.0f / 1080.0f) * yres, &config);
	struct ToastBase {
		//static void Countdown(CVarManagerWrapper cm, GameWrapper gw);
		//static void RenderActionNotif(CVarManagerWrapper cm, GameWrapper gw);
		static void RenderBlankNotif();
		static void RenderLogo();
		static void RenderHeader(string text);
		static void RenderText(string text);
		//static void RenderButton(string text, CVarManagerWrapper& cm, GameWrapper& gw); //reference may not work
		static void RenderNote(string text);
		static void setRes(size_t& x, size_t& y, GameWrapper& gw);
		static constexpr bool notif_enabled = true;
		//static bool countdown = false;	
		//static double countdown_start = 20;
		//static double countdown_current;
		static constexpr float res_ratio_x = 1550 / 1920.0; //multiply these by res to get scaled toast
		static constexpr float res_ratio_y = 20 / 1080.0;
		static constexpr float res_ratio_w = 350 / 1920.0;
		static constexpr float res_ratio_h = 400 / 1080.0;
		//static float action_notif_width, action_notif_height, action_notif_x, action_notif_y;
		std::shared_ptr<ImageWrapper> logo = std::make_shared<ImageWrapper>("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\sixmanlogo.png", false, true);
		//static constexpr ImFont* roboto_reg = new ImFont;
		//static constexpr ImFont* roboto_black;
		//static constexpr ImFont* roboto_bold;



	};
}