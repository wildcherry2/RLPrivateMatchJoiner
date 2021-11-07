#include "pch.h"
#include "_Timeretry.h"

void Settings::Timeretry::Render() {
	if (ImGui::SliderInt("Seconds to wait before retrying", &val, 30, 120)) cm->getCvar(name).setValue(val);
	ImGui::SameLine();
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered()) {
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted("The time to wait before autoretry attempts to join the match");
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}
