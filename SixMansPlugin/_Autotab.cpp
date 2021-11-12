#include "pch.h"
#include "_Autotab.h"

void Settings::Autotab::Render() {
	if (ImGui::Checkbox("Autotab", &enabled)) cm->getCvar(name).setValue(enabled);
	ImGui::SameLine();
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered()) {
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted("Enable or disable automatically tabbing in after clicking a match link");
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}
