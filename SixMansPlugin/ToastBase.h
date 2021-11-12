#pragma once
#include "pch.h"

using namespace std;

namespace ToastBase {
	static size_t xres = 1;
	static size_t yres = 1;
	static ImFontConfig config; //changed values in imgui header
	static ImFont* roboto_reg = ImGui::GetIO().Fonts->AddFontFromFileTTF("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\Roboto-Regular.tff", (14.0f / 1080.0f) * yres, &config);
	static ImFont* roboto_black = ImGui::GetIO().Fonts->AddFontFromFileTTF("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\Roboto-Black.tff", (14.0f / 1080.0f) * yres, &config);
	static ImFont* roboto_bold = ImGui::GetIO().Fonts->AddFontFromFileTTF("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\Roboto-Bold.tff", (14.0f / 1080.0f) * yres, &config);

	struct ToastBase {
		static void RenderBlankNotif();
		static void RenderLogo();
		static void RenderHeader(string text);
		static void RenderText(string text);
		static void RenderNote(string text);
		static void setRes(size_t& x, size_t& y, GameWrapper& gw);
		static constexpr bool notif_enabled = true;
		static constexpr float res_ratio_x = 1550 / 1920.0; //multiply these by res to get scaled toast
		static constexpr float res_ratio_y = 20 / 1080.0;
		static constexpr float res_ratio_w = 350 / 1920.0;
		static constexpr float res_ratio_h = 400 / 1080.0;
		std::shared_ptr<ImageWrapper> logo = std::make_shared<ImageWrapper>("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\sixmanlogo.png", false, true);
	};
}