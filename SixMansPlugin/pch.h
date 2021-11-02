#pragma once

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"

#include "Simple-Web-Server/server_http.hpp";

#include <string>
#include <cstring>
#include <vector>
#include <functional>
#include <memory>
#include <iostream>
#include <fstream>
#include <thread>
#include <datetimeapi.h>

#include "imgui/imgui.h"

#include "fmt/core.h"
#include "fmt/ranges.h"

#include "nlohmann/json.hpp"

extern std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

template<typename S, typename... Args>
void log(const S& format_str, Args&&... args)
{
	_globalCvarManager->log(fmt::format(format_str, args...));
}