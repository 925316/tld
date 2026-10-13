#include "pch.h"
#include "overlay/menu.h"
#include "core/camera.h"
#include "core/feature.h"
#include "core/tracking.h"

namespace Menu
{
	void Draw()
	{
		ImGui::Begin("TLD Mod", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		FeatureRegistry::DrawMenu();
		ImGui::Separator();
		ImGui::Text("Animals: %zu  Items: %zu", Tracking::AiList().size(), Tracking::GearList().size());
		ImGui::End();

		ImDrawList* bg = ImGui::GetBackgroundDrawList();
		if (g_camera.valid)
		{
			char status[256];
			snprintf(status, sizeof(status),
				"Camera Pos: (%.1f, %.1f, %.1f) | Rot: (%.2f, %.2f, %.2f, %.2f)",
				g_camera.position.x, g_camera.position.y, g_camera.position.z,
				g_camera.rotation.x, g_camera.rotation.y, g_camera.rotation.z, g_camera.rotation.w);
			bg->AddText(ImVec2(10, 10), IM_COL32(0, 255, 0, 255), status);
		}
		else
		{
			bg->AddText(ImVec2(10, 10), IM_COL32(255, 0, 0, 255), "Camera not found / Player not loaded");
		}
	}
}
