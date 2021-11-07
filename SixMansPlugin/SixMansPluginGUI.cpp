//https://bakkesmodwiki.github.io/bakkesmod_api/
//https://pthom.github.io/imgui_manual_online/manual/imgui_manual.html
#include "pch.h"
#include "SixMansPlugin.h"


std::string SixMansPlugin::GetPluginName() {
	return "6Mans Plugin Settings";
}
void SixMansPlugin::SetImGuiContext(uintptr_t ctx) {
	ImGui::SetCurrentContext(reinterpret_cast<ImGuiContext*>(ctx));
}
void SixMansPlugin::RenderSettings() {
	renderModEnabledCheckbox();
	renderMapCombobox("Default Map");
	renderAutotabEnabled();
	renderAutojoinEnabled();
	renderAutoretryEnabled();
}

void SixMansPlugin::renderModEnabledCheckbox() { 
	Settings::ModEnabled me = Settings::ModEnabled(*cvarManager);
	me.Render();
}
void SixMansPlugin::renderAutotabEnabled() { 
	Settings::Autotab at = Settings::Autotab(*cvarManager);
	at.Render();
}

void SixMansPlugin::renderAutojoinEnabled() {
	Settings::Autojoin aj = Settings::Autojoin(*cvarManager);
	aj.Render();
}

void SixMansPlugin::renderAutoretryEnabled() { 
	Settings::Autoretry ar = Settings::Autoretry(*cvarManager);
	ar.Render();
	//if(enabled) renderTimeRetry();
}
void SixMansPlugin::renderTimeRetry() {
	//if(ar.enabled) { rest of shit here }
	CVarWrapper cv = cvarManager->getCvar("6mTimeBeforeRetrying");
	if (!cv) return;
	int val = cv.getIntValue();

	if (ImGui::SliderInt("Seconds to wait before retrying", &val, 30, 120)) cv.setValue(val);
	ImGui::SameLine();
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted("The time to wait before autoretry attempts to join the match");
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}
void SixMansPlugin::renderMapCombobox(std::string name) {
	CVarWrapper cv = cvarManager->getCvar("6mMapNameSelection");
	if (!cv) return;
	int current = cv.getIntValue();
	if (ImGui::Combo(name.c_str(), &current, Constants::MAP_NORMALNAMES, IM_ARRAYSIZE(Constants::MAP_NORMALNAMES))) { cv.setValue(current); }
	ImGui::SameLine();
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted("The default map when creating matches.\nNOTE:Only standard maps are listed");
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}