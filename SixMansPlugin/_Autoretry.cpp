#include "pch.h"
#include "_Autoretry.h"

void Settings::Autoretry::Render() {
	if (ImGui::Checkbox("Autoretry", &enabled)) {
		cm->getCvar(name).setValue(enabled);
	}
	ImGui::SameLine();
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered()) {
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted("Enable or disable automatically retrying to join/create a match after the first attempt");
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}
