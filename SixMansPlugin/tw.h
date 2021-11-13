#pragma once
#include "ToastBase.h"

struct tw : ToastUtils {
	tw() {};
	tw(ToastUtils& tb);
	void Render(GameWrapper& gw, CVarManagerWrapper& cw);
};
