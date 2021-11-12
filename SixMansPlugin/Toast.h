#pragma once
#include "pch.h"

using namespace std;

struct Toast {
	Toast() {};

	void Countdown(CVarManagerWrapper cm, GameWrapper gw);
	void RenderActionNotif(CVarManagerWrapper cm, GameWrapper gw);
	void RenderBlankNotif();
	void RenderLogo();
	void RenderHeader(string text);
	void RenderText(string text);
	void RenderButton(string text, CVarManagerWrapper& cm, GameWrapper& gw); //reference may not work
	void RenderNote(string text);
	void setRes(size_t& x, size_t& y);

	bool notif_enabled = true;
	bool countdown = false;
	size_t xres;
	size_t yres;
	double countdown_start = 20;
	double countdown_current;
	float res_ratio_x = 1550 / 1920.0; //multiply these by res to get scaled toast
	float res_ratio_y = 20 / 1080.0;
	float res_ratio_w = 350 / 1920.0;
	float res_ratio_h = 400 / 1080.0;
	float action_notif_width, action_notif_height, action_notif_x, action_notif_y;
	std::shared_ptr<ImageWrapper> logo;
	ImFont* roboto_reg;
	ImFont* roboto_black;
	ImFont* roboto_bold;
	
};