#include "pch.h"
#include "ToastBase.h"

//using namespace tb;
using namespace std;

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

ToastUtils::ToastUtils(GameWrapper& gw) {
	//ToastBase::notif_enabled = true;
	config = make_shared<ImFontConfig>();
	notif_enabled = make_shared<bool>(true);
	isWindowOpen_ = make_shared<bool>(false);
	res_ratio_x = make_shared<float>(1550.0 / 1920.0);
	res_ratio_y = make_shared<float>(20.0 / 1080.0);
	res_ratio_w = make_shared<float>(350.0 / 1920.0);
	res_ratio_h = make_shared<float>(400.0 / 1080);
	std::string res_str = gw.GetSettings().GetVideoSettings().Resolution;
	size_t pos = res_str.find("x");
	
	config->OversampleH = 2;
	config->OversampleV = 2;
	xres = make_shared<float>(std::stof(res_str.substr(0, pos)));
	yres = make_shared<float>(std::stof(res_str.substr(pos + 1, res_str.length() - pos + 1)))/* * res_ratio_y*/;
	logo = std::make_shared<ImageWrapper>(std::string("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\sixmanlogo.png"), false, true);
	roboto_reg = make_shared<ImFont*>(ImGui::GetIO().Fonts->AddFontFromFileTTF("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\Roboto-Regular.tff", (14.0f / 1080.0f) * *yres, config.get()));
	roboto_black = make_shared<ImFont*>(ImGui::GetIO().Fonts->AddFontFromFileTTF("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\Roboto-Black.tff", (14.0f / 1080.0f) * *yres, config.get()));
	roboto_bold = make_shared<ImFont*>(ImGui::GetIO().Fonts->AddFontFromFileTTF("%APPDATA%\\bakkesmod\\bakkesmod\\data\\6m\\Roboto-Bold.tff", (14.0f / 1080.0f) * *yres, config.get()));
	//setRes(xres, yres, gw);
	
}

void ToastUtils::RenderBlankNotif(float& xres, float& yres, float& res_ratio_x, float& res_ratio_y, float& res_ratio_w) {
	ImGui::SetWindowPos(ImVec2{ xres * res_ratio_x, yres * res_ratio_y });
	ImGui::SetWindowSize(ImVec2{xres * res_ratio_w, 0 }); //setting height to 0 lets it autoresize
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 12.0f;
	style.WindowBorderSize = 0.0f;
}

void ToastUtils::RenderLogo(ImageWrapper& logo, float& xres) {
	if (auto logoTex = logo.GetImGuiTex()) {
		auto logo_rect = ImVec2{ (80.0f / 1920.0f) * xres, (80.0f / 1920.0f) * xres };
		ImGui::Image(logoTex, { logo_rect.x,logo_rect.y });
	}
}

void ToastUtils::RenderHeader(std::string text, ImFont* roboto_black) {
	ImGui::PushFont(roboto_black);
	ImGui::SameLine();

	ImGui::Text(text.c_str());
	ImGui::PopFont();
}

void ToastUtils::RenderText(std::string text, ImFont* roboto_bold) {
	ImGui::PushFont(roboto_bold);
	ImGui::Text(text.c_str());
	ImGui::PopFont();
}

void ToastUtils::RenderNote(std::string text, ImFont* roboto_reg) {
	ImGui::PushFont(roboto_reg);
	ImGui::Text(text.c_str());
	ImGui::PopFont();
}
