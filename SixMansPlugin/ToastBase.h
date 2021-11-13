#pragma once
#include "pch.h"

using namespace std;

//namespace tb {

	struct ToastUtils {
		ToastUtils() {};
		ToastUtils(GameWrapper& gw);
		//void init(GameWrapper& gw);
		static void RenderBlankNotif(float& xres, float& yres, float& res_ratio_x, float& res_ratio_y, float& res_ratio_w);
		static void RenderLogo(ImageWrapper& logo, float& xres);
		static void RenderHeader(string text, ImFont* roboto_black);
		static void RenderText(string text, ImFont* roboto_bold);
		static void RenderNote(string text, ImFont* roboto_reg);

		shared_ptr<ImFont*> roboto_reg;
		shared_ptr<ImFont*> roboto_black;
		shared_ptr<ImFont*> roboto_bold;
		shared_ptr<ImFontConfig> config;
		shared_ptr<bool> notif_enabled/* = true*/;
		shared_ptr<bool> isWindowOpen_;
		shared_ptr<float> xres;
		shared_ptr<float> yres;
		shared_ptr<float> res_ratio_x; //multiply these by res to get scaled toast
		shared_ptr<float> res_ratio_y;
		shared_ptr<float> res_ratio_w;
		shared_ptr<float> res_ratio_h;
		shared_ptr<ImageWrapper> logo;
	};
//}
