#pragma once
#include "pch.h"
using namespace std;
struct Match {
	Match() {
		name = "nullname";
		pass = "nullpass";
		this->event = 1;
		gametags = "BotsNone";
		selected_map = "Park_P";
		region = Region::USE;
	};
	string name;
	string pass;
	size_t event;
	string gametags;
	string selected_map;
	Region region;
};