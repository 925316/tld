#include "pch.h"
#include "features/common.h"
#include "core/camera.h"
#include "core/tracking.h"

namespace
{
	void DrawLabel(ImDrawList* draw, const Vector3& worldPos, const std::string& text, ImU32 color)
	{
		Vector3 screen = WorldToScreen(GetMainCamera(), worldPos, 0);
		if (screen.z < 0.1f) return;
		ImGuiIO& io = ImGui::GetIO();
		draw->AddText(ImVec2(screen.x, io.DisplaySize.y - screen.y), color, text.c_str());
	}

	class CorpseEspFeature : public Feature
	{
	public:
		CorpseEspFeature() : Feature("ESP", "Corpses") {}

		void OnTick() override
		{
			void* camera = GetMainCamera();
			if (!camera) return;

			ImDrawList* draw = ImGui::GetForegroundDrawList();
			const Vector3 camPos = g_camera.position;

			Tracking::GearList().for_each([&](void* gi)
				{
					if (!gi) return;
					void* corpse = ReadPtr(reinterpret_cast<uintptr_t>(gi), Offsets::GearBodyHarvest);
					if (!corpse) return;

					Vector3 worldPos = GetGearItemWorldPosition(gi);
					if (worldPos.x == -9999.0f) return;

					float distance = Vector3_Distance(camPos, worldPos);
					if (distance > m_distance) return;

					char buffer[96];
					snprintf(buffer, sizeof(buffer), "Corpse\n%.1fm\nfrozen %d%%",
						distance,
						static_cast<int>(ReadFloat(reinterpret_cast<uintptr_t>(corpse), Offsets::CorpsePercentFrozen) * 100.0f));

					DrawLabel(draw, worldPos, buffer, IM_COL32(200, 140, 255, 255));
				});
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("Distance", &m_distance, 10.0f, 1000.0f);
		}

	private:
		float m_distance = 300.0f;
	};

	REGISTER_FEATURE(CorpseEspFeature)
}
