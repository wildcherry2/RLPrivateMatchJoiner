#include "pch.h"
#include "tw.h"

tw::tw(ToastUtils& tb) {
	this->config = tb.config;
	this->logo = tb.logo;
	this->notif_enabled = tb.notif_enabled;
	this->res_ratio_h = tb.res_ratio_h;
	this->res_ratio_w = tb.res_ratio_w;
	this->res_ratio_x = tb.res_ratio_x;
	this->res_ratio_y = tb.res_ratio_y;
	this->roboto_black = tb.roboto_black;
	this->roboto_bold = tb.roboto_bold;
	this->roboto_reg = tb.roboto_reg;
	this->xres = tb.xres;
	this->yres = tb.yres;
	this->isWindowOpen_ = tb.isWindowOpen_;
}

void tw::Render(GameWrapper& gw, CVarManagerWrapper& cw) {
	int flags = ImGuiWindowFlags_NoCollapse + ImGuiWindowFlags_NoMove + ImGuiWindowFlags_NoResize + ImGuiWindowFlags_NoScrollbar + ImGuiWindowFlags_NoTitleBar;
	if (!ImGui::Begin("test", isWindowOpen_.get(), flags)) {
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

	ImGui::Text("test");

	ImGui::End();
}