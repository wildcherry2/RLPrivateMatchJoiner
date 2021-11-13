#include "pch.h"
#include "ToastBase.h"

using namespace tb;

//bool ToastBase::notif_enabled = true;
//float ToastBase::res_ratio_x = 1550.0 / 1920.0;
//float ToastBase::res_ratio_y = 20.0 / 1080.0;
//float ToastBase::res_ratio_w = 350.0 / 1920.0;
//float ToastBase::res_ratio_h = 400.0 / 1080;
//ImFontConfig ToastBase::config;
//std::shared_ptr<ImageWrapper> ToastBase::logo = std::make_shared<ImageWrapper>(std::string("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\sixmanlogo.png"), false, true);
//ImFont* ToastBase::roboto_reg = ImGui::GetIO().Fonts->AddFontFromFileTTF("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\Roboto-Regular.tff", (14.0f / 1080.0f) * yres, &config);
//ImFont* ToastBase::roboto_black = ImGui::GetIO().Fonts->AddFontFromFileTTF("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\Roboto-Black.tff", (14.0f / 1080.0f) * yres, &config);
//ImFont* ToastBase::roboto_bold = ImGui::GetIO().Fonts->AddFontFromFileTTF("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\Roboto-Bold.tff", (14.0f / 1080.0f) * yres, &config);
//float ToastBase::xres = 0/* * res_ratio_x*/;
//float ToastBase::yres = 0/* * res_ratio_y*/;

ToastBase::ToastBase(GameWrapper& gw) {
	//ToastBase::notif_enabled = true;
	notif_enabled = true;
	res_ratio_x = 1550.0 / 1920.0;
	res_ratio_y = 20.0 / 1080.0;
	res_ratio_w = 350.0 / 1920.0;
	res_ratio_h = 400.0 / 1080;
	std::string res_str = gw.GetSettings().GetVideoSettings().Resolution;
	size_t pos = res_str.find("x");
	
	config.OversampleH = 2;
	config.OversampleV = 2;
	ToastBase::xres = std::stof(res_str.substr(0, pos))/* * res_ratio_x*/;
	ToastBase::yres = std::stof(res_str.substr(pos + 1, res_str.length() - pos + 1))/* * res_ratio_y*/;
	ToastBase::logo = std::make_shared<ImageWrapper>(std::string("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\sixmanlogo.png"), false, true);
	ToastBase::roboto_reg = ImGui::GetIO().Fonts->AddFontFromFileTTF("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\Roboto-Regular.tff", (14.0f / 1080.0f) * yres, &config);
	ToastBase::roboto_black = ImGui::GetIO().Fonts->AddFontFromFileTTF("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\Roboto-Black.tff", (14.0f / 1080.0f) * yres, &config);
	ToastBase::roboto_bold = ImGui::GetIO().Fonts->AddFontFromFileTTF("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\Roboto-Bold.tff", (14.0f / 1080.0f) * yres, &config);
	//setRes(xres, yres, gw);
	
}

void tb::ToastBase::RenderBlankNotif() {
	ImGui::SetWindowPos(ImVec2{ xres * res_ratio_x, yres * res_ratio_y });
	ImGui::SetWindowSize(ImVec2{xres * res_ratio_w, 0 }); //setting height to 0 lets it autoresize
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 12.0f;
	style.WindowBorderSize = 0.0f;
}

void tb::ToastBase::RenderLogo() {
	if (auto logoTex = logo->GetImGuiTex()) {
		auto logo_rect = ImVec2{ (80.0f / 1920.0f) * xres, (80.0f / 1920.0f) * xres };
		ImGui::Image(logoTex, { logo_rect.x,logo_rect.y });
	}
}

void tb::ToastBase::RenderHeader(std::string text) {
	ImGui::PushFont(roboto_black);
	ImGui::SameLine();

	ImGui::Text(text.c_str());
	ImGui::PopFont();
}

void tb::ToastBase::RenderText(std::string text) {
	ImGui::PushFont(roboto_bold);
	ImGui::Text(text.c_str());
	ImGui::PopFont();
}

void tb::ToastBase::RenderNote(std::string text) {
	ImGui::PushFont(roboto_reg);
	ImGui::Text(text.c_str());
	ImGui::PopFont();
}
