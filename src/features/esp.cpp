#include "pch.h"
#include "core/feature.h"
#include "core/camera.h"
#include "core/game.h"
#include "core/tracking.h"

namespace
{
	void DrawEspText(ImDrawList* draw, const Vector3& worldPos, const std::string& text, ImU32 color, float maxDistance)
	{
		Vector3 screenPos = WorldToScreen(GetMainCamera(), worldPos, 0);
		if (screenPos.z < 0.1f) return;

		if (Vector3_Distance(g_camera.position, worldPos) > maxDistance) return;

		ImGuiIO& io = ImGui::GetIO();
		draw->AddText(ImVec2(screenPos.x, io.DisplaySize.y - screenPos.y), color, text.c_str());
	}

	class AnimalEspFeature : public Feature
	{
	public:
		AnimalEspFeature() : Feature("ESP", "Animals") {}

		void OnTick() override
		{
			void* camera = GetMainCamera();
			if (!camera) return;

			ImDrawList* draw = ImGui::GetForegroundDrawList();
			const Vector3 camPos = g_camera.position;

			Tracking::AiList().for_each([&](void* ai)
				{
					Vector3 worldPos = GetWorldPosition(ai);
					bool dead = AiHP(ai) <= 0.0f;
					if (dead && !m_showDead) return;

					std::string text = AiSubTypeName(AiSubType(ai));
					text += '\n';
					if (m_showHp)
					{
						text += std::to_string(static_cast<int>(AiHP(ai))) + '/' +
							std::to_string(static_cast<int>(AiMaxHP(ai))) + '\n';
					}
					char distBuf[32];
					sprintf_s(distBuf, "%.1fm", Vector3_Distance(camPos, worldPos));
					text += distBuf;
					if (m_showName)
					{
						System_String* name = AiDisplayName(ai);
						if (name)
						{
							text += '\n' + name->ToString();
						}
					}

					if (AiModeIsHostile(AiMode(ai)))
					{
						Vector3 screenPos = WorldToScreen(camera, worldPos, 0);
						if (screenPos.z >= 0.1f)
						{
							ImGuiIO& io = ImGui::GetIO();
							draw->AddText(ImVec2(screenPos.x, io.DisplaySize.y - screenPos.y),
								IM_COL32(255, 40, 40, 255), text.c_str());
						}
						return;
					}
					DrawEspText(draw, worldPos, text, IM_COL32(255, 100, 100, 255), m_distance);
				});
		}

		void OnMenu() override
		{
			ImGui::Checkbox("Show HP", &m_showHp);
			ImGui::SameLine();
			ImGui::Checkbox("Show Name", &m_showName);
			ImGui::Checkbox("Show Dead", &m_showDead);
			ImGui::SliderFloat("Distance", &m_distance, 10.0f, 1000.0f);
		}

	private:
		bool m_showHp = true;
		bool m_showName = true;
		bool m_showDead = false;
		float m_distance = 250.0f;
	};

	class ItemEspFeature : public Feature
	{
	public:
		ItemEspFeature() : Feature("ESP", "Items") {}

		void OnTick() override
		{
			if (!GetMainCamera()) return;

			ImDrawList* draw = ImGui::GetForegroundDrawList();
			const Vector3 camPos = g_camera.position;

			Tracking::GearList().for_each([&](void* item)
				{
					Vector3 worldPos = GetGearItemWorldPosition(item);
					if (worldPos.x == -9999.0f) return;

					std::string text = "*\n";
					char distBuf[32];
					sprintf_s(distBuf, "%.1fm", Vector3_Distance(camPos, worldPos));
					text += distBuf;

					System_String* nameStr = GearItem_GetName(item);
					if (nameStr)
					{
						std::string name = nameStr->ToString();
						if (name.find('[') == std::string::npos)
						{
							text += '\n' + name;
						}
					}
					DrawEspText(draw, worldPos, text, IM_COL32(255, 255, 100, 255), m_distance);
				});
		}

		void OnMenu() override
		{
			ImGui::SliderFloat("Distance", &m_distance, 10.0f, 1000.0f);
		}

	private:
		float m_distance = 250.0f;
	};

	REGISTER_FEATURE(AnimalEspFeature)
	REGISTER_FEATURE(ItemEspFeature)
}
