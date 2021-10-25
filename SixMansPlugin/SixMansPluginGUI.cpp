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
	renderAutoretryEnabled();
	renderTimeRetry();
}

void SixMansPlugin::renderModEnabledCheckbox() { 
	CVarWrapper cv = cvarManager->getCvar("6mModEnabled");
	if (!cv) return;
	bool enabled = cv.getBoolValue();

	if (ImGui::Checkbox("Enabled", &enabled)) cv.setValue(enabled);

	ImGui::SameLine();
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted("Enable or disable the plugin");
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}
void SixMansPlugin::renderAutotabEnabled() { 
	CVarWrapper cv = cvarManager->getCvar("6mAutotabInToggle");
	if (!cv) return;
	bool enabled = cv.getBoolValue();
	
	if (ImGui::Checkbox("Autotab", &enabled)) cv.setValue(enabled);
	ImGui::SameLine();
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted("Enable or disable automatically tabbing in after clicking a match link");
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}
void SixMansPlugin::renderAutoretryEnabled() { 
	CVarWrapper cv = cvarManager->getCvar("6mAutoRetryToggle");
	if (!cv) return;
	bool enabled = cv.getBoolValue();

	if (ImGui::Checkbox("Autoretry", &enabled)) { 
		cv.setValue(enabled);
		
	}
	ImGui::SameLine();
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted("Enable or disable automatically retrying to join/create a match after the first attempt");
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}

	//if (enabled) renderTimeRetry();
}
void SixMansPlugin::renderTimeRetry() {
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
	if (ImGui::Combo(name.c_str(), &current, MAP_NORMALNAMES, IM_ARRAYSIZE(MAP_NORMALNAMES))) { cv.setValue(current); }
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