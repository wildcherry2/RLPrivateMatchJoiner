#include "pch.h"
#include "_ModEnabled.h"

void Settings::ModEnabled::Render() {
	if (ImGui::Checkbox("Enabled", &enabled)) cm->getCvar(name).setValue(enabled);
	ImGui::SameLine();
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered()) {
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted("Enable or disable the plugin");
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}
