#include "pch.h"
#include "_Autojoin.h"

void Settings::Autojoin::Render() {
	if (ImGui::Checkbox("Autojoin", &enabled)) cm->getCvar(name).setValue(enabled);
	ImGui::SameLine();
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered()) {
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted("Enable or disable automatically joining once match info is loaded");
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}
