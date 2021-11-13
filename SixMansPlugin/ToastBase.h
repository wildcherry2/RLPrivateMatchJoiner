#pragma once
#include "pch.h"

using namespace std;

namespace tb {
	 //ImFont* roboto_reg;
	 //ImFont* roboto_black;
	 //ImFont* roboto_bold;
	 //ImFontConfig config;
	 //bool notif_enabled/* = true*/;
	 //float xres;
	 //float yres;
	 //float res_ratio_x/* = 1550 / 1920.0*/; //multiply these by res to get scaled toast
	 //float res_ratio_y/* = 20 / 1080.0*/;
	 //float res_ratio_w/* = 350 / 1920.0*/;
	 //float res_ratio_h/* = 400 / 1080.0*/;
	 //std::shared_ptr<ImageWrapper> logo;
	struct ToastBase {
		ToastBase(GameWrapper& gw);
		//void init(GameWrapper& gw);
		void RenderBlankNotif();
		void RenderLogo();
		void RenderHeader(string text);
		void RenderText(string text);
		void RenderNote(string text);

		ImFont* roboto_reg;
		ImFont* roboto_black;
		ImFont* roboto_bold;
		ImFontConfig config;
		bool notif_enabled/* = true*/;
		float xres;
		float yres;
		float res_ratio_x/* = 1550 / 1920.0*/; //multiply these by res to get scaled toast
		float res_ratio_y/* = 20 / 1080.0*/;
		float res_ratio_w/* = 350 / 1920.0*/;
		float res_ratio_h/* = 400 / 1080.0*/;
		std::shared_ptr<ImageWrapper> logo;
		
		//static constexpr float res_ratio_x = 1550 / 1920.0; //multiply these by res to get scaled toast
		//static constexpr float res_ratio_y = 20 / 1080.0;
		//static constexpr float res_ratio_w = 350 / 1920.0;
		//static constexpr float res_ratio_h = 400 / 1080.0;
		//std::shared_ptr<ImageWrapper> logo = std::make_shared<ImageWrapper>("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\sixmanlogo.png", false, true);
		/*size_t xres = 1;
		size_t yres = 1;*/
		//ImFontConfig config; //changed values in imgui header
		/*ImFont* roboto_reg = ImGui::GetIO().Fonts->AddFontFromFileTTF("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\Roboto-Regular.tff", (14.0f / 1080.0f) * yres, &config);
		ImFont* roboto_black = ImGui::GetIO().Fonts->AddFontFromFileTTF("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\Roboto-Black.tff", (14.0f / 1080.0f) * yres, &config);
		ImFont* roboto_bold = ImGui::GetIO().Fonts->AddFontFromFileTTF("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\Roboto-Bold.tff", (14.0f / 1080.0f) * yres, &config);*/
	};
}
